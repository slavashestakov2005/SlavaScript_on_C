#include "numbervalue.h"
#include "../Exception/exceptions.h"
#include <sstream>

using namespace SlavaScript::lang;
using SlavaScript::exceptions::MathException;


std::shared_ptr<NumberValue> NumberValue::M_ONE = SHARE(NumberValue, -1);
std::shared_ptr<NumberValue> NumberValue::ZERO = SHARE(NumberValue, 0);
std::shared_ptr<NumberValue> NumberValue::ONE = SHARE(NumberValue, 1);


NumberValue::NumberValue(Bignum value) : value(value) {}
NumberValue::NumberValue(std::string value) : value(Bignum(value)) {}
NumberValue::NumberValue(int value) : value(Bignum(value)) {}
NumberValue::NumberValue(long long value) : value(Bignum(value)) {}
NumberValue::NumberValue(size_t value) : value(Bignum((long long) value)) {}
NumberValue::NumberValue(clock_t value) : value(Bignum((long long) value)) {}
NumberValue::NumberValue(double value) : value(Bignum(value)) {}
NumberValue::NumberValue(std::strong_ordering val){
    if (val == std::strong_ordering::less) value = Bignum(-1);
    else if (val == std::strong_ordering::greater) value = Bignum(1);
    else value = Bignum(0);
}


std::shared_ptr<Value> NumberValue::copy(){
    return SHARE(NumberValue, value);
}

double NumberValue::asDouble(){
    std::istringstream is(value);
    double val = 0;
    try{
        is >> val;
        return val;
    }catch(...) {
        throw MathException("Number is too large for operation");
    }
}

std::string NumberValue::asString(){
    return value;
}

bool NumberValue::asBool(){
    return bool(value);
}

Bignum NumberValue::asBignum(){
    return value;
}

Values NumberValue::type() const{
    return Values::NUMBER;
}

NumberValue::operator std::string(){
    return asString();
};


namespace SlavaScript::lang{
    CMP(NumberValue){
        RCHECK(a.value, b.value);
    }

    DEF_EQ(NumberValue)
}
