#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED

#include <memory>
#include <vector>
#include "../Value/value.h"
#include "../Exception/typeexception.h"

using SlavaScript::exceptions::TypeException;

namespace SlavaScript::lang{
    class Function{
    public:
        virtual std::shared_ptr<Value> execute(std::vector<std::shared_ptr<Value>>) = 0;
        virtual operator std::string(){  throw new TypeException("Cannot cast function to string"); }
        virtual std::shared_ptr<Value> operator()(std::vector<std::shared_ptr<Value>> args) final { return execute(args); }
        virtual ~Function(){}
    };
}

#endif // FUNCTION_H_INCLUDED
