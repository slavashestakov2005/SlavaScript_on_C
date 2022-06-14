#ifndef CLASSVALUE_H_INCLUDED
#define CLASSVALUE_H_INCLUDED

#include "mapvalue.h"
#include "../Lib/class.h"

namespace SlavaScript::lang{
    class ClassValue : public Value{
    private:
        std::shared_ptr<Class> cls;
    public:
        ClassValue(std::shared_ptr<Class> cls);
        std::shared_ptr<Value> copy();

        std::shared_ptr<Value> construct(std::vector<std::shared_ptr<Value>> values);
        std::string get_name() const;
        std::shared_ptr<ClassMethod> get_function(std::string func);
        bool isExists(std::string name);

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
