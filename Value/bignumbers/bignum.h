#ifndef BIGNUM_H_INCLUDED
#define BIGNUM_H_INCLUDED

#include <vector>
#include <string>

namespace SlavaScript{ namespace lang{
    class Bignum{
    private:
        std::vector<int> mas;
        const int BASE = 1000000000;
        const int POW = 9;
        bool neg;
        int exponent;
        int tochnost;
        bool isCorect(std::string);
        void delete_end_zero();
    public:
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
        operator std::string() const;
        explicit operator double() const;
        void shift(int n);
        void setTochnost(int n);
        Bignum operator-();
        Bignum operator+();
        Bignum& operator++();
        Bignum operator++(int);
        Bignum& operator--();
        Bignum operator--(int);
        //
        Bignum& operator+=(Bignum const& temp);
        Bignum& operator-=(Bignum const& temp);
        Bignum& operator*=(Bignum const& temp);
        /**
            Operator /= can @throw  std::domain_error("Division by zero").
        **/
        Bignum& operator/=(Bignum const& temp);
        /**
            Operator %= can @throw  std::domain_error("Modulo by zero").
        **/
        Bignum& operator%=(Bignum const& temp);
        //
        friend bool operator==(Bignum const& a, Bignum const& b);
        friend bool operator!=(Bignum const& a, Bignum const& b);
        friend bool operator<(Bignum const& a, Bignum const& b);
        friend bool operator>(Bignum const& a, Bignum const& b);
        friend bool operator<=(Bignum const& a, Bignum const& b);
        friend bool operator>=(Bignum const& a, Bignum const& b);
    };

    std::istream& operator>>(std::istream& is, Bignum& temp);
    std::ostream& operator<<(std::ostream& os, const Bignum& temp);
    Bignum& operator+(Bignum a, Bignum const& b);
    Bignum& operator-(Bignum a, Bignum const& b);
    Bignum& operator*(Bignum a, Bignum const& b);
    Bignum& operator/(Bignum a, Bignum const& b);
    Bignum& operator%(Bignum a, Bignum const& b);
}}

#endif // BIGNUM_H_INCLUDED
