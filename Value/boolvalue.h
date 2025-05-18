#pragma once

#include <Value/value.h>


namespace SlavaScript::lang {
    class BoolValue : public Value {
    private:
        bool value;
    public:
        static std::shared_ptr<BoolValue> TRUE_, FALSE_;
        static std::shared_ptr<BoolValue> fromBool(bool b);

        BoolValue(bool value);

        std::shared_ptr<Value> copy() override;
        double asDouble() override;
        std::string asString() override;
        bool asBool() override;
        Bignum asBignum() override;
        Values type() const override;
        operator std::string() override;

        friend CMP(BoolValue);
        friend EQ(BoolValue);
    };
}
