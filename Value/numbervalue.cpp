#include <sstream>
#include "numbervalue.h"
#include <exception>

using namespace SlavaScript::lang;

std::shared_ptr<NumberValue> NumberValue::M_ONE = std::make_shared<NumberValue>(-1);
std::shared_ptr<NumberValue> NumberValue::ZERO = std::make_shared<NumberValue>(0);
std::shared_ptr<NumberValue> NumberValue::ONE = std::make_shared<NumberValue>(1);

double NumberValue::asDouble(){
    std::istringstream is(value);
    double val = 0;
    try{
        is >> val;
        return val;
    }catch(...) {
        throw std::logic_error("Bad Number class");
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

bool SlavaScript::lang::operator==(NumberValue const& a, NumberValue const& b){
    return a.value == b.value;
}

bool SlavaScript::lang::operator!=(NumberValue const& a, NumberValue const& b){
    return a.value != b.value;
}

bool SlavaScript::lang::operator<(NumberValue const& a, NumberValue const& b){
    return a.value < b.value;
}

bool SlavaScript::lang::operator<=(NumberValue const& a, NumberValue const& b){
    return a.value <= b.value;
}

bool SlavaScript::lang::operator>(NumberValue const& a, NumberValue const& b){
    return a.value > b.value;
}

bool SlavaScript::lang::operator>=(NumberValue const& a, NumberValue const& b){
    return a.value >= b.value;
}
