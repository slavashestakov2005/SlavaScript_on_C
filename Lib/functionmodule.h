#ifndef FUNCTIONMODULE_H_INCLUDED
#define FUNCTIONMODULE_H_INCLUDED

#include <functional>
#include "function.h"

namespace SlavaScript{ namespace lang{
    using function_type = std::function<Value*(std::vector<Value*>)>;

    class FunctionModule : public Function{
    private:
        function_type f;
    public:
        FunctionModule(function_type f) : f(f) {}
        Value* execute(std::vector<Value*> values);
        operator std::string();
    };
}}

#endif // FUNCTIONMODULE_H_INCLUDED
