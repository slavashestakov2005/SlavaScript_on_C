#ifndef CLASSVALUE_H_INCLUDED
#define CLASSVALUE_H_INCLUDED

#include "mapvalue.h"
#include "../Lib/classmethod.h"

namespace SlavaScript{ namespace lang{
    class ClassValue : public Value{
    private:
        std::string className;
        MapValue* thisMap = new MapValue(1);
        ClassMethod* constructor = nullptr;
    public:
        ClassValue(std::string className);
        MapValue* getThisMap();
        void addField(std::string name, Value* value);
        void addMethod(std::string name, ClassMethod* method);
        void callConstructor(std::vector<Value*> values);
        Value* access(Value* value);
        /** @return  throw: std::logic_error*. */
        void set(Value* key, Value* value);
        /** @return  throw: std::logic_error*. */
        Value* get(Value* key);
        /** @return  throw: TypeException*. */
        double asDouble();
        std::string asString();
        /** @return  throw: TypeException*. */
        bool asBool();
        /** @return  throw: TypeException*. */
        Bignum asBignum();
        Values type() const;
        operator std::string();
        ~ClassValue();
        friend bool operator==(ClassValue const& a, ClassValue const& b);
        friend bool operator!=(ClassValue const& a, ClassValue const& b);
        friend bool operator<(ClassValue const& a, ClassValue const& b);
        friend bool operator<=(ClassValue const& a, ClassValue const& b);
        friend bool operator>(ClassValue const& a, ClassValue const& b);
        friend bool operator>=(ClassValue const& a, ClassValue const& b);
    };
}}

#endif // CLASSVALUE_H_INCLUDED
