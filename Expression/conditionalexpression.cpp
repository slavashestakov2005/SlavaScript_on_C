#include "conditionalexpression.h"
#include "../Value/boolvalue.h"
#include "../Value/arrayvalue.h"
#include "../Lib/functions.h"
#include "../Value/classvalue.h"
#include "../Lib/moduleobject.h"
#include "../Value/integrationvalue.h"
#include "valueexpression.h"
#include "../Exception/operationIsnotsupportedexception.h"
#include "../Exception/typeexception.h"
#include <string>
#include <stdexcept>

using namespace SlavaScript::lang;
using SlavaScript::exceptions::OperationIsNotSupportedException;

std::shared_ptr<Value> ConditionalExpression::calculate(ConditionalOperator operation, std::shared_ptr<Value> left, std::shared_ptr<Value> right){
    if (left -> type() == Values::OBJECT || right -> type() == Values::OBJECT){
        try{
            std::shared_ptr<Function> func = get_property(left, operation);
            return ClassMethod::execute(func, {right}, left);
        } catch(...) {}
        if (operation == ConditionalOperator::AND || operation == ConditionalOperator::OR) throw new TypeException("Operation " + getOperator(operation) + " undefined");
        std::shared_ptr<Function> func = get_property(left, ConditionalOperator::LTEQGT);
        std::shared_ptr<Value> res;
        if (func -> isClassMethod()) res = ClassMethod::execute(func, {right}, left);
        else res = func -> execute({right});
        if (res -> type() != Values::NUMBER) throw new TypeException("Operation <=> return not a number");
        int sign_of_res = res -> asBignum().get_sign();
        bool result = false;
        if (sign_of_res == -1 && (operation == ConditionalOperator::LT || operation == ConditionalOperator::LTEQ || operation == ConditionalOperator::NOT_EQUALS)) result = true;
        else if (sign_of_res == 1 && (operation == ConditionalOperator::GT || operation == ConditionalOperator::GTEQ || operation == ConditionalOperator::NOT_EQUALS)) result = true;
        else if (sign_of_res == 0 && (operation == ConditionalOperator::LTEQ || operation == ConditionalOperator::GTEQ || operation == ConditionalOperator::EQUALS)) result = true;
        return BoolValue::fromBool(result);
    }
    bool result;
    switch(operation){
        case ConditionalOperator::EQUALS : result = equals(left, right); break;
        case ConditionalOperator::NOT_EQUALS : result = !equals(left, right); break;
        case ConditionalOperator::LT : result = comparator(left, right); break;
        case ConditionalOperator::LTEQ : result = comparator(left, right) || equals(left, right); break;
        case ConditionalOperator::GT : result = comparator(right, left); break;
        case ConditionalOperator::GTEQ : result = comparator(right, left) || equals(left, right); break;
        case ConditionalOperator::AND : result = left -> asBool() && right -> asBool(); break;
        case ConditionalOperator::OR : result = left -> asBool() || right -> asBool(); break;
        default: throw new OperationIsNotSupportedException(getOperator(operation));
    }
    return BoolValue::fromBool(result);
}

std::shared_ptr<Value> ConditionalExpression::eval(){
    std::shared_ptr<Value> value1 = expr1 -> eval();
    std::shared_ptr<Value> value2 = expr2 -> eval();
    if (Functions::find(getOperator(operation), 2)){
        std::vector<std::shared_ptr<Value>> vec = { value1, value2 };
        return Functions::get(getOperator(operation), 2) -> execute(vec);
    }
    return calculate(operation, value1, value2);
}

ConditionalExpression::operator std::string(){
    return "[" + std::string(*expr1) + " " + getOperator(operation) + " " + std::string(*expr2) + "]";
}

ConditionalExpression::~ConditionalExpression(){
    delete expr1;
    expr1 = nullptr;
    delete expr2;
    expr2 = nullptr;
}

void ConditionalExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}
