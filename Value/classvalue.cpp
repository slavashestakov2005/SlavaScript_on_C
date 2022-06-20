#include "classvalue.h"
#include "objectvalue.h"
#include "../Statement/functiondefinestatement.h"
#include "../Statement/classdeclarationsstatement.h"

using namespace SlavaScript::lang;

ClassValue::ClassValue(std::shared_ptr<Class> cls) : cls(cls) {}

std::shared_ptr<Value> ClassValue::copy(){
    SH_RET(ClassValue, cls);
}

std::shared_ptr<Value> ClassValue::construct(std::vector<std::shared_ptr<Value>> values){ return cls -> construct(values); }

std::string ClassValue::getName() const { return cls -> getName(); }

std::shared_ptr<Function> ClassValue::getFunction(std::string func){ return cls -> getFunction(func); }

bool ClassValue::isExists(std::string name){ return cls -> isExists(name); }

double ClassValue::asDouble(){
    throw new TypeException("Cannot cast class to double");
}

std::string ClassValue::asString(){
    throw new TypeException("Cannot cast class to string");
}

bool ClassValue::asBool(){
    throw new TypeException("Cannot cast class to bool");
}

Bignum ClassValue::asBignum(){
    throw new TypeException("Cannot cast class to number");
}

Values ClassValue::type() const{
    return Values::CLASS;
}

std::string ClassValue::stringType() const{ return cls -> stringType(); }

ClassValue::operator std::string(){ return std::string(*cls); }

namespace SlavaScript::lang{
    CMP(ClassValue){
        RCHECK(a.getName(), b.getName());
    }

    DEF_CMP(ClassValue)
}
