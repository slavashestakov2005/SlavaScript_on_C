#include "variableexpression.h"
#include "../Lib/variables.h"
#include "../Lib/functions.h"
#include "../Value/functionvalue.h"
#include "../Exception/variabledoesnotexistsexception.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::VariableDoesNotExistsException;

VariableExpression::operator std::string(){
    return "'" + name + "'";
}

Value* VariableExpression::eval(){
    if (Variables::isExists(name)) return Variables::get(name);
    if (Functions::isExists(name)) return new FunctionValue(Functions::get(name));
    throw new VariableDoesNotExistsException(name);

}

void VariableExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}
