#include "exception"
#include "unaryoperator.h"
#include "unaryexpression.h"
#include "../Value/numbervalue.h"
#include "../Lib/variables.h"
#include "../Value/boolvalue.h"
#include "../Value/nullvalue.h"
#include "../Lib/functions.h"
#include "variableexpression.h"
#include "../Exception/typeexception.h"
#include "../Exception/operationIsnotsupportedexception.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::OperationIsNotSupportedException;

namespace{
    std::string mas[] = {
        "+", "-", "!", "~", "++", "--"
    };
}

Value* UnaryExpression::calculate(UnaryOperator operation, Value* value){
    if (value -> type() == Values::NULL_) return NullValue::NULL_;
    switch(operation){
        case UnaryOperator::PLUS : return new NumberValue(value -> asBignum());
        case UnaryOperator::NEGATIVE : return new NumberValue(-(value -> asBignum()));
        case UnaryOperator::NOT : return new BoolValue(!(value -> asBignum()));
        /// case UnaryOperator::COMPLEMENT : return new NumberValue(~(value -> asBignum()));
        case UnaryOperator::PLUSPLUS : return new NumberValue(++(value -> asBignum()));
        case UnaryOperator::MINUSMINUS : return new NumberValue(--(value -> asBignum()));
        default: throw new OperationIsNotSupportedException(mas[(int)operation]);
    }
}

Value* UnaryExpression::eval(){
    Value* val = expr -> eval();
    if (Functions::find(mas[(int) operation], 1)){
        std::vector<Value*> value;
        value.push_back(val);
        return Functions::get(mas[(int) operation], 1) -> execute(value);
    }
    return calculate(operation, val);
}

UnaryExpression::operator std::string(){
    return "[" + mas[int(operation)] + " " + std::string(*expr) + "]";
}

UnaryExpression::~UnaryExpression(){
    delete expr;
    expr = nullptr;
}

void UnaryExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}
