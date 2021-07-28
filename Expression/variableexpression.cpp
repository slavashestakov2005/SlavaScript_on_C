#include "variableexpression.h"
#include "../Lib/names.h"

using namespace SlavaScript::lang;

VariableExpression::operator std::string(){
    return "'" + name + "'";
}

std::shared_ptr<Value> VariableExpression::eval(){
    return Names::get(name);
}

void VariableExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}
