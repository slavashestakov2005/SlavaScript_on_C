#ifndef NULLVALUE_H_INCLUDED
#define NULLVALUE_H_INCLUDED

#include <memory>
#include "value.h"

namespace SlavaScript::lang{
    class NullValue : public Value{
    public:
        static std::shared_ptr<NullValue> NULL_;

        NullValue(){}
        std::shared_ptr<Value> copy();

        double asDouble();
        std::string asString();
        bool asBool();
        Bignum asBignum();
        Values type() const;
        operator std::string();
        ~NullValue(){}

        DECS_COND(NullValue)
    };
}

#endif // NULLVALUE_H_INCLUDED
