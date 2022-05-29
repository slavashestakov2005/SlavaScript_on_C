#ifndef BIGNUM_H_INCLUDED
#define BIGNUM_H_INCLUDED

#include <vector>
#include <string>
#include "../../Lib/macros.h"

namespace SlavaScript::lang{
    class UnsignedBig{
    private:
        std::vector<int> digits;
        void delete_end_zero();
    public:
        static UnsignedBig pow_10_to_n(int n);
        static const int BASE, POW;
        static const std::string EXAMPLE;
        static const UnsignedBig ZERO, ONE;

        void shift(int position);
        void shift10(int position);
        int size() const;

        UnsignedBig();
        UnsignedBig(UnsignedBig const&);
        UnsignedBig(int);
        UnsignedBig(long long);
        explicit UnsignedBig(std::string);

        UnsignedBig& operator=(UnsignedBig const& temp);
        UnsignedBig& operator=(int temp);
        UnsignedBig& operator=(long long temp);
        UnsignedBig& operator=(std::string temp);

        explicit operator bool() const;
        operator std::string() const;

        UnsignedBig& operator++();
        UnsignedBig operator++(int);
        UnsignedBig& operator--();
        UnsignedBig operator--(int);

        DECS_1(UnsignedBig)
        DECS_COND(UnsignedBig)
    };

    inline const int UnsignedBig::BASE = 1000000000, UnsignedBig::POW = 9;
    inline const std::string UnsignedBig::EXAMPLE = "000000000";
    inline const UnsignedBig UnsignedBig::ZERO = UnsignedBig(0), UnsignedBig::ONE = UnsignedBig(1);
    std::istream& operator>>(std::istream& is, UnsignedBig& temp);
    std::ostream& operator<<(std::ostream& os, const UnsignedBig& temp);
    DECS_2(UnsignedBig)

    class Bignum{
    private:
        UnsignedBig value;
        bool sign;
        int dot;
        void delete_end_zero();
    public:
        static const bool PLUS, MINUS;
        static const int EPS;
        static const Bignum ZERO, ONE;

        Bignum();
        explicit Bignum(std::string);
        Bignum(Bignum const&);
        Bignum(int);
        Bignum(long long);
        Bignum(double);

        Bignum& operator=(Bignum const& temp);
        Bignum& operator=(std::string temp);
        Bignum& operator=(int temp);
        Bignum& operator=(long long temp);
        Bignum& operator=(double temp);

        explicit operator bool() const;
        explicit operator double() const;
        operator std::string() const;

        Bignum operator-();
        Bignum operator+();
        Bignum& operator++();
        Bignum operator++(int);
        Bignum& operator--();
        Bignum operator--(int);

        DECS_1(Bignum)
        DECS_COND(Bignum)
    };

    inline const bool Bignum::PLUS = true, Bignum::MINUS = false;
    inline const int Bignum::EPS = 9;
    inline const Bignum Bignum::ZERO = Bignum(UnsignedBig::ZERO), Bignum::ONE = Bignum(UnsignedBig::ONE);
    std::istream& operator>>(std::istream& is, Bignum& temp);
    std::ostream& operator<<(std::ostream& os, const Bignum& temp);
    DECS_2(Bignum)

    class RationalBig{
    private:
        Bignum numerator, denominator;
    public:
        Bignum div() const;

        RationalBig();
        RationalBig(RationalBig const&);
        RationalBig(Bignum numerator);
        RationalBig(Bignum numerator, Bignum denominator);

        explicit operator bool() const;
        operator std::string() const;
        std::string frac() const;
        operator Bignum() const;
        RationalBig operator-();

        DEC_1(RationalBig, +=) DEC_1(RationalBig, -=) DEC_1(RationalBig, *=) DEC_1(RationalBig, /=)
        DECS_COND(RationalBig)
    };

    DEC_2(RationalBig, +) DEC_2(RationalBig, -) DEC_2(RationalBig, *) DEC_2(RationalBig, /)
}

#endif // BIGNUM_H_INCLUDED
