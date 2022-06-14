#ifndef MODULEOBJECT_H_INCLUDED
#define MODULEOBJECT_H_INCLUDED

#include <memory>
#include "../Value/value.h"
#include "../Exception/typeexception.h"
#include "../Lib/macros.h"
#include "../Lib/function.h"
#include "../Value/stringvalue.h"
#include "../Value/functionvalue.h"
#include "../Value/objectvalue.h"
using SlavaScript::exceptions::TypeException;

namespace SlavaScript::lang{
    class ModuleObject : public Value{
    public:
        virtual std::shared_ptr<Value> copy() = 0;
        virtual std::shared_ptr<Value> accessDot(std::shared_ptr<Value> property){}
        virtual std::shared_ptr<Value> accessBracket(std::shared_ptr<Value> property){}
        virtual double asDouble() { throw new TypeException("Cannot cast class to double"); }
        virtual std::string asString() { throw new TypeException("Cannot cast class to string"); }
        virtual bool asBool() { throw new TypeException("Cannot cast class to bool"); }
        virtual Bignum asBignum() { throw new TypeException("Cannot cast class to number"); }
        virtual Values type() const { return Values::OBJECT; }
        virtual operator std::string() { throw new TypeException("Cannot cast class to string"); }
        bool isClassFromModule(){ return true; }
        virtual ~ModuleObject(){}
    };

    template<typename T>
    class ModuleObjectT : public ModuleObject{
    public:
        static bool is_instance(std::shared_ptr<Value> v){ return v -> string_type() == correct_class_name(); }
        static std::string correct_class_name() { return "ModuleObject " + T::__class_name__; }
        virtual std::string string_type() const { return correct_class_name(); }
        virtual ~ModuleObjectT(){}
    };

    template<typename T>
    std::shared_ptr<Function> get_property(std::shared_ptr<Value> value, T operation){
        std::string op = getOperator(operation);
        std::shared_ptr<Value> val;
        if (value -> type() != Values::OBJECT) throw new TypeException("Can not use " + op + " for non-class and class values");
        if (value -> isClassFromModule()) val = CAST(ModuleObject, value) -> accessDot(SHARE(StringValue, op));
        else val = CAST(ObjectValue, value) -> access(SHARE(StringValue, op));
        if (val -> type() != Values::FUNCTION) throw new TypeException("Operation " + op + " is not a function");
        std::shared_ptr<Function> func = CAST(FunctionValue, val) -> getFunction();
        return func;
    }
}

#endif // MODULEOBJECT_H_INCLUDED
