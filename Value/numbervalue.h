#pragma once

#include <ctime>

#include <Value/bignumbers/bignum.h>
#include <Value/value.h>


namespace SlavaScript::lang {
    class NumberValue : public Value {
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
        NumberValue(std::strong_ordering val);

        std::shared_ptr<Value> copy() override;
        double asDouble() override;
        std::string asString() override;
        bool asBool() override;
        Bignum asBignum() override;
        Values type() const override;
        operator std::string() override;

        friend CMP(NumberValue);
        friend EQ(NumberValue);
    };
}
