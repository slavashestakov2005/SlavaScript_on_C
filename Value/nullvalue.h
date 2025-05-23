#pragma once

#include <Value/value.h>


namespace SlavaScript::lang {
    class NullValue : public Value {
    public:
        static std::shared_ptr<NullValue> NULL_;

        NullValue() {}

        std::shared_ptr<Value> copy() override;
        double asDouble() override;
        std::string asString() override;
        bool asBool() override;
        Bignum asBignum() override;
        Values type() const override;
        operator std::string() override;

        friend CMP(NullValue);
        friend EQ(NullValue);
    };
}
