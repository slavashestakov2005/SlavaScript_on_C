#ifndef FUNCTIONVALUE_H_INCLUDED
#define FUNCTIONVALUE_H_INCLUDED

#include "value.h"
#include "../Lib/function.h"

namespace SlavaScript{ namespace lang{
    class FunctionValue : public Value{
    private:
        Function* value;
    public:
        FunctionValue(Function* value) : value(value) {}
        /** @return  throw: TypeException*. */
        double asDouble();
        std::string asString();
        /** @return  throw: TypeException*. */
        bool asBool();
        /** @return  throw: TypeException*. */
        Bignum asBignum();
        Values type() const;
        Function* getFunction();
        operator std::string();
        ~FunctionValue();
        /** @return  throw: TypeException*. */
        friend bool operator==(FunctionValue const& a, FunctionValue const& b);
        /** @return  throw: TypeException*. */
        friend bool operator!=(FunctionValue const& a, FunctionValue const& b);
        /** @return  throw: TypeException*. */
        friend bool operator<(FunctionValue const& a, FunctionValue const& b);
        /** @return  throw: TypeException*. */
        friend bool operator<=(FunctionValue const& a, FunctionValue const& b);
        /** @return  throw: TypeException*. */
        friend bool operator>(FunctionValue const& a, FunctionValue const& b);
        /** @return  throw: TypeException*. */
        friend bool operator>=(FunctionValue const& a, FunctionValue const& b);
    };
}}

#endif // FUNCTIONVALUE_H_INCLUDED
