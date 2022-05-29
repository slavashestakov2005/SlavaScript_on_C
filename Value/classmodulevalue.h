#ifndef CLASSMODULEVALUE_H_INCLUDED
#define CLASSMODULEVALUE_H_INCLUDED

#include <memory>
#include "value.h"
#include "../Exception/typeexception.h"
#include "../Lib/macros.h"
#include "../Lib/function.h"
#include "stringvalue.h"
#include "functionvalue.h"
using SlavaScript::exceptions::TypeException;

namespace SlavaScript::lang{
    class ClassModuleValue : public Value{
    public:
        virtual std::shared_ptr<Value> copy() = 0;
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

    template<typename T>
    class ClassModuleValueT : public ClassModuleValue{
    public:
        static bool is_instance(std::shared_ptr<Value> v){ return v -> string_type() == correct_class_name(); }
        static std::string correct_class_name() { return "ModuleClass " + T::__class_name__; }
        virtual std::string string_type() const { return correct_class_name(); }
        virtual ~ClassModuleValueT(){}
    };

    template<typename T>
    std::shared_ptr<Function> get_property(std::shared_ptr<Value> value, T operation){
        std::string op = getOperator(operation);
        std::shared_ptr<Value> val = CAST(ClassModuleValue, value) -> accessDot(SHARE(StringValue, op));
        if (val -> type() != Values::FUNCTION) throw new TypeException("Operation " + op + " is not a function");
        std::shared_ptr<Function> func = CAST(FunctionValue, val) -> getFunction();
        return func;
    }
}

#endif // CLASSMODULEVALUE_H_INCLUDED
