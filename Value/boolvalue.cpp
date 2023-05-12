#include "boolvalue.h"

using namespace SlavaScript::lang;


std::shared_ptr<BoolValue> BoolValue::TRUE_ = SHARE(BoolValue, true);
std::shared_ptr<BoolValue> BoolValue::FALSE_ = SHARE(BoolValue, false);

std::shared_ptr<BoolValue> BoolValue::fromBool(bool b){
    return (b ? TRUE_ : FALSE_);
}


BoolValue::BoolValue(bool value) : value(value) {}


std::shared_ptr<Value> BoolValue::copy(){
    return fromBool(this -> value);
}

double BoolValue::asDouble(){
    return (value ? 1 : 0);
}

std::string BoolValue::asString(){
    return (value ? "true" : "false");
}

bool BoolValue::asBool(){
    return value;
}

Bignum BoolValue::asBignum(){
    return Bignum(value);
}

Values BoolValue::type() const{
    return Values::BOOL;
}

BoolValue::operator std::string(){
    return asString();
}


namespace SlavaScript::lang{
    CMP(BoolValue){
        RCHECK(a.value, b.value);
    }

    DEF_EQ(BoolValue)
}
