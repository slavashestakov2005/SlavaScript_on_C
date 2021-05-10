#include "assignmentexpression.h"
#include "../Lib/variables.h"
#include "../Expression/binaryexpression.h"
#include "../Expression/valueexpression.h"
#include "../Exception/operationIsnotsupportedexception.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::OperationIsNotSupportedException;

std::shared_ptr<Value> AssignmentExpression::calculate(AssignmentOperator operation, std::shared_ptr<Value> left, std::shared_ptr<Value> right){
    std::shared_ptr<Value> result;
    switch(operation){
        case AssignmentOperator::ASSIGN : result = right; break;
        case AssignmentOperator::ADD : result = BinaryExpression::calculate(BinaryOperator::ADD, left, right); break;
        case AssignmentOperator::SUBSTRACT : result = BinaryExpression::calculate(BinaryOperator::SUBSTRACT , left, right); break;
        case AssignmentOperator::MULTIPLY : result = BinaryExpression::calculate(BinaryOperator::MULTIPLY, left, right); break;
        case AssignmentOperator::DIVIDE : result = BinaryExpression::calculate(BinaryOperator::DIVIDE, left, right); break;
        case AssignmentOperator::REMAINDER : result = BinaryExpression::calculate(BinaryOperator::REMAINDER, left, right); break;
        case AssignmentOperator::POWER : result = BinaryExpression::calculate(BinaryOperator::POWER, left, right); break;
        case AssignmentOperator::AND : result = BinaryExpression::calculate(BinaryOperator::AND, left, right); break;
        case AssignmentOperator::OR : result = BinaryExpression::calculate(BinaryOperator::OR, left, right); break;
        case AssignmentOperator::XOR : result = BinaryExpression::calculate(BinaryOperator::XOR, left, right); break;
        case AssignmentOperator::LSHIFT : result = BinaryExpression::calculate(BinaryOperator::LSHIFT, left, right); break;
        case AssignmentOperator::RSHIFT : result = BinaryExpression::calculate(BinaryOperator::RSHIFT, left, right); break;
        case AssignmentOperator::_PLUSPLUS : result = BinaryExpression::calculate(BinaryOperator::ADD, left, NumberValue::ONE); break;
        case AssignmentOperator::PLUSPLUS_ : result = BinaryExpression::calculate(BinaryOperator::ADD, left, NumberValue::ONE); break;
        case AssignmentOperator::_MINUSMINUS : result = BinaryExpression::calculate(BinaryOperator::SUBSTRACT, left, NumberValue::ONE); break;
        case AssignmentOperator::MINUSMINUS_ : result = BinaryExpression::calculate(BinaryOperator::SUBSTRACT, left, NumberValue::ONE); break;
        default: throw new OperationIsNotSupportedException(getOperator(operation));
    }
    return result;
}

std::shared_ptr<Value> AssignmentExpression::eval(){
    std::shared_ptr<Value> left = Variables::get(variable);
    std::shared_ptr<Value> right = expression == nullptr ? nullptr : expression -> eval();
    std::shared_ptr<Value> result = calculate(operation, left, right);
    Variables::set(variable, result);
    if (operation == AssignmentOperator::_PLUSPLUS || operation == AssignmentOperator::_MINUSMINUS) result = left;
    return result;
}

AssignmentExpression::operator std::string(){
    if (operation == AssignmentOperator::MINUSMINUS_ || operation == AssignmentOperator::PLUSPLUS_){
        return getOperator(operation) + " '" + variable + "'";
    }
    return "'" + variable + "' " + getOperator(operation) + " " + std::string(*expression);
}

AssignmentExpression::~AssignmentExpression(){
    delete expression;
    expression = nullptr;
}

void AssignmentExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}
