#ifndef FUNCTIONVALUE_H_INCLUDED
#define FUNCTIONVALUE_H_INCLUDED

#include "value.h"
#include "../Lib/function.h"

namespace SlavaScript::lang{
    class FunctionValue : public Value{
    private:
        std::shared_ptr<Function> value;
    public:
        FunctionValue(std::shared_ptr<Function> value);
        FunctionValue(Function* value);

        std::shared_ptr<Function> getFunction();

        std::shared_ptr<Value> copy() override;
        double asDouble() override;
        std::string asString() override;
        bool asBool() override;
        Bignum asBignum() override;
        Values type() const override;
        operator std::string() override;

        friend CMP(FunctionValue);
        friend EQ(FunctionValue);
    };
}

#endif // FUNCTIONVALUE_H_INCLUDED
