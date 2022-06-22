#include "math.h"
#include <cmath>
#include "../Lib/function.h"
#include "../Value/arrayvalue.h"
#include "../Value/boolvalue.h"
#include "../Value/numbervalue.h"
#include "../Value/functionvalue.h"
#include "../Lib/classes.h"
#include "../Lib/functions.h"
#include "../Lib/moduleclass.h"
#include "../Lib/moduleobject.h"
#include "../Lib/variables.h"
#include "../Exception/argumentsmismatchexception.h"
#include "../Exception/mathexception.h"
#include "../Exception/typeexception.h"
#include "../Exception/unknownpropertyexception.h"
#include "../Value/bignumbers/smath.h"
#include "../Lib/utils.h"

using namespace SlavaScript::lang;
using namespace SlavaScript::modules::math_f;
using SlavaScript::modules::Math;
using SlavaScript::exceptions::ArgumentsMismatchException;
using SlavaScript::exceptions::MathException;
using SlavaScript::exceptions::TypeException;
using SlavaScript::exceptions::UnknownPropertyException;

namespace SlavaScript::modules::math_out{
    using SlavaScript::lang::compare;
    using PolynomialCoeff = RationalBig;

    CLASS_IN_MODULE_1(Polynomial)
        std::vector<PolynomialCoeff> coefficients;

        Polynomial(std::vector<std::shared_ptr<Value>> values){
            for(auto x : values) coefficients.push_back(x -> asBignum());
        }
        Polynomial(Polynomial const& temp) : coefficients(temp.coefficients) {}
        Polynomial(std::vector<PolynomialCoeff> coefficients = {Bignum::ZERO}) : coefficients(coefficients){ delete_end_zero(); }

        int deg() const{
            if (coefficients.size() == 1 && !coefficients[0]) return -1;
            return coefficients.size() - 1;
        }

        std::shared_ptr<Value> copy() override{
            return SHARE(Polynomial, coefficients);
        }
        operator std::string() override{
            std::string ans = "<polynomial=";
            for(int i = coefficients.size() - 1; i > -1; --i){
                if (coefficients[i]){
                    std::string c = std::string(coefficients[i]);
                    if (c == "-1" && i) ans += "-";
                    else if (c[0] != '-' && ans.size() > 12) ans += "+";
                    if (i == 0 || c != "1" && c != "-1") ans += c;
                    if (i) ans += "x";
                    if (i > 1){
                        ans += "^";
                        int q = i;
                        while(q){
                            ans += char('0' + q % 10);
                            q /= 10;
                        }
                    }
                }
            }
            if (ans.size() == 12) ans += '0';
            return ans + ">";
        }

        std::shared_ptr<Value> getDot(std::shared_ptr<Value> property) override;

        ~Polynomial(){}

        void delete_end_zero(){
            for(int i = coefficients.size() - 1; i > 0; --i) if (coefficients[i]) break; else coefficients.pop_back();
        }

        Polynomial operator+() const{
            return Polynomial(*this);
        }

        Polynomial operator-() const{
            int sz = coefficients.size();
            std::vector<PolynomialCoeff> new_v(sz);
            for(int i = 0; i < sz; ++i) new_v[i] -= coefficients[i];
            return Polynomial(new_v);
        }

        Polynomial& operator+=(Polynomial const& tem){
            int d1 = deg(), d2 = tem.deg();
            if (d1 == -1 && d2 == -1){
                coefficients = {Bignum::ZERO};
                return *this;
            }
            std::vector<PolynomialCoeff> new_v(std::max(d1, d2) + 1);
            for(int i = 0; i < new_v.size(); ++i){
                if (i <= d1) new_v[i] += coefficients[i];
                if (i <= d2) new_v[i] += tem.coefficients[i];
            }
            coefficients = new_v;
            delete_end_zero();
            return *this;
        }

        Polynomial& operator-=(Polynomial const& tem){
            return *this += -tem;
        }

