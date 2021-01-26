#include "classvalue.h"
#include "stringvalue.h"
#include "../Exception/typeexception.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::TypeException;

ClassValue::ClassValue(std::string className) : className(className){
    thisMap -> setThisMap(true);
};

MapValue* ClassValue::getThisMap(){
    return thisMap;
}

void ClassValue::addField(std::string name, Value* value){
    thisMap -> set(new StringValue(name), value);
}

void ClassValue::addMethod(std::string name, ClassMethod* method){
    thisMap -> set(new StringValue(name), method);
    if (name == className) constructor = method;
}

void ClassValue::callConstructor(std::vector<Value*> values){
    if (constructor != nullptr) constructor -> execute(values);
}

Value* ClassValue::access(Value* value){
    return thisMap -> get(value);
}

void ClassValue::set(Value* key, Value* value){
    if (!thisMap -> containsKey(key)) throw new std::logic_error("Unable to add new field " + key -> asString() + " to class " + className);
    thisMap -> set(key, value);
}

Value* ClassValue::get(Value* key){
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

ClassValue::~ClassValue(){
    delete thisMap;
    thisMap = nullptr;
    delete constructor;
    constructor = nullptr;
}

bool SlavaScript::lang::operator==(ClassValue const& a, ClassValue const& b){
    return a.className == b.className;
}

bool SlavaScript::lang::operator!=(ClassValue const& a, ClassValue const& b){
    return a.className != b.className;
}

bool SlavaScript::lang::operator<(ClassValue const& a, ClassValue const& b){
    return a.className < b.className;
}

bool SlavaScript::lang::operator<=(ClassValue const& a, ClassValue const& b){
    return a.className <= b.className;
}

bool SlavaScript::lang::operator>(ClassValue const& a, ClassValue const& b){
    return a.className > b.className;
}

bool SlavaScript::lang::operator>=(ClassValue const& a, ClassValue const& b){
    return a.className >= b.className;
}
