#ifndef BOOLVALUE_H_INCLUDED
#define BOOLVALUE_H_INCLUDED

#include "value.h"
#include <memory>

namespace SlavaScript::lang{
    class BoolValue : public Value{
    private:
        bool value;
    public:
        static std::shared_ptr<BoolValue> TRUE_, FALSE_;
        static std::shared_ptr<BoolValue> fromBool(bool b);

        BoolValue(bool value) : value(value) {}
        std::shared_ptr<Value> copy();

        double asDouble();
        std::string asString();
        bool asBool();
        Bignum asBignum();
        Values type() const;
        operator std::string();
        ~BoolValue(){}

        friend CMP(BoolValue);
    };

    DEC_CMP(BoolValue)
}

#endif // BOOLVALUE_H_INCLUDED
