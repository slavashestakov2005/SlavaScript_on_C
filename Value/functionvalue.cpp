#include "functionvalue.h"
#include "../Exception/typeexception.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::TypeException;

std::shared_ptr<Value> FunctionValue::copy(){
    return SHARE(FunctionValue, value);
}

double FunctionValue::asDouble(){
    throw new TypeException("Cannot cast function to number");
}

std::string FunctionValue::asString(){
    return std::string(*value);
}

bool FunctionValue::asBool(){
    throw new TypeException("Cannot cast function to bool");
}

Bignum FunctionValue::asBignum(){
    throw new TypeException("Cannot cast function to number");
}

Values FunctionValue::type() const{
    return Values::FUNCTION;
}

std::shared_ptr<Function> FunctionValue::getFunction(){
    return value;
}

FunctionValue::operator std::string(){
    return asString();
};

bool SlavaScript::lang::operator==(FunctionValue const& a, FunctionValue const& b){
    throw new TypeException("Operator '==' cannot used for two functions");
}

bool SlavaScript::lang::operator!=(FunctionValue const& a, FunctionValue const& b){
    throw new TypeException("Operator '!=' cannot used for two functions");
}

bool SlavaScript::lang::operator<(FunctionValue const& a, FunctionValue const& b){
    throw new TypeException("Operator '<' cannot used for two functions");
}

bool SlavaScript::lang::operator<=(FunctionValue const& a, FunctionValue const& b){
    throw new TypeException("Operator '<=' cannot used for two functions");
}

bool SlavaScript::lang::operator>(FunctionValue const& a, FunctionValue const& b){
    throw new TypeException("Operator '>' cannot used for two functions");
}

bool SlavaScript::lang::operator>=(FunctionValue const& a, FunctionValue const& b){
    throw new TypeException("Operator '>=' cannot used for two functions");
}
