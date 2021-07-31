#include "nullvalue.h"
#include "../Exception/typeexception.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::TypeException;

std::shared_ptr<NullValue> NullValue::NULL_ = SHARE(NullValue, );

std::shared_ptr<Value> NullValue::copy(){
    return NULL_;
}

double NullValue::asDouble(){
    throw new TypeException("Cannot cast null to double");
}

std::string NullValue::asString(){
    throw new TypeException("Cannot cast null to string");
}

bool NullValue::asBool(){
    throw new TypeException("Cannot cast null to bool");
}

Bignum NullValue::asBignum(){
    throw new TypeException("Cannot cast null to number");
}

Values NullValue::type() const{
    return Values::NULL_;
}

NullValue::operator std::string(){
    return "null";
}

bool SlavaScript::lang::operator==(NullValue const& a, NullValue const& b){
    return true;
}

bool SlavaScript::lang::operator!=(NullValue const& a, NullValue const& b){
    return false;
}

bool SlavaScript::lang::operator<(NullValue const& a, NullValue const& b){
    return false;
}

bool SlavaScript::lang::operator<=(NullValue const& a, NullValue const& b){
    return true;
}

bool SlavaScript::lang::operator>(NullValue const& a, NullValue const& b){
    return false;
}

bool SlavaScript::lang::operator>=(NullValue const& a, NullValue const& b){
    return true;
}
