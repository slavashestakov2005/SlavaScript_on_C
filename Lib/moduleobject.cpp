#include "moduleobject.h"
#include "../Exception/exceptions.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::CastException;

double ModuleObject::asDouble(){
    throw CastException(Values::OBJECT, Values::NUMBER);
}

std::string ModuleObject::asString(){
    throw CastException(Values::OBJECT, Values::STRING);
}

bool ModuleObject::asBool(){
    throw CastException(Values::OBJECT, Values::BOOL);
}

Bignum ModuleObject::asBignum(){
    throw CastException(Values::OBJECT, Values::NUMBER);
}

Values ModuleObject::type() const{
    return Values::OBJECT;
}

ModuleObject::operator std::string(){
    throw CastException(Values::OBJECT, Values::STRING);
}
