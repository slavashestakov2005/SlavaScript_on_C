#include "functionvalue.h"
#include "../Exception/exceptions.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::CastException;
using SlavaScript::exceptions::UnknownOperationException;


FunctionValue::FunctionValue(std::shared_ptr<Function> value) : value(value) {}
FunctionValue::FunctionValue(Function* value) : value(std::shared_ptr<Function>(value)) {}


std::shared_ptr<Function> FunctionValue::getFunction(){
    return value;
}


std::shared_ptr<Value> FunctionValue::copy(){
    return SHARE(FunctionValue, value);
}

double FunctionValue::asDouble(){
    throw CastException(Values::FUNCTION, Values::NUMBER);
}

std::string FunctionValue::asString(){
    return std::string(*value);
}

bool FunctionValue::asBool(){
    throw CastException(Values::FUNCTION, Values::BOOL);
}

Bignum FunctionValue::asBignum(){
    throw CastException(Values::FUNCTION, Values::NUMBER);
}

Values FunctionValue::type() const{
    return Values::FUNCTION;
}

FunctionValue::operator std::string(){
    return asString();
}

namespace SlavaScript::lang{
    CMP(FunctionValue){
        throw UnknownOperationException("conditional", &a, &b);
    }

    DEF_EQ(FunctionValue)
}
