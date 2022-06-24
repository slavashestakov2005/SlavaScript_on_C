#include "suffixassignmentexpression.h"
#include "assignmentexpression.h"

using namespace SlavaScript::lang;


SuffixAssignmentExpression::SuffixAssignmentExpression(AssignmentOperator operation, SuffixExpression* containerExpr, Expression* expression) : operation(operation), containerExpr(containerExpr), expression(expression) {}

std::shared_ptr<Value> SuffixAssignmentExpression::eval(){
    std::shared_ptr<Value> left = containerExpr -> eval(), right = expression -> eval();
    containerExpr -> set(AssignmentExpression::calculate(operation, left, right));
    if (operation != AssignmentOperator::_PLUSPLUS && operation != AssignmentOperator::_MINUSMINUS) return right;
    return left;
}

Expressions SuffixAssignmentExpression::type() const{
    return Expressions::SuffixAssignmentExpression;
}

SuffixAssignmentExpression::operator std::string(){
    if (operation == AssignmentOperator::MINUSMINUS_ || operation == AssignmentOperator::PLUSPLUS_){
        return getOperator(operation) + " " + std::string(*containerExpr);
    }
    return std::string(*containerExpr) + " " + getOperator(operation) + " " + std::string(*expression);
}

SuffixAssignmentExpression::~SuffixAssignmentExpression(){
    delete expression;
    expression = nullptr;
}

void SuffixAssignmentExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}