        Polynomial& operator*=(Polynomial const& tem){
            int d1 = deg(), d2 = tem.deg();
            if (d1 == -1 || d2 == -1){
                coefficients = {Bignum::ZERO};
                return *this;
            }
            std::vector<PolynomialCoeff> new_v(d1 + d2 + 1);
            for(int i = 0; i < coefficients.size(); ++i){
                for(int j = 0; j < tem.coefficients.size(); ++j){
                    new_v[i + j] += coefficients[i] * tem.coefficients[j];
                }
            }
            coefficients = new_v;
            delete_end_zero();
            return *this;
        }

        Polynomial& operator/=(PolynomialCoeff const& tem){
            for(PolynomialCoeff &x : coefficients) x /= tem;
            return *this;
        }

        std::pair<Polynomial, Polynomial> operator/(Polynomial const& temp){
            Polynomial a = *this, ans;
            while(a.deg() >= temp.deg()){
                std::vector<PolynomialCoeff> coeff(a.deg() - temp.deg());
                coeff.push_back(a.coefficients.back() / temp.coefficients.back());
                Polynomial p(coeff);
                ans += p;
                p *= temp;
                a -= p;
            }
            return {ans, a};
        }

        Polynomial& operator%=(Polynomial const& tem){
            std::pair<Polynomial, Polynomial> divmod = ((*this) / tem);
            (*this) = divmod.second;
            return *this;
        }
        friend CMP(Polynomial);
    CLASS_IN_MODULE_2(Polynomial)

    BINARY_OP(Polynomial, +) BINARY_OP(Polynomial, -) BINARY_OP(Polynomial, *) BINARY_OP(Polynomial, %)
    DEF_CMP(Polynomial)

    CMP(Polynomial){
        CHECK(a.coefficients.size(), b.coefficients.size());
        int sz = a.coefficients.size();
        for(int i = sz - 1; i >= 0; --i){
            CHECK(a.coefficients[i], b.coefficients[i]);
        }
        return 0;
    }

    CLASS_METHOD_(Deg, Polynomial)
        if (values.size()) throw new ArgumentsMismatchException("Zero arguments expected");
        SH_RET(NumberValue, instance -> deg());
    CME

    CLASS_METHOD_(Compare, Polynomial)
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
        std::shared_ptr<Polynomial> p;
        if (values[0] -> type() == Values::NUMBER) p = SHARE(Polynomial, std::vector<PolynomialCoeff>{values[0] -> asBignum()});
        else if (Polynomial::is_instance(values[0])) p = CAST(Polynomial, values[0]);
        else throw new TypeException("Polynomial expected");
        return SHARE(NumberValue, compare(*instance, *p));
    CME

    #define POLYNOMIAL_FUNCTION(cls, op) \
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected"); \
        std::shared_ptr<Polynomial> p; \
        if (values[0] -> type() == Values::NUMBER) p = SHARE(Polynomial, std::vector<PolynomialCoeff>{values[0] -> asBignum()}); \
        else if (Polynomial::is_instance(values[0])) p = CAST(Polynomial, values[0]); \
        else throw new TypeException("Polynomial expected"); \
        auto q = (*instance) op (*p);

    #define POLYNOMIAL_FUNCTION_01(cls, op) \
        CLASS_METHOD_(cls, Polynomial) \
            if (values.empty()) SH_RET(Polynomial, op (*instance)); \
            POLYNOMIAL_FUNCTION(cls, op) \
            SH_RET(Polynomial, q); \
        CME

    #define POLYNOMIAL_FUNCTION_1(cls, op) \
        CLASS_METHOD_(cls, Polynomial) \
            POLYNOMIAL_FUNCTION(cls, op) \
            SH_RET(Polynomial, q); \
        CME

