#include "objectvalue.h"
#include "stringvalue.h"
#include "../Exception/typeexception.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::TypeException;

ObjectValue::ObjectValue(std::string className) : className(className){
    thisMap -> setThisMap(true);
}

std::shared_ptr<Value> ObjectValue::copy(){
    std::shared_ptr<ObjectValue> val = SHARE(ObjectValue, this -> className);
    val -> constructor = this -> constructor;
    val -> thisMap = CAST(MapValue, this -> thisMap -> copy());
    return val;
}

std::shared_ptr<MapValue> ObjectValue::getThisMap(){
    return thisMap;
}

void ObjectValue::addField(std::string name, std::shared_ptr<Value> value){
    thisMap -> set(SHARE(StringValue, name), value);
}

void ObjectValue::addMethod(std::string name, std::shared_ptr<ClassMethod> method){
    thisMap -> set(SHARE(StringValue, name), method);
    if (name == className) constructor = method;
}

void ObjectValue::callConstructor(std::vector<std::shared_ptr<Value>> values){
    if (constructor != nullptr) constructor -> execute(values);
}

std::shared_ptr<Value> ObjectValue::access(std::shared_ptr<Value> value){
    return thisMap -> get(value);
}

void ObjectValue::set(std::shared_ptr<Value> key, std::shared_ptr<Value> value){
    if (!thisMap -> containsKey(key)) throw new std::logic_error("Unable to add new field " + key -> asString() + " to class " + className);
    thisMap -> set(key, value);
}

std::shared_ptr<Value> ObjectValue::get(std::shared_ptr<Value> key){
    if (!thisMap -> containsKey(key)){
        std::string s = "Field " + std::string(*key) + " undefined in " + className;
        throw new std::logic_error(s.c_str());
    }
    return thisMap -> get(key);
}

std::string ObjectValue::get_name(){
    return className;
}

double ObjectValue::asDouble(){
    throw new TypeException("Cannot cast class to double");
}

std::string ObjectValue::asString(){
    return "class " + className + "@" + std::string(*thisMap);
}

bool ObjectValue::asBool(){
    throw new TypeException("Cannot cast class to bool");
}

Bignum ObjectValue::asBignum(){
    throw new TypeException("Cannot cast class to number");
}

Values ObjectValue::type() const{
    return Values::OBJECT;
}

std::string ObjectValue::string_type() const{
    return "UserObject " + className;
}

ObjectValue::operator std::string(){
    return asString();
}

namespace SlavaScript::lang{
    bool operator==(ObjectValue const& a, ObjectValue const& b){
        return a.className == b.className;
    }

    bool operator<(ObjectValue const& a, ObjectValue const& b){
        return a.className < b.className;
    }

    COND_OPS(ObjectValue)
}
