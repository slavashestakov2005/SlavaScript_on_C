#include "classvalue.h"
#include "../Exception/exceptions.h"
#include "../Lib/utils.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::CastException;


ClassValue::ClassValue(std::shared_ptr<Class> cls) : cls(cls) {}


std::shared_ptr<Value> ClassValue::construct(std::vector<std::shared_ptr<Value>> values){ return cls -> construct(values); }

std::string ClassValue::getName() const { return cls -> getName(); }

std::shared_ptr<Function> ClassValue::getFunction(std::string func){ return cls -> getFunction(func); }

bool ClassValue::isExists(std::string name){ return cls -> isExists(name); }


std::shared_ptr<Value> ClassValue::copy(){
    SH_RET(ClassValue, cls);
}

double ClassValue::asDouble(){
    throw CastException(Values::CLASS, Values::NUMBER);
}

std::string ClassValue::asString(){
    throw CastException(Values::CLASS, Values::STRING);
}

bool ClassValue::asBool(){
    throw CastException(Values::CLASS, Values::BOOL);
}

Bignum ClassValue::asBignum(){
    throw CastException(Values::CLASS, Values::NUMBER);
}

Values ClassValue::type() const{
    return Values::CLASS;
}

ClassValue::operator std::string(){ return std::string(*cls); }

std::string ClassValue::stringType() const{ return cls -> stringType(); }


namespace SlavaScript::lang{
    CMP(ClassValue){
        RCHECK(a.getName(), b.getName());
    }

    DEF_EQ(ClassValue)
}
