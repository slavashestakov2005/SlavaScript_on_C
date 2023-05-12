#include "nullvalue.h"
#include "../Exception/exceptions.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::CastException;


std::shared_ptr<NullValue> NullValue::NULL_ = SHARE(NullValue, );


std::shared_ptr<Value> NullValue::copy(){
    return NULL_;
}

double NullValue::asDouble(){
    throw CastException(Values::NULL_, Values::NUMBER);
}

std::string NullValue::asString(){
    throw CastException(Values::NULL_, Values::STRING);
}

bool NullValue::asBool(){
    throw CastException(Values::NULL_, Values::BOOL);
}

Bignum NullValue::asBignum(){
    throw CastException(Values::NULL_, Values::NUMBER);
}

Values NullValue::type() const{
    return Values::NULL_;
}

NullValue::operator std::string(){
    return "null";
}


namespace SlavaScript::lang{
    CMP(NullValue){
        return std::strong_ordering::equal;
    }

    DEF_EQ(NullValue)
}
