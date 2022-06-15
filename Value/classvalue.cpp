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

std::string ClassValue::get_name() const { return cls -> get_name(); }

std::shared_ptr<ClassMethod> ClassValue::get_function(std::string func){ return cls -> get_function(func); }

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

std::string ClassValue::string_type() const{ return cls -> string_type(); }

ClassValue::operator std::string(){ return std::string(*cls); }

namespace SlavaScript::lang{
    bool operator==(ClassValue const& a, ClassValue const& b){
        return a.get_name() == b.get_name();
    }

    bool operator<(ClassValue const& a, ClassValue const& b){
        return a.get_name() < b.get_name();
    }

    COND_OPS(ClassValue)
}
