#ifndef UTILS_IMPL_H_INCLUDED
#define UTILS_IMPL_H_INCLUDED

#include "../Exception/exceptions.h"
#include "../Value/functionvalue.h"
#include "../Value/stringvalue.h"

namespace SlavaScript::lang{
    template<typename T>
    std::shared_ptr<Function> get_property(std::shared_ptr<Value> value, T operation){
        std::string op = getOperator(operation);
        argType(Values::OBJECT, value, "Can not use " + op + " for non-class and class values");
        std::shared_ptr<Value> val = value -> getDot(SHARE(StringValue, op));
        argType(Values::FUNCTION, val, "Operation " + op + " is not a function");
        std::shared_ptr<Function> func = CAST(FunctionValue, val) -> getFunction();
        return func;
    }
}

#endif // UTILS_IMPL_H_INCLUDED
