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
}}}

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

/*
_CRTIMP double __cdecl ceil (double);
_CRTIMP double __cdecl floor (double);
_CRTIMP double __cdecl fabs (double);

_CRTIMP double __cdecl ldexp (double, int);
_CRTIMP double __cdecl frexp (double, int*);
_CRTIMP double __cdecl modf (double, double*);
_CRTIMP double __cdecl fmod (double, double);
*/
