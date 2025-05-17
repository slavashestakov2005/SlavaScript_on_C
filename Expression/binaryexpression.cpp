#include "binaryexpression.h"
#include "../Exception/exceptions.h"
#include "../Lib/functions.h"
#include "../Lib/utils.h"
#include "../Value/arrayvalue.h"
#include "../Value/bignumbers/smath.h"
#include "../Value/mapvalue.h"
#include "../Value/nullvalue.h"
#include "../Value/numbervalue.h"

using namespace SlavaScript::lang;
using SlavaScript::modules::math_out::pow;
using SlavaScript::exceptions::UnknownOperationException;


std::shared_ptr<Value> BinaryExpression::calculate(BinaryOperator operation, std::shared_ptr<Value> left, std::shared_ptr<Value> right){
    if (left -> type() == Values::INTEGRATION || right -> type() == Values::INTEGRATION) throw UnknownOperationException(getOperator(operation), left, right);
    if (left -> type() == Values::OBJECT || right -> type() == Values::OBJECT){
        return get_property(left, operation) -> execute({right});
    }
    if (left -> type() == Values::FUNCTION || right -> type() == Values::FUNCTION) throw UnknownOperationException(getOperator(operation), left, right);
    if (left -> type() == Values::NULL_ || right -> type() == Values::NULL_) return NullValue::NULL_;
    if (left -> type() == Values::MAP && right -> type() != Values::MAP && right -> type() != Values::STRING) throw UnknownOperationException(getOperator(operation), left, right);
    if (right -> type() == Values::MAP && left -> type() != Values::MAP && left -> type() != Values::STRING) throw UnknownOperationException(getOperator(operation), left, right);
    if (left -> type() == Values::ARRAY && right -> type() == Values::ARRAY){
        if (operation != BinaryOperator::ADD) throw UnknownOperationException(getOperator(operation), left, right);
        return ArrayValue::add(CAST(ArrayValue, left), CAST(ArrayValue, right));
    }
    if (left -> type() == Values::MAP && right -> type() == Values::MAP){
        if (operation != BinaryOperator::ADD) throw UnknownOperationException(getOperator(operation), left, right);
        return MapValue::add(CAST(MapValue, left), CAST(MapValue, left));
    }
    if (left -> type() == Values::ARRAY){
        if (operation != BinaryOperator::ADD) throw UnknownOperationException(getOperator(operation), left, right);
        return ArrayValue::add(CAST(ArrayValue, left), right);
    }
    if (right -> type() == Values::ARRAY && left -> type() != Values::STRING){
        throw UnknownOperationException(getOperator(operation), left, right);
    }
    if (left -> type() == Values::STRING || right -> type() == Values::STRING){
        std::string string1 = left -> asString();
        std::string string2 = right -> asString();
        switch(operation){
            case BinaryOperator::ADD : SH_RET(StringValue, string1 + string2);
            case BinaryOperator::MULTIPLY : {
                if (right -> type() != Values::NUMBER) throw UnknownOperationException(getOperator(operation), left, right);
                int iterations = right -> asDouble();
                std::string result;
                for(int i = 0; i < iterations; ++i) result += string1;
                SH_RET(StringValue, result);
            }
            default: throw UnknownOperationException(getOperator(operation), left, right);
        }
    }
    Bignum num1 = left -> asBignum();
    Bignum num2 = right -> asBignum();
    ///long long lon1 = num1, lon2 = num2;
    switch(operation){
        case BinaryOperator::ADD : num1 += num2; break;
        case BinaryOperator::SUBSTRACT : num1 -= num2; break;
        case BinaryOperator::MULTIPLY : num1 *= num2; break;
        case BinaryOperator::DIVIDE : num1 /= num2; break;
        case BinaryOperator::REMAINDER : num1 %= num2; break;
        case BinaryOperator::POWER : num1 = pow(num1, num2); break;
///        case BinaryOperator::AND: return new NumberValue(lon1 & lon2);
///        case BinaryOperator::OR: return new NumberValue(lon1 | lon2);
///        case BinaryOperator::XOR: return new NumberValue(lon1 ^ lon2);
///        case BinaryOperator::LSHIFT: return new NumberValue(lon1 << lon2);
///        case BinaryOperator::RSHIFT: return new NumberValue(lon1 >> lon2);
        default: throw UnknownOperationException(getOperator(operation), left, right);
    }
    SH_RET(NumberValue, num1);
}

BinaryExpression::BinaryExpression(BinaryOperator operation) : operation(operation), expr1(nullptr), expr2(nullptr) {}
BinaryExpression::BinaryExpression(BinaryOperator operation, Expression* expr1, Expression* expr2) : operation(operation), expr1(expr1), expr2(expr2) {}

std::shared_ptr<Value> BinaryExpression::eval(){
    std::shared_ptr<Value> value1 = expr1 -> eval();
    std::shared_ptr<Value> value2 = expr2 -> eval();
    if (Functions::find(getOperator(operation), 2)){
        std::vector<std::shared_ptr<Value>> vec = {value1, value2};
        return Functions::get(getOperator(operation), 2) -> execute(vec);
    }
    return calculate(operation, value1, value2);
}

Expressions BinaryExpression::type() const{
    return Expressions::BinaryExpression;
}

BinaryExpression::operator std::string(){
    return "[" + std::string(*expr1) + " " + getOperator(operation) + " " + std::string(*expr2) + "]";
}

BinaryExpression::~BinaryExpression(){
    delete expr1;
    expr1 = nullptr;
    delete expr2;
    expr2 = nullptr;
}

void BinaryExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}
