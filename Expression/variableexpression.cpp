#include "variableexpression.h"
#include "../Lib/variables.h"
#include "../Exception/variabledoesnotexistsexception.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::VariableDoesNotExistsException;

VariableExpression::operator std::string(){
    return name;
}

Value* VariableExpression::eval(){
    if (!Variables::isExists(name)) throw new VariableDoesNotExistsException(name);
    return Variables::get(name);
}

void VariableExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}
