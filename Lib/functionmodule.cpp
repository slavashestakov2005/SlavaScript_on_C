#include "functionmodule.h"
#include "../Exception/typeexception.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::TypeException;

Value* FunctionModule::execute(std::vector<Value*> values){
    return f(values);
}

FunctionModule::operator std::string(){
    throw new TypeException("Cannot cast function to string");
}
