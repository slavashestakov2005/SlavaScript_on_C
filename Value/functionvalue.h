#ifndef FUNCTIONVALUE_H_INCLUDED
#define FUNCTIONVALUE_H_INCLUDED

#include "value.h"
#include "../Lib/function.h"

namespace SlavaScript{ namespace lang{
    class FunctionValue : public Value{
    private:
        std::shared_ptr<Function> value;
    public:
        FunctionValue(std::shared_ptr<Function> value) : value(value) {}
        FunctionValue(Function* value) : value(std::shared_ptr<Function>(value)) {}

        std::shared_ptr<Function> getFunction();

        double asDouble();
        std::string asString();
        bool asBool();
        Bignum asBignum();
        Values type() const;
        operator std::string();
        ~FunctionValue(){}

        friend bool operator==(FunctionValue const& a, FunctionValue const& b);
        friend bool operator!=(FunctionValue const& a, FunctionValue const& b);
        friend bool operator<(FunctionValue const& a, FunctionValue const& b);
        friend bool operator<=(FunctionValue const& a, FunctionValue const& b);
        friend bool operator>(FunctionValue const& a, FunctionValue const& b);
        friend bool operator>=(FunctionValue const& a, FunctionValue const& b);
    };
}}

#endif // FUNCTIONVALUE_H_INCLUDED
