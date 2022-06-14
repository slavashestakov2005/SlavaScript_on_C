#include "modulefunction.h"
#include "../Exception/typeexception.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::TypeException;

std::shared_ptr<Value> ModuleFunction::execute(std::vector<std::shared_ptr<Value>> values){
    return f(values);
}

ModuleFunction::operator std::string(){
    throw new TypeException("Cannot cast function to string");
}
