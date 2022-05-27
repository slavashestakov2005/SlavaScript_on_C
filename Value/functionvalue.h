#ifndef FUNCTIONVALUE_H_INCLUDED
#define FUNCTIONVALUE_H_INCLUDED

#include "value.h"
#include "../Lib/function.h"

namespace SlavaScript::lang{
    class FunctionValue : public Value{
    private:
        std::shared_ptr<Function> value;
    public:
        FunctionValue(std::shared_ptr<Function> value) : value(value) {}
        FunctionValue(Function* value) : value(std::shared_ptr<Function>(value)) {}
        std::shared_ptr<Value> copy();

        std::shared_ptr<Function> getFunction();

        double asDouble();
        std::string asString();
        bool asBool();
        Bignum asBignum();
        Values type() const;
        operator std::string();
        ~FunctionValue(){}

        DECS_COND(FunctionValue)
    };
}

#endif // FUNCTIONVALUE_H_INCLUDED
