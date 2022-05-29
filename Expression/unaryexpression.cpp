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
#include "../Value/classmodulevalue.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::OperationIsNotSupportedException;

std::shared_ptr<Value> UnaryExpression::calculate(UnaryOperator operation, std::shared_ptr<Value> value){
    if (value -> type() == Values::INTEGRATION) throw new TypeException("Cannot used unary operation for integration");
    if (value -> type() == Values::CLASS){
        if (value -> isClassFromModule()){
            std::shared_ptr<Function> func = get_property(value, operation);
            return func -> execute({});
        }
        else throw new TypeException("Cannot used unary operation for class");
    }
    if (value -> type() == Values::NULL_) return NullValue::NULL_;
    switch(operation){
        case UnaryOperator::PLUS : return SHARE(NumberValue, value -> asBignum());
        case UnaryOperator::NEGATIVE : return SHARE(NumberValue, -(value -> asBignum()));
        case UnaryOperator::NOT : return BoolValue::fromBool(!(value -> asBignum()));
        /// case UnaryOperator::COMPLEMENT : return new NumberValue(~(value -> asBignum()));
        case UnaryOperator::PLUSPLUS : return SHARE(NumberValue, ++(value -> asBignum()));
        case UnaryOperator::MINUSMINUS : return SHARE(NumberValue, --(value -> asBignum()));
        default: throw new OperationIsNotSupportedException(getOperator(operation));
    }
}

std::shared_ptr<Value> UnaryExpression::eval(){
    std::shared_ptr<Value> val = expr -> eval();
    if (Functions::find(getOperator(operation), 1)){
        std::vector<std::shared_ptr<Value>> value;
        value.push_back(val);
        return Functions::get(getOperator(operation), 1) -> execute(value);
    }
    return calculate(operation, val);
}

UnaryExpression::operator std::string(){
    return "[" + getOperator(operation) + " " + std::string(*expr) + "]";
}

UnaryExpression::~UnaryExpression(){
    delete expr;
    expr = nullptr;
}

void UnaryExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}
