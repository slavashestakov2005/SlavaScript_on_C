#ifndef CLASSVALUE_H_INCLUDED
#define CLASSVALUE_H_INCLUDED

#include "mapvalue.h"
#include "../Lib/classmethod.h"

namespace SlavaScript::lang{
    class ClassValue : public Value{
    private:
        std::string name;
        ClassDeclarationsStatement* statement;
    public:
        ClassValue(ClassDeclarationsStatement* statement);
        std::shared_ptr<Value> copy();

        std::shared_ptr<Value> construct(std::vector<std::shared_ptr<Value>> values);
        std::string get_name();

        double asDouble();
        std::string asString();
        bool asBool();
        Bignum asBignum();
        Values type() const;
        std::string string_type() const;
        operator std::string();
        ~ClassValue(){}

        DECS_COND(ClassValue)
    };
}

#endif // CLASSVALUE_H_INCLUDED
