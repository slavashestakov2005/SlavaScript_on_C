#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED

#include <vector>
#include "../Value/value.h"
#include "../Exception/typeexception.h"

using SlavaScript::exceptions::TypeException;

namespace SlavaScript{ namespace lang{
    class Function{
    public:
        bool type = false;
        virtual Value* execute(std::vector<Value*>) = 0;
        virtual operator std::string(){  throw new TypeException("Cannot cast function to string"); }
        virtual Value* operator()(std::vector<Value*> args) final { return execute(args); }
    };
}}

#endif // FUNCTION_H_INCLUDED
