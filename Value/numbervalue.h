#ifndef NUMBERVALUE_H_INCLUDED
#define NUMBERVALUE_H_INCLUDED

#include "value.h"
#include "bignumbers/bignum.h"

namespace SlavaScript{ namespace lang{
    class NumberValue : public Value{
    private:
        Bignum value;
    public:
        static NumberValue *M_ONE, *ZERO, *ONE;
        NumberValue(Bignum value) : value(value) {}
        NumberValue(std::string value) : value(Bignum(value)) {}
        NumberValue(int value) : value(Bignum(value)) {}
        /** @return  throw: std::logic_error. */
        double asDouble();
        std::string asString();
        bool asBool();
        Bignum asBignum();
        Values type() const;
        operator std::string();
        ~NumberValue(){}
        friend bool operator==(NumberValue const& a, NumberValue const& b);
        friend bool operator!=(NumberValue const& a, NumberValue const& b);
        friend bool operator<(NumberValue const& a, NumberValue const& b);
        friend bool operator<=(NumberValue const& a, NumberValue const& b);
        friend bool operator>(NumberValue const& a, NumberValue const& b);
        friend bool operator>=(NumberValue const& a, NumberValue const& b);
    };
}}

#endif // NUMBERVALUE_H_INCLUDED