    #define POLYNOMIAL_FUNCTION_2(cls, op) \
        CLASS_METHOD_(cls, Polynomial) \
            POLYNOMIAL_FUNCTION(cls, op) \
            if (values[0] -> type() == Values::NUMBER) SH_RET(Polynomial, q.first); \
            std::vector<std::shared_ptr<Value>> v = {SHARE(Polynomial, q.first), SHARE(Polynomial, q.second)}; \
            SH_RET(ArrayValue, v); \
        CME

    #define POLYNOMIAL_FUNCTION_3(cls, op) \
        CLASS_METHOD_(cls, Polynomial) \
            POLYNOMIAL_FUNCTION(cls, op) \
            return BoolValue::fromBool(q); \
        CME

    POLYNOMIAL_FUNCTION_01(Add, +)  /// x + y   x += y      +x
    POLYNOMIAL_FUNCTION_01(Sub, -)  /// x - y   x -= y      -x
    POLYNOMIAL_FUNCTION_1(Mul, *)   /// x * y   x *= y
    POLYNOMIAL_FUNCTION_2(Div, /)   /// x / y   x /= y
    POLYNOMIAL_FUNCTION_1(Mod, %)   /// x % y   x %= y
    POLYNOMIAL_FUNCTION_3(Eq, ==)   /// x == y
    POLYNOMIAL_FUNCTION_3(Ne, !=)   /// x != y
    POLYNOMIAL_FUNCTION_3(Lt, <)    /// x < y
    POLYNOMIAL_FUNCTION_3(Le, <=)   /// x <= y
    POLYNOMIAL_FUNCTION_3(Gt, >)    /// x > y
    POLYNOMIAL_FUNCTION_3(Ge, >=)   /// x >= y


    std::shared_ptr<Value> Polynomial::getDot(std::shared_ptr<Value> property){
        std::string prop = property -> asString();
        CHECK_PROP("deg", Deg);
        CHECK_PROP("+", Add);
        CHECK_PROP("-", Sub);
        CHECK_PROP("*", Mul);
        CHECK_PROP("/", Div);
        CHECK_PROP("%", Mod);
        CHECK_PROP("<=>", Compare);
        CHECK_PROP("==", Eq);
        CHECK_PROP("!=", Ne);
        CHECK_PROP("<", Lt);
        CHECK_PROP("<=", Le);
        CHECK_PROP(">", Gt);
        CHECK_PROP(">=", Ge);
        throw new UnknownPropertyException(prop);
    }
}

namespace SlavaScript::modules::math_f{
    #define MATH_FUNCTION(name) \
        CREATE_FUNCTION(name) \
            if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected"); \
            SH_RET(NumberValue, math_out:: name (values[0] -> asBignum())); \
        });

