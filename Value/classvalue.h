#ifndef CLASSVALUE_H_INCLUDED
#define CLASSVALUE_H_INCLUDED

#include "mapvalue.h"
#include "../Lib/classmethod.h"

namespace SlavaScript{ namespace lang{
    class ClassValue : public Value{
    private:
        std::string className;
        std::shared_ptr<MapValue> thisMap = SHARE(MapValue, 1);
        std::shared_ptr<ClassMethod> constructor = nullptr;
    public:
        ClassValue(std::string className);
        std::shared_ptr<Value> copy();

        std::shared_ptr<MapValue> getThisMap();
        void addField(std::string name, std::shared_ptr<Value> value);
        void addMethod(std::string name, std::shared_ptr<ClassMethod> method);
        void callConstructor(std::vector<std::shared_ptr<Value>> values);
        std::shared_ptr<Value> access(std::shared_ptr<Value> value);
        void set(std::shared_ptr<Value> key, std::shared_ptr<Value> value);
        std::shared_ptr<Value> get(std::shared_ptr<Value> key);

        double asDouble();
        std::string asString();
        bool asBool();
        Bignum asBignum();
        Values type() const;
        operator std::string();
        ~ClassValue(){}

        DECS_COND(ClassValue)
    };
}}

#endif // CLASSVALUE_H_INCLUDED
