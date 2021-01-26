#include "functionvalue.h"
#include "../Exception/typeexception.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::TypeException;

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

Function* FunctionValue::getFunction(){
    return value;
}

FunctionValue::operator std::string(){
    return asString();
};

FunctionValue::~FunctionValue(){
    delete value;
}

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
