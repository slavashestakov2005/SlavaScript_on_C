#include "math.h"
#include "../Exception/exceptions.h"
#include "../Lib/classes.h"
#include "../Lib/classmethod.h"
#include "../Lib/moduleclass.h"
#include "../Lib/moduleobject.h"
#include "../Lib/utils.h"
#include "../Value/arrayvalue.h"
#include "../Value/bignumbers/smath.h"
#include "../Value/boolvalue.h"
#include "../Value/numbervalue.h"

using namespace SlavaScript::lang;
using namespace SlavaScript::modules::math_f;
using SlavaScript::modules::Math;
using SlavaScript::exceptions::MathException;
using SlavaScript::exceptions::TypeException;
using SlavaScript::exceptions::UnknownPropertyException;


namespace SlavaScript::modules::math_out{
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
            SH_RET(Polynomial, coefficients);
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
        friend EQ(Polynomial);
    CLASS_IN_MODULE_2(Polynomial)

    DEF_OP_OUT(Polynomial, +)
    DEF_OP_OUT(Polynomial, -)
    DEF_OP_OUT(Polynomial, *)
    DEF_OP_OUT(Polynomial, %)
    DEF_EQ(Polynomial)

    CMP(Polynomial){
        CHECK(a.coefficients.size(), b.coefficients.size());
        int sz = a.coefficients.size();
        for(int i = sz - 1; i >= 0; --i){
            CHECK(a.coefficients[i], b.coefficients[i]);
        }
        return std::strong_ordering::equal;
    }

    CLASS_METHOD_PTR(Deg, Polynomial)
        argsCount(0, values.size());
        SH_RET(NumberValue, instance -> deg());
    CME

    CLASS_METHOD_PTR(Compare, Polynomial)
        argsCount(1, values.size());
        std::shared_ptr<Polynomial> p;
        if (values[0] -> type() == Values::NUMBER) p = SHARE(Polynomial, std::vector<PolynomialCoeff>{values[0] -> asBignum()});
        else if (Polynomial::is_instance(values[0])) p = CAST(Polynomial, values[0]);
        else throw TypeException("Polynomial expected");
        SH_RET(NumberValue, *instance <=> *p);
    CME

    #define POLYNOMIAL_FUNCTION(cls, op) \
        argsCount(1, values.size()); \
        std::shared_ptr<Polynomial> p; \
        if (values[0] -> type() == Values::NUMBER) p = SHARE(Polynomial, std::vector<PolynomialCoeff>{values[0] -> asBignum()}); \
        else if (Polynomial::is_instance(values[0])) p = CAST(Polynomial, values[0]); \
        else throw TypeException("Polynomial expected"); \
        auto q = (*instance) op (*p);

    #define POLYNOMIAL_FUNCTION_01(cls, op) \
        CLASS_METHOD_PTR(cls, Polynomial) \
            if (values.empty()) SH_RET(Polynomial, op (*instance)); \
            POLYNOMIAL_FUNCTION(cls, op) \
            SH_RET(Polynomial, q); \
        CME

    #define POLYNOMIAL_FUNCTION_1(cls, op) \
        CLASS_METHOD_PTR(cls, Polynomial) \
            POLYNOMIAL_FUNCTION(cls, op) \
            SH_RET(Polynomial, q); \
        CME

    #define POLYNOMIAL_FUNCTION_2(cls, op) \
        CLASS_METHOD_PTR(cls, Polynomial) \
            POLYNOMIAL_FUNCTION(cls, op) \
            if (values[0] -> type() == Values::NUMBER) SH_RET(Polynomial, q.first); \
            std::vector<std::shared_ptr<Value>> v = {SHARE(Polynomial, q.first), SHARE(Polynomial, q.second)}; \
            SH_RET(ArrayValue, v); \
        CME

    #define POLYNOMIAL_FUNCTION_3(cls, op) \
        CLASS_METHOD_PTR(cls, Polynomial) \
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
        ADD_METHOD_PTR("deg", Deg);
        ADD_METHOD_PTR("+", Add);
        ADD_METHOD_PTR("-", Sub);
        ADD_METHOD_PTR("*", Mul);
        ADD_METHOD_PTR("/", Div);
        ADD_METHOD_PTR("%", Mod);
        ADD_METHOD_PTR("<=>", Compare);
        ADD_METHOD_PTR("==", Eq);
        ADD_METHOD_PTR("!=", Ne);
        ADD_METHOD_PTR("<", Lt);
        ADD_METHOD_PTR("<=", Le);
        ADD_METHOD_PTR(">", Gt);
        ADD_METHOD_PTR(">=", Ge);
        throw UnknownPropertyException(prop);
    }
}

