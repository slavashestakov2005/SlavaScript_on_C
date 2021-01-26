#ifndef STRINGVALUE_H_INCLUDED
#define STRINGVALUE_H_INCLUDED

#include "container.h"
#include "value.h"

namespace SlavaScript{ namespace lang{
    class StringValue : public Value, Container{
    private:
        std::string value;
    public:
        StringValue(std::string value) : value(value) {}
        int size();
        void set(int index, Value* val);
        /** @return  throw: UnknownPropertyException*. */
        Value* accessDot(Value* property);
        Value* accessBracket(Value* property);
        /** @return  throw: TypeException*. */
        double asDouble();
        std::string asString();
        /** @return  throw: TypeException*. */
        bool asBool();
        /** @return  throw: TypeException*. */
        Bignum asBignum();
        Values type() const;
        operator std::string();
        ~StringValue(){}
        friend bool operator==(StringValue const& a, StringValue const& b);
        friend bool operator!=(StringValue const& a, StringValue const& b);
        friend bool operator<(StringValue const& a, StringValue const& b);
        friend bool operator<=(StringValue const& a, StringValue const& b);
        friend bool operator>(StringValue const& a, StringValue const& b);
        friend bool operator>=(StringValue const& a, StringValue const& b);
    };
}}

#endif // STRINGVALUE_H_INCLUDED
