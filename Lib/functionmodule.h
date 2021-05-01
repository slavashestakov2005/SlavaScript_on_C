#ifndef FUNCTIONMODULE_H_INCLUDED
#define FUNCTIONMODULE_H_INCLUDED

#include <functional>
#include "function.h"

namespace SlavaScript{ namespace lang{
    using function_type = std::function<std::shared_ptr<Value>(std::vector<std::shared_ptr<Value>>)>;

    class FunctionModule : public Function{
    private:
        function_type f;
    public:
        FunctionModule(function_type f) : f(f) {}
        std::shared_ptr<Value> execute(std::vector<std::shared_ptr<Value>> values);
        operator std::string();
    };
}}

#endif // FUNCTIONMODULE_H_INCLUDED
