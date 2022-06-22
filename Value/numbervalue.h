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

        NumberValue(Bignum value);
        NumberValue(std::string value);
        NumberValue(int value);
        NumberValue(long long value);
        NumberValue(size_t value);
        NumberValue(clock_t value);
        NumberValue(double value);

        std::shared_ptr<Value> copy() override;
        double asDouble() override;
        std::string asString() override;
        bool asBool() override;
        Bignum asBignum() override;
        Values type() const override;
        operator std::string() override;

        friend CMP(NumberValue);
    };

    DEC_CMP(NumberValue)
}

#endif // NUMBERVALUE_H_INCLUDED
