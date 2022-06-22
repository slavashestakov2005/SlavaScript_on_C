#ifndef NULLVALUE_H_INCLUDED
#define NULLVALUE_H_INCLUDED

#include <memory>
#include "value.h"

namespace SlavaScript::lang{
    class NullValue : public Value{
    public:
        static std::shared_ptr<NullValue> NULL_;

        NullValue(){}

        std::shared_ptr<Value> copy() override;
        double asDouble() override;
        std::string asString() override;
        bool asBool() override;
        Bignum asBignum() override;
        Values type() const override;
        operator std::string() override;

        friend CMP(NullValue);
    };

    DEC_CMP(NullValue)
}

#endif // NULLVALUE_H_INCLUDED
