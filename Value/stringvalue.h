#ifndef STRINGVALUE_H_INCLUDED
#define STRINGVALUE_H_INCLUDED

#include "container.h"
#include "value.h"

namespace SlavaScript{ namespace lang{
    class StringValue : public Value, Container<std::string>{
    private:
        std::string value;
    public:
        StringValue(std::string value) : value(value) {}
        std::shared_ptr<Value> copy();

        void set(int index, std::shared_ptr<Value> val);

        int size() const;
        std::shared_ptr<Value> accessDot(std::shared_ptr<Value> property);
        std::shared_ptr<Value> accessBracket(std::shared_ptr<Value> property);
        std::string::iterator begin();
        std::string::iterator end();

        double asDouble();
        std::string asString();
        bool asBool();
        Bignum asBignum();
        Values type() const;
        operator std::string();
        ~StringValue(){}

        DECS_COND(StringValue)
    };
}}

#endif // STRINGVALUE_H_INCLUDED
