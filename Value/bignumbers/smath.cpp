#include "bignum.h"
#include <cmath>
#include "../../Exception/mathexception.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::MathException;

namespace{
    Bignum tau("6.28318530717958647682");
    Bignum pi("3.14159265358979323846");
}

namespace SlavaScript::modules::math_out{
    Bignum sin(const Bignum& x){
        return std::sin(double(x));
    }

    Bignum cos(const Bignum& x){
        return std::cos(double(x));
    }

    Bignum tan(const Bignum& x){
        return sin(x) / cos(x);
    }

    Bignum sinh(const Bignum& x){
        return std::sinh(double(x));
    }

    Bignum cosh(const Bignum& x){
        return std::cosh(double(x));
    }

    Bignum tanh(const Bignum& x){
        return sinh(x) / cosh(x);
    }

    Bignum asin(const Bignum& x){
        if (x < -1 || x > 1) throw new MathException("For asin expected value in [-1; 1]");
        return std::asin(double(x));
    }

    Bignum acos(const Bignum& x){
        if (x < -1 || x > 1) throw new MathException("For acos expected value in [-1; 1]");
        return std::acos(double(x));
    }

    Bignum atan(const Bignum& x){
        return std::atan(double(x));
    }

    Bignum atan2(const Bignum& x, const Bignum& y){
        return std::atan2(double(x), double(y));
    }

    Bignum exp(const Bignum& x){
        return std::exp(double(x));
    }

    Bignum log(const Bignum& x){
        return std::log(double(x));
    }

    Bignum log10(const Bignum& x){
        return std::log10(double(x));
    }

    Bignum pow(const Bignum& x, const Bignum& y){
        return std::pow(double(x), double(y));
    }

    Bignum sqrt(const Bignum& x){
        return std::sqrt(double(x));
    }

    Bignum cbrt(const Bignum& x){
        return std::cbrt(double(x));
    }

    Bignum hypot(const Bignum& x, const Bignum& y){
        return std::hypot(double(x), double(y));
    }

    Bignum to_degrees(const Bignum& x){
        return x * 180 / pi;
    }

    Bignum to_radians(const Bignum& x){
        return x * pi / 180;
    }

    Bignum copy_sign(const Bignum& x, const Bignum& y){
        if (x * y < 0) return x * -1;
        return x;
    }

    Bignum expm1(const Bignum& x){
        return std::expm1(double(x));
    }

    Bignum log1p(const Bignum& x){
        return std::log1p(double(x));
    }

    Bignum ceil(const Bignum& x){
        return std::ceil(double(x));
    }

    Bignum floor(const Bignum& x){
        return std::floor(double(x));
    }

    Bignum round(const Bignum& x){
        return std::round(double(x));
    }

    Bignum abs(const Bignum& x){
        return x < 0 ? x * -1 : x;
    }
}