namespace SlavaScript::modules::math_f{
    #define MATH_FUNCTION(name) \
        CREATE_FUNCTION(name) \
            argsCount(1, values.size()); \
            SH_RET(NumberValue, math_out:: name (values[0] -> asBignum())); \
        });

    #define MATH_BINARY_FUNCTION(name) \
        CREATE_FUNCTION(name) \
            argsCount(2, values.size()); \
            SH_RET(NumberValue, math_out:: name (values[0] -> asBignum(), values[1] -> asBignum())); \
        });

    MATH_FUNCTION(abs)
    MATH_FUNCTION(acos)
    MATH_FUNCTION(asin)
    MATH_FUNCTION(atan)
    CREATE_FUNCTION(binpow)
        argsCount(2, 3, values.size());
        Bignum x = values[0] -> asBignum(), y = values[1] -> asBignum(), mod = Bignum::ZERO;
        if (values.size() > 2) mod = values[2] -> asBignum();
        SH_RET(NumberValue, math_out::binpow(x.toUnsigned(), y.toUnsigned(), mod.toUnsigned()));
    FE

    MATH_BINARY_FUNCTION(atan2)
    MATH_FUNCTION(cbrt)
    MATH_FUNCTION(ceil)
    MATH_BINARY_FUNCTION(copy_sign)
    MATH_FUNCTION(cos)
    MATH_FUNCTION(cosh)
    MATH_FUNCTION(exp)
    MATH_FUNCTION(expm1)

    CREATE_FUNCTION(factorial)
        argsCount(1, values.size());
        if (values[0] -> asDouble() < 0) throw MathException("Bad argument for factorial");
        Bignum result = 1;
        int n = values[0] -> asDouble();
        for(int i = 2; i <= n; ++i) result *= i;
        SH_RET(NumberValue, result);
    FE

    MATH_FUNCTION(floor)
    MATH_BINARY_FUNCTION(hypot)

    CREATE_FUNCTION(interpolate)
        math_out::Polynomial result;
        for(int i = 0; i < values.size(); ++i){
            argType(Values::ARRAY, values[i]);
            if (CAST(ArrayValue, values[i]) -> size() != 2) throw TypeException("Expected array with len 2.");
        }
        for(int i = 0; i < values.size(); ++i){
            math_out::Polynomial t({ CAST(ArrayValue, values[i]) -> get(1) -> asBignum() });
            for(int j = 0; j < values.size(); ++j){
                if (i != j){
                    Bignum xi = CAST(ArrayValue, values[i]) -> get(0) -> asBignum(), xj = CAST(ArrayValue, values[j]) -> get(0) -> asBignum();
                    if (xi == xj) throw MathException("Cannot used equals x for interpolate");
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
        argsCount(1, values.size());
        Bignum x = values[0] -> asBignum();
        if (x < 0) return NumberValue::M_ONE;
        else if (x > 0) return NumberValue::ONE;
        else return NumberValue::ZERO;
    FE

    MATH_FUNCTION(sin)
    MATH_FUNCTION(sinh)

    CREATE_FUNCTION(sqrt)
        argsCount(1, values.size());
        if (values[0] -> asDouble() < 0) throw MathException("Sqrt from negative argument");
        SH_RET(NumberValue, math_out::sqrt(values[0] -> asBignum()));
    FE

    MATH_FUNCTION(tan)
    MATH_FUNCTION(tanh)
    MATH_FUNCTION(to_degrees)
    MATH_FUNCTION(to_radians)

    MCLASS_DEF(math_out, Polynomial)
}


void Math::initConstants(){
    Variables::set("PI", SHARE(NumberValue, 3.1415926535));
    Variables::set("E", SHARE(NumberValue, 2.7182818284));
}

void Math::initFunctions(){
    MFUNC_UNARY(math_f, abs)
    MFUNC_UNARY(math_f, acos)
    MFUNC_UNARY(math_f, asin)
    MFUNC_UNARY(math_f, atan)
    MFUNC_BINARY(math_f, atan2)
    MFUNC_INFO(math_f, binpow, ArgumentsInfo(2, 1, 0))
    MFUNC_UNARY(math_f, cbrt)
    MFUNC_UNARY(math_f, ceil)
    MFUNC_BINARY(math_f, copy_sign)
    MFUNC_UNARY(math_f, cos)
    MFUNC_UNARY(math_f, cosh)
    MFUNC_UNARY(math_f, exp)
    MFUNC_UNARY(math_f, expm1)
    MFUNC_UNARY(math_f, factorial)
    MFUNC_UNARY(math_f, floor)
    MFUNC_BINARY(math_f, hypot)
    MFUNC_INF(math_f, interpolate)
    MFUNC_UNARY(math_f, log)
    MFUNC_UNARY(math_f, log10)
    MFUNC_UNARY(math_f, log1p)
    MFUNC_BINARY(math_f, pow)
    MFUNC_UNARY(math_f, round)
    MFUNC_UNARY(math_f, signum)
    MFUNC_UNARY(math_f, sin)
    MFUNC_UNARY(math_f, sinh)
    MFUNC_UNARY(math_f, sqrt)
    MFUNC_UNARY(math_f, tan)
    MFUNC_UNARY(math_f, tanh)
    MFUNC_UNARY(math_f, to_degrees)
    MFUNC_UNARY(math_f, to_radians)
}

void Math::initClasses(){
    MCLASS_SET(math_f, Polynomial)
}

/*
_CRTIMP double __cdecl ldexp (double, int);
_CRTIMP double __cdecl frexp (double, int*);
_CRTIMP double __cdecl modf (double, double*);
_CRTIMP double __cdecl fmod (double, double);
*/
