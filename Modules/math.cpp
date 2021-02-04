#include "math.h"
#include <cmath>
#include "../Lib/function.h"
#include "../Value/numbervalue.h"
#include "../Lib/functions.h"
#include "../Lib/variables.h"
#include "../Exception/argumentsmismatchexception.h"
#include "../Exception/mathexception.h"
#include "../Value/bignumbers/smath.h"

using namespace SlavaScript::lang;
using namespace SlavaScript::modules::math_f;
using SlavaScript::modules::Math;
using SlavaScript::exceptions::ArgumentsMismatchException;
using SlavaScript::exceptions::MathException;

namespace SlavaScript{ namespace modules{ namespace math_f{
    Function* abs = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
        return new NumberValue(math_out::abs(values[0] -> asBignum()));
    });

    Function* acos = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
        return new NumberValue(math_out::acos(values[0] -> asBignum()));
    });

    Function* asin = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
        return new NumberValue(math_out::sin(values[0] -> asBignum()));
    });

    Function* atan = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
        return new NumberValue(math_out::atan(values[0] -> asBignum()));
    });

    Function* atan2 = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 2) throw new ArgumentsMismatchException("Two argument expected");
        return new NumberValue(math_out::atan2(values[0] -> asBignum(), values[1] -> asBignum()));
    });

    Function* cbrt = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
        return new NumberValue(math_out::cbrt(values[0] -> asBignum()));
    });

    Function* ceil = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
        return new NumberValue(math_out::ceil(values[0] -> asBignum()));
    });

    Function* copy_sign = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 2) throw new ArgumentsMismatchException("One argument expected");
        return new NumberValue(math_out::copy_sign(values[0] -> asBignum(), values[1] -> asBignum()));
    });

    Function* cos = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
        return new NumberValue(math_out::cos(values[0] -> asBignum()));
    });

    Function* cosh = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
        return new NumberValue(math_out::cosh(values[0] -> asBignum()));
    });

    Function* exp = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
        return new NumberValue(math_out::exp(values[0] -> asBignum()));
    });

    Function* expm1 = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
        return new NumberValue(math_out::expm1(values[0] -> asBignum()));
    });

    Function* factorial = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
        if (values[0] -> asDouble() < 0) throw new MathException("Bad argument for factorial");
        Bignum result = 1;
        int n = values[0] -> asDouble();
        for(int i = 2; i <= n; ++i) result *= i;
        return new NumberValue(result);
    });

    Function* floor = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
        return new NumberValue(math_out::floor(values[0] -> asBignum()));
    });

    Function* hypot = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 2) throw new ArgumentsMismatchException("One argument expected");
        return new NumberValue(math_out::hypot(values[0] -> asBignum(), values[1] -> asBignum()));
    });

    Function* log = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
        return new NumberValue(math_out::log(values[0] -> asBignum()));
    });

    Function* log10 = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
        return new NumberValue(math_out::log10(values[0] -> asBignum()));
    });

    Function* log1p = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
        return new NumberValue(math_out::log1p(values[0] -> asBignum()));
    });

    Function* pow = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 2) throw new ArgumentsMismatchException("Two argument expected");
        return new NumberValue(math_out::pow(values[0] -> asBignum(), values[1] -> asBignum()));
    });

    Function* round = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
        return new NumberValue(math_out::round(values[0] -> asBignum()));
    });

    Function* signum = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
        Bignum x = values[0] -> asBignum();
        if (x < 0) return NumberValue::M_ONE;
        else if (x > 0) return NumberValue::ONE;
        else return NumberValue::ZERO;
    });

    Function* sin = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
        return new NumberValue(math_out::sin(values[0] -> asBignum()));
    });

    Function* sinh = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
        return new NumberValue(math_out::sinh(values[0] -> asBignum()));
    });

    Function* sqrt = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
        if (values[0] -> asDouble() < 0) throw new MathException("Sqrt from negative argument");
        return new NumberValue(math_out::sqrt(values[0] -> asBignum()));
    });

    Function* tan = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
        return new NumberValue(math_out::tan(values[0] -> asBignum()));
    });

    Function* tanh = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
        return new NumberValue(math_out::tanh(values[0] -> asBignum()));
    });

    Function* to_degrees = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
        return new NumberValue(math_out::to_degrees(values[0] -> asBignum()));
    });

    Function* to_radians = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw new ArgumentsMismatchException("One argument expected");
        return new NumberValue(math_out::to_radians(values[0] -> asBignum()));
    });
}}}

void Math::initConstants(){
    Variables::set("PI", new NumberValue(3.1415926535));
    Variables::set("E", new NumberValue(2.7182818284));
}

void Math::initFunctions(){
    Functions::set("abs", math_f::abs);
    Functions::set("acos", math_f::acos);
    Functions::set("asin", math_f::asin);
    Functions::set("atan", math_f::atan);
    Functions::set("atan2", math_f::atan2);
    Functions::set("cbrt", math_f::cbrt);
    Functions::set("ceil", math_f::ceil);
    Functions::set("copy_sign", math_f::copy_sign);
    Functions::set("cos", math_f::cos);
    Functions::set("cosh", math_f::cosh);
    Functions::set("exp", math_f::exp);
    Functions::set("expm1", math_f::expm1);
    Functions::set("factorial", math_f::factorial);
    Functions::set("floor", math_f::floor);
    Functions::set("hypot", math_f::hypot);
    Functions::set("log", math_f::log);
    Functions::set("log10", math_f::log10);
    Functions::set("log1p", math_f::log1p);
    Functions::set("pow", math_f::pow);
    Functions::set("round", math_f::round);
    Functions::set("signum", math_f::signum);
    Functions::set("sin", math_f::sin);
    Functions::set("sinh", math_f::sinh);
    Functions::set("sqrt", math_f::sqrt);
    Functions::set("tan", math_f::tan);
    Functions::set("tanh", math_f::tanh);
    Functions::set("to_degrees", math_f::to_degrees);
    Functions::set("to_radians", math_f::to_radians);
}

/*
_CRTIMP double __cdecl ceil (double);
_CRTIMP double __cdecl floor (double);
_CRTIMP double __cdecl fabs (double);

_CRTIMP double __cdecl ldexp (double, int);
_CRTIMP double __cdecl frexp (double, int*);
_CRTIMP double __cdecl modf (double, double*);
_CRTIMP double __cdecl fmod (double, double);
*/
