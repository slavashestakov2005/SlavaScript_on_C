#include "containerassignmentexpression.h"
#include "../Lib/variables.h"
#include "../Expression/binaryexpression.h"
#include "../Expression/unaryexpression.h"
#include "../Expression/valueexpression.h"
#include "../Exception/typeexception.h"

using namespace SlavaScript::lang;

std::shared_ptr<Value> ContainerAssignmentExpression::eval(){
    std::shared_ptr<Value> result = containerExpr -> eval();
    containerExpr -> set(AssignmentExpression::calculate(operation, result, expression -> eval()));
    if (operation != AssignmentOperator::_PLUSPLUS && operation != AssignmentOperator::_MINUSMINUS) result = containerExpr -> get();
    return result;
}

ContainerAssignmentExpression::operator std::string(){
    if (operation == AssignmentOperator::MINUSMINUS_ || operation == AssignmentOperator::PLUSPLUS_){
        return getOperator(operation) + " " + std::string(*containerExpr);
    }
    return std::string(*containerExpr) + " " + getOperator(operation) + " " + std::string(*expression);
}

ContainerAssignmentExpression::~ContainerAssignmentExpression(){
    delete expression;
    expression = nullptr;
}

void ContainerAssignmentExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}
