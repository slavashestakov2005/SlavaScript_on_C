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

        void set(int index, std::shared_ptr<Value> val);

        int size() const;
        std::shared_ptr<Value> accessDot(std::shared_ptr<Value> property);
        std::shared_ptr<Value> accessBracket(std::shared_ptr<Value> property);

        double asDouble();
        std::string asString();
        bool asBool();
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
