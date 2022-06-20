#include "binaryexpression.h"
#include "../Lib/moduleobject.h"
#include "../Value/numbervalue.h"
#include "../Value/stringvalue.h"
#include "../Value/arrayvalue.h"
#include "valueexpression.h"
#include "../Exception/typeexception.h"
#include "../Exception/mathexception.h"
#include "../Exception/operationIsnotsupportedexception.h"
#include "../Lib/functions.h"
#include "../Value/nullvalue.h"
#include "../Value/bignumbers/smath.h"
#include <vector>

using namespace SlavaScript::lang;
using SlavaScript::modules::math_out::pow;
using SlavaScript::exceptions::TypeException;
using SlavaScript::exceptions::OperationIsNotSupportedException;

std::shared_ptr<Value> BinaryExpression::calculate(BinaryOperator operation, std::shared_ptr<Value> left, std::shared_ptr<Value> right){
    if (left -> type() == Values::INTEGRATION || right -> type() == Values::INTEGRATION) throw new TypeException("Cannot used binary operation for integration");
    if (left -> type() == Values::OBJECT || right -> type() == Values::OBJECT){
        return get_property(left, operation) -> execute({right});
    }
    if (left -> type() == Values::FUNCTION || right -> type() == Values::FUNCTION) throw new TypeException("Cannot used binary operation for function");
    if (left -> type() == Values::NULL_ || right -> type() == Values::NULL_) return NullValue::NULL_;
    if (left -> type() == Values::MAP && right -> type() != Values::MAP && right -> type() != Values::STRING) throw new TypeException("Cannot used binary operation for map and not map and not string");
    if (right -> type() == Values::MAP && left -> type() != Values::MAP && left -> type() != Values::STRING) throw new TypeException("Cannot used binary operation for not map and not string and array");
    if (left -> type() == Values::ARRAY && right -> type() == Values::ARRAY){
        if (operation != BinaryOperator::ADD) throw new TypeException("Cannot used array and array for not plus operation");
        return ArrayValue::add(CAST(ArrayValue, left), CAST(ArrayValue, right));
    }
    if (left -> type() == Values::MAP && right -> type() == Values::MAP){
        if (operation != BinaryOperator::ADD) throw new TypeException("Cannot used map and map for not plus operation");
        return MapValue::add(CAST(MapValue, left), CAST(MapValue, left));
    }
    if (left -> type() == Values::ARRAY){
        if (operation != BinaryOperator::ADD) throw new TypeException("Cannot used not plus binary operation for array");
        return ArrayValue::add(CAST(ArrayValue, left), right);
    }
    if (right -> type() == Values::ARRAY && left -> type() != Values::STRING){
        throw new TypeException("Cannot used binary plus for not string, not array and array");
    }
    if (left -> type() == Values::STRING || right -> type() == Values::STRING){
        std::string string1 = left -> asString();
        std::string string2 = right -> asString();
        switch(operation){
            case BinaryOperator::ADD : return SHARE(StringValue, string1 + string2);
            case BinaryOperator::MULTIPLY : {
                if (right -> type() != Values::NUMBER) throw new TypeException("Unknown multiply for not number and not number");
                int iterations = right -> asDouble();
                std::string result;
                for(int i = 0; i < iterations; ++i) result += string1;
                return SHARE(StringValue, result);
            }
            default: throw new OperationIsNotSupportedException(getOperator(operation));
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
        default: throw new OperationIsNotSupportedException(getOperator(operation));
    }
    return SHARE(NumberValue, num1);
}

std::shared_ptr<Value> BinaryExpression::eval(){
    std::shared_ptr<Value> value1 = expr1 -> eval();
    std::shared_ptr<Value> value2 = expr2 -> eval();
    if (Functions::find(getOperator(operation), 2)){
        std::vector<std::shared_ptr<Value>> vec = {value1, value2};
        return Functions::get(getOperator(operation), 2) -> execute(vec);
    }
    return calculate(operation, value1, value2);
}

BinaryExpression::operator std::string(){
    return "[" + std::string(*expr1) + " " + getOperator(operation) + " " + std::string(*expr2) + "]";
}

void BinaryExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}

BinaryExpression::~BinaryExpression(){
    delete expr1;
    expr1 = nullptr;
    delete expr2;
    expr2 = nullptr;
}
