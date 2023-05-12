#ifndef SMATH_H_INCLUDED
#define SMATH_H_INCLUDED

namespace SlavaScript::modules::math_out{
    lang::Bignum sin(const lang::Bignum& x);
    lang::Bignum cos(const lang::Bignum& x);
    lang::Bignum tan(const lang::Bignum& x);
    lang::Bignum sinh(const lang::Bignum& x);
    lang::Bignum cosh(const lang::Bignum& x);
    lang::Bignum tanh(const lang::Bignum& x);
    lang::Bignum asin(const lang::Bignum& x);
    lang::Bignum acos(const lang::Bignum& x);
    lang::Bignum atan(const lang::Bignum& x);
    lang::Bignum atan2(const lang::Bignum& x, const lang::Bignum& y);
    lang::UnsignedBig binpow(const lang::UnsignedBig& x, const lang::UnsignedBig& y, const lang::UnsignedBig& mod);
    lang::Bignum exp(const lang::Bignum& x);
    lang::Bignum log(const lang::Bignum& x);
    lang::Bignum log10(const lang::Bignum& x);
    lang::Bignum pow(const lang::Bignum& x, const lang::Bignum& y);
    lang::Bignum sqrt(const lang::Bignum& x);
    lang::Bignum cbrt(const lang::Bignum& x);
    lang::Bignum hypot(const lang::Bignum& x, const lang::Bignum& y);
    lang::Bignum to_degrees(const lang::Bignum& x);
    lang::Bignum to_radians(const lang::Bignum& x);
    lang::Bignum copy_sign(const lang::Bignum& x, const lang::Bignum& y);
    lang::Bignum expm1(const lang::Bignum& x);
    lang::Bignum log1p(const lang::Bignum& x);

    lang::Bignum ceil(const lang::Bignum& x);
    lang::Bignum floor(const lang::Bignum& x);
    lang::Bignum round(const lang::Bignum& x);
    lang::Bignum abs(const lang::Bignum& x);

    /*
    _CRTIMP double __cdecl sin (double);
    _CRTIMP double __cdecl cos (double);
    _CRTIMP double __cdecl tan (double);
    _CRTIMP double __cdecl sinh (double);
    _CRTIMP double __cdecl cosh (double);
    _CRTIMP double __cdecl tanh (double);

    _CRTIMP double __cdecl asin (double);
    _CRTIMP double __cdecl acos (double);
    _CRTIMP double __cdecl atan (double);

    _CRTIMP double __cdecl atan2 (double, double);
    _CRTIMP double __cdecl exp (double);
    _CRTIMP double __cdecl log (double);
    _CRTIMP double __cdecl log10 (double);
    _CRTIMP	double __cdecl pow (double, double);
    _CRTIMP double __cdecl sqrt (double);
    _CRTIMP double __cdecl ceil (double);
    _CRTIMP double __cdecl floor (double);
    _CRTIMP double __cdecl fabs (double);

    _CRTIMP double __cdecl ldexp (double, int);
    _CRTIMP double __cdecl frexp (double, int*);
    _CRTIMP double __cdecl modf (double, double*);
    _CRTIMP double __cdecl fmod (double, double);
    */
}

#endif // SMATH_H_INCLUDED
