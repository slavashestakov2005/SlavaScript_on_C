#include "conditionalexpression.h"
#include "../Value/boolvalue.h"
#include "../Value/arrayvalue.h"
#include "../Lib/functions.h"
#include "../Value/classvalue.h"
#include "valueexpression.h"
#include "../Exception/operationIsnotsupportedexception.h"
#include "../Exception/typeexception.h"
#include <string>
#include <stdexcept>

using namespace SlavaScript::lang;
using SlavaScript::exceptions::OperationIsNotSupportedException;

namespace{
    std::string mas[] = {
        "==", "!=",
        "<", "<=", ">", ">=",
        "&&", "||"
    };

    bool operator_gtgt(Value const& a, Value const& b){
        if (a.type() != b.type()) return false;
        switch(a.type()){
            case Values::ARRAY : return *(ArrayValue*)(&a) == *(ArrayValue*)(&b);
            case Values::BOOL : return *(BoolValue*)(&a) == *(BoolValue*)(&b);
            case Values::NUMBER : return *(NumberValue*)(&a) == *(NumberValue*)(&b);
            case Values::FUNCTION : return *(FunctionValue*)(&a) == *(FunctionValue*)(&b);
            case Values::MAP : return *(MapValue*)(&a) == *(MapValue*)(&b);
            case Values::STRING : return *(StringValue*)(&a) == *(StringValue*)(&b);
            case Values::NULL_ : return *(NullValue*)(&a) == *(NullValue*)(&b);
            case Values::CLASS : return *(ClassValue*)(&a) == *(ClassValue*)(&b);
        }
    }

    bool operator_lt(Value const& a, Value const& b){
        if (a.type() != b.type()) return int(a.type()) < int(b.type());
        switch(a.type()){
            case Values::ARRAY : return *(ArrayValue*)(&a) < *(ArrayValue*)(&b);
            case Values::BOOL : return *(BoolValue*)(&a) < *(BoolValue*)(&b);
            case Values::NUMBER : return *(NumberValue*)(&a) < *(NumberValue*)(&b);
            case Values::FUNCTION : return *(FunctionValue*)(&a) < *(FunctionValue*)(&b);
            case Values::MAP : return *(MapValue*)(&a) < *(MapValue*)(&b);
            case Values::STRING : return *(StringValue*)(&a) < *(StringValue*)(&b);
            case Values::NULL_ : return *(NullValue*)(&a) < *(NullValue*)(&b);
            case Values::CLASS : return *(ClassValue*)(&a) < *(ClassValue*)(&b);
        }
    }
}

std::shared_ptr<Value> ConditionalExpression::calculate(ConditionalOperator operation, std::shared_ptr<Value> left, std::shared_ptr<Value> right){
    bool result;
    switch(operation){
        case ConditionalOperator::EQUALS : result = operator_gtgt(*left, *right); break;
        case ConditionalOperator::NOT_EQUALS : result = !operator_gtgt(*left, *right); break;
        case ConditionalOperator::LT : result = operator_lt(*left, *right); break;
        case ConditionalOperator::LTEQ : result = operator_lt(*left, *right) || operator_gtgt(*left, *right); break;
        case ConditionalOperator::GT : result = operator_lt(*right, *left); break;
        case ConditionalOperator::GTEQ : result = operator_lt(*right, *left) || operator_gtgt(*left, *right); break;
        case ConditionalOperator::AND : result = left -> asBool() && right -> asBool(); break;
        case ConditionalOperator::OR : result = left -> asBool() || right -> asBool(); break;
        default: throw new OperationIsNotSupportedException(mas[(int)operation]);
    }
    return BoolValue::fromBool(result);
}

std::shared_ptr<Value> ConditionalExpression::eval(){
    std::shared_ptr<Value> value1 = expr1 -> eval();
    std::shared_ptr<Value> value2 = expr2 -> eval();
    if (Functions::find(mas[(int) operation], 2)){
        std::vector<std::shared_ptr<Value>> vec = { value1, value2 };
        return Functions::get(mas[(int) operation], 2) -> execute(vec);
    }
    return calculate(operation, value1, value2);
}

ConditionalExpression::operator std::string(){
    return "[" + std::string(*expr1) + " " + mas[int(operation)] + " " + std::string(*expr2) + "]";
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
