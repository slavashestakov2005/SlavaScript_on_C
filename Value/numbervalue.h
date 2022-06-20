#ifndef NUMBERVALUE_H_INCLUDED
#define NUMBERVALUE_H_INCLUDED

#include "value.h"
#include "bignumbers/bignum.h"
#include <ctime>
#include <memory>

namespace SlavaScript::lang{
    class NumberValue : public Value{
    private:
        Bignum value;
    public:
        static std::shared_ptr<NumberValue> M_ONE, ZERO, ONE;

        NumberValue(Bignum value) : value(value) {}
        NumberValue(std::string value) : value(Bignum(value)) {}
        NumberValue(int value) : value(Bignum(value)) {}
        NumberValue(long long value) : value(Bignum(value)) {}
        NumberValue(size_t value) : value(Bignum((long long) value)) {}
        NumberValue(clock_t value) : value(Bignum((long long) value)) {}
        NumberValue(double value) : value(Bignum(value)) {}
        std::shared_ptr<Value> copy();

        double asDouble();
        std::string asString();
        bool asBool();
        Bignum asBignum();
        Values type() const;
        operator std::string();
        ~NumberValue(){}

        friend CMP(NumberValue);
    };

    DEC_CMP(NumberValue)
}

#endif // NUMBERVALUE_H_INCLUDED