    #define MATH_BINARY_FUNCTION(name) \
        CREATE_FUNCTION(name) \
            if (values.size() != 2) throw new ArgumentsMismatchException("Two arguments expected"); \
            SH_RET(NumberValue, math_out:: name (values[0] -> asBignum(), values[1] -> asBignum())); \
        });

    MATH_FUNCTION(abs)
    MATH_FUNCTION(acos)
    MATH_FUNCTION(asin)
    MATH_FUNCTION(atan)
    MATH_BINARY_FUNCTION(atan2)
    MATH_FUNCTION(cbrt)
    MATH_FUNCTION(ceil)
    MATH_BINARY_FUNCTION(copy_sign)
    MATH_FUNCTION(cos)
    MATH_FUNCTION(cosh)
    MATH_FUNCTION(exp)
    MATH_FUNCTION(expm1)

    CREATE_FUNCTION(factorial)
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
        if (values[0] -> asDouble() < 0) throw new MathException("Bad argument for factorial");
        Bignum result = 1;
        int n = values[0] -> asDouble();
        for(int i = 2; i <= n; ++i) result *= i;
        SH_RET(NumberValue, result);
    FE

    MATH_FUNCTION(floor)
    MATH_BINARY_FUNCTION(hypot)

    CREATE_FUNCTION(interpolate)
        math_out::Polynomial result;
        for(int i = 0; i < values.size(); ++i) if (values[i] -> type() != Values::ARRAY || CAST(ArrayValue, values[i]) -> size() != 2) throw new TypeException("Expected array with len 2.");
        for(int i = 0; i < values.size(); ++i){
            math_out::Polynomial t({ CAST(ArrayValue, values[i]) -> get(1) -> asBignum() });
            for(int j = 0; j < values.size(); ++j){
                if (i != j){
                    Bignum xi = CAST(ArrayValue, values[i]) -> get(0) -> asBignum(), xj = CAST(ArrayValue, values[j]) -> get(0) -> asBignum();
                    if (xi == xj) throw new std::logic_error("Cannot used equals x");
                    t *= math_out::Polynomial({Bignum(-xj), Bignum(1)});
                    t /= xi - xj;
                }
            }
            result += t;
        }
        SH_RET(math_out::Polynomial, result.coefficients);
    FE

    MATH_FUNCTION(log)
    MATH_FUNCTION(log10)
    MATH_FUNCTION(log1p)

    MATH_BINARY_FUNCTION(pow)
    MATH_FUNCTION(round)

    CREATE_FUNCTION(signum)
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
        Bignum x = values[0] -> asBignum();
        if (x < 0) return NumberValue::M_ONE;
        else if (x > 0) return NumberValue::ONE;
        else return NumberValue::ZERO;
    FE

    MATH_FUNCTION(sin)
    MATH_FUNCTION(sinh)

    CREATE_FUNCTION(sqrt)
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
        if (values[0] -> asDouble() < 0) throw new MathException("Sqrt from negative argument");
        SH_RET(NumberValue, math_out::sqrt(values[0] -> asBignum()));
    FE

    MATH_FUNCTION(tan)
    MATH_FUNCTION(tanh)
    MATH_FUNCTION(to_degrees)
    MATH_FUNCTION(to_radians)

    DEF_CLASS_(math_out, Polynomial)
}


void Math::initConstants(){
    Variables::set("PI", SHARE(NumberValue, 3.1415926535));
    Variables::set("E", SHARE(NumberValue, 2.7182818284));
}

void Math::initFunctions(){
    UNARY_F_(math_f, abs)
    UNARY_F_(math_f, acos)
    UNARY_F_(math_f, asin)
    UNARY_F_(math_f, atan)
    BINARY_F_(math_f, atan2)
    UNARY_F_(math_f, cbrt)
    UNARY_F_(math_f, ceil)
    BINARY_F_(math_f, copy_sign)
    UNARY_F_(math_f, cos)
    UNARY_F_(math_f, cosh)
    UNARY_F_(math_f, exp)
    UNARY_F_(math_f, expm1)
    UNARY_F_(math_f, factorial)
    UNARY_F_(math_f, floor)
    BINARY_F_(math_f, hypot)
    INF_F_(math_f, interpolate)
    UNARY_F_(math_f, log)
    UNARY_F_(math_f, log10)
    UNARY_F_(math_f, log1p)
    BINARY_F_(math_f, pow)
    UNARY_F_(math_f, round)
    UNARY_F_(math_f, signum)
    UNARY_F_(math_f, sin)
    UNARY_F_(math_f, sinh)
    UNARY_F_(math_f, sqrt)
    UNARY_F_(math_f, tan)
    UNARY_F_(math_f, tanh)
    UNARY_F_(math_f, to_degrees)
    UNARY_F_(math_f, to_radians)
}

void Math::initClasses(){
    SET_CLASS_(math_f, Polynomial)
}

/*
_CRTIMP double __cdecl ldexp (double, int);
_CRTIMP double __cdecl frexp (double, int*);
_CRTIMP double __cdecl modf (double, double*);
_CRTIMP double __cdecl fmod (double, double);
*/
