#ifndef UTILS_IMPL_H_INCLUDED
#define UTILS_IMPL_H_INCLUDED

#include "../Value/functionvalue.h"
#include "../Value/stringvalue.h"

namespace SlavaScript::lang{
    template<typename T>
    std::shared_ptr<Function> get_property(std::shared_ptr<Value> value, T operation){
        std::string op = getOperator(operation);
        if (value -> type() != Values::OBJECT) throw new TypeException("Can not use " + op + " for non-class and class values");
        std::shared_ptr<Value> val = value -> getDot(SHARE(StringValue, op));
        if (val -> type() != Values::FUNCTION) throw new TypeException("Operation " + op + " is not a function");
        std::shared_ptr<Function> func = CAST(FunctionValue, val) -> getFunction();
        return func;
    }
}

#endif // UTILS_IMPL_H_INCLUDED
