#include "classvalue.h"
#include "stringvalue.h"
#include "../Exception/typeexception.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::TypeException;

ClassValue::ClassValue(std::string className) : className(className){
    thisMap -> setThisMap(true);
};

std::shared_ptr<Value> ClassValue::copy(){
    std::shared_ptr<ClassValue> val = SHARE(ClassValue, this -> className);
    val -> constructor = this -> constructor;
    val -> thisMap = CAST(MapValue, this -> thisMap -> copy());
    return val;
}

std::shared_ptr<MapValue> ClassValue::getThisMap(){
    return thisMap;
}

void ClassValue::addField(std::string name, std::shared_ptr<Value> value){
    thisMap -> set(SHARE(StringValue, name), value);
}

void ClassValue::addMethod(std::string name, std::shared_ptr<ClassMethod> method){
    thisMap -> set(SHARE(StringValue, name), method);
    if (name == className) constructor = method;
}

void ClassValue::callConstructor(std::vector<std::shared_ptr<Value>> values){
    if (constructor != nullptr) constructor -> execute(values);
}

std::shared_ptr<Value> ClassValue::access(std::shared_ptr<Value> value){
    return thisMap -> get(value);
}

void ClassValue::set(std::shared_ptr<Value> key, std::shared_ptr<Value> value){
    if (!thisMap -> containsKey(key)) throw new std::logic_error("Unable to add new field " + key -> asString() + " to class " + className);
    thisMap -> set(key, value);
}

std::shared_ptr<Value> ClassValue::get(std::shared_ptr<Value> key){
    if (!thisMap -> containsKey(key)){
        std::string s = "Field " + std::string(*key) + " undefined in " + className;
        throw new std::logic_error(s.c_str());
    }
    return thisMap -> get(key);
}

double ClassValue::asDouble(){
    throw new TypeException("Cannot cast class to double");
}

std::string ClassValue::asString(){
    return "class " + className + "@" + std::string(*thisMap);
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

ClassValue::operator std::string(){
    return asString();
}

namespace SlavaScript{ namespace lang{
    bool operator==(ClassValue const& a, ClassValue const& b){
        return a.className == b.className;
    }

    bool operator<(ClassValue const& a, ClassValue const& b){
        return a.className < b.className;
    }

    COND_OPS(ClassValue)
}}
