#include <Exception/exceptions.h>
#include <Expression/conditionalexpression.h>
#include <Lib/functions.h>
#include <Lib/utils.h>
#include <Value/boolvalue.h>


using namespace SlavaScript::lang;
using SlavaScript::exceptions::LogicException;
using SlavaScript::exceptions::UnknownOperationException;


std::shared_ptr<Value> ConditionalExpression::calculate(ConditionalOperator operation, std::shared_ptr<Value> left, std::shared_ptr<Value> right) {
    if (left -> type() == Values::OBJECT || right -> type() == Values::OBJECT) {
        try {
            return get_property(left, operation) -> execute({right});
        } catch (...) {}
        if (operation == ConditionalOperator::AND || operation == ConditionalOperator::OR) throw UnknownOperationException(getOperator(operation), left, right);
        std::shared_ptr<Function> func = get_property(left, ConditionalOperator::LTEQGT);
        std::shared_ptr<Value> res = func -> execute({right});
        if (res -> type() != Values::NUMBER) throw LogicException("Operation <=> return not a number");
        int sign_of_res = res -> asBignum().get_sign();
        bool result = false;
        if (sign_of_res == -1 && (operation == ConditionalOperator::LT || operation == ConditionalOperator::LTEQ || operation == ConditionalOperator::NOT_EQUALS)) result = true;
        else if (sign_of_res == 1 && (operation == ConditionalOperator::GT || operation == ConditionalOperator::GTEQ || operation == ConditionalOperator::NOT_EQUALS)) result = true;
        else if (sign_of_res == 0 && (operation == ConditionalOperator::LTEQ || operation == ConditionalOperator::GTEQ || operation == ConditionalOperator::EQUALS)) result = true;
        return BoolValue::fromBool(result);
    }
    bool result;
    switch (operation) {
        case ConditionalOperator::EQUALS : result = equals(left, right); break;
        case ConditionalOperator::NOT_EQUALS : result = !equals(left, right); break;
        case ConditionalOperator::LT : result = comparator(left, right); break;
        case ConditionalOperator::LTEQ : result = comparator(left, right) || equals(left, right); break;
        case ConditionalOperator::GT : result = comparator(right, left); break;
        case ConditionalOperator::GTEQ : result = comparator(right, left) || equals(left, right); break;
        case ConditionalOperator::AND : result = left -> asBool() && right -> asBool(); break;
        case ConditionalOperator::OR : result = left -> asBool() || right -> asBool(); break;
        default: throw UnknownOperationException(getOperator(operation), left, right);
    }
    return BoolValue::fromBool(result);
}

ConditionalExpression::ConditionalExpression(ConditionalOperator operation, Expression* expr1, Expression* expr2) : operation(operation), expr1(expr1), expr2(expr2) {}

std::shared_ptr<Value> ConditionalExpression::eval() {
    std::shared_ptr<Value> value1 = expr1 -> eval();
    std::shared_ptr<Value> value2 = expr2 -> eval();
    if (Functions::find(getOperator(operation), 2)) {
        std::vector<std::shared_ptr<Value>> vec = { value1, value2 };
        return Functions::get(getOperator(operation), 2) -> execute(vec);
    }
    return calculate(operation, value1, value2);
}

Expressions ConditionalExpression::type() const {
    return Expressions::ConditionalExpression;
}

ConditionalExpression::operator std::string() {
    return "[" + std::string(*expr1) + " " + getOperator(operation) + " " + std::string(*expr2) + "]";
}

ConditionalExpression::~ConditionalExpression() {
    delete expr1;
    expr1 = nullptr;
    delete expr2;
    expr2 = nullptr;
}

void ConditionalExpression::accept(Visitor* visitor) {
    visitor -> visit(this);
}
