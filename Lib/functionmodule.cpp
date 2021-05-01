#include "functionmodule.h"
#include "../Exception/typeexception.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::TypeException;

std::shared_ptr<Value> FunctionModule::execute(std::vector<std::shared_ptr<Value>> values){
    return f(values);
}

FunctionModule::operator std::string(){
    throw new TypeException("Cannot cast function to string");
}
