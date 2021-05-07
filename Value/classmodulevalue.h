#ifndef CLASSMODULEVALUE_H_INCLUDED
#define CLASSMODULEVALUE_H_INCLUDED

#include <memory>
#include "value.h"
#include "../Exception/typeexception.h"
using SlavaScript::exceptions::TypeException;

namespace SlavaScript{ namespace lang{
    #define CLASS_MODULE_FUNCTION(className, fieldType, fieldName) \
        class className : public Function { \
        private: \
            fieldType* fieldName; \
        public: \
            className(fieldType* fieldName) : fieldName(fieldName) {} \
            CREATE_MEMBER_FUNCTION

    class ClassModuleValue : public Value{
    public:
        virtual std::shared_ptr<Value> accessDot(std::shared_ptr<Value> property){}
        virtual std::shared_ptr<Value> accessBracket(std::shared_ptr<Value> property){}
        virtual double asDouble() { throw new TypeException("Cannot cast class to double"); }
        virtual std::string asString() { throw new TypeException("Cannot cast class to string"); }
        virtual bool asBool() { throw new TypeException("Cannot cast class to bool"); }
        virtual Bignum asBignum() { throw new TypeException("Cannot cast class to number"); }
        virtual Values type() const { return Values::CLASS; }
        virtual operator std::string() { throw new TypeException("Cannot cast class to string"); }
        bool isClassFromModule(){ return true; }
        virtual ~ClassModuleValue(){}
    };
}}

#endif // CLASSMODULEVALUE_H_INCLUDED
