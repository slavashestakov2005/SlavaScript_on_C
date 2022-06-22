#include "variableexpression.h"
#include "../Lib/names.h"

using namespace SlavaScript::lang;

VariableExpression::VariableExpression(std::string name) : name(name) {}

std::shared_ptr<Value> VariableExpression::eval(){
    return Names::get(name);
}

Expressions VariableExpression::type() const{
    return Expressions::VariableExpression;
}

VariableExpression::operator std::string(){
    return "'" + name + "'";
}

VariableExpression::~VariableExpression() {}

void VariableExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}
