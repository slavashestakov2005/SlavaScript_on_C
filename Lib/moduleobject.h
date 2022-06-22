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
        double asDouble() override{ throw new TypeException("Cannot cast object to double"); }
        std::string asString() override{ throw new TypeException("Cannot cast object to string"); }
        bool asBool() override{ throw new TypeException("Cannot cast object to bool"); }
        Bignum asBignum() override{ throw new TypeException("Cannot cast object to number"); }
        Values type() const override{ return Values::OBJECT; }
        operator std::string() override{ throw new TypeException("Cannot cast object to string"); }

        ~ModuleObject(){}
    };

    template<typename T>
    class ModuleObjectT : public ModuleObject{
    public:
        static bool is_instance(std::shared_ptr<Value> v){ return v -> stringType() == correct_class_name(); }
        static std::string correct_class_name() { return "ModuleObject " + T::__class_name__; }

        std::string stringType() const override { return correct_class_name(); }

        ~ModuleObjectT(){}
    };
}

#endif // MODULEOBJECT_H_INCLUDED
