#include "objectvalue.h"
#include "stringvalue.h"
#include "functionvalue.h"
#include "../Lib/classes.h"
#include "../Exception/typeexception.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::TypeException;

ObjectValue::ObjectValue(std::string className) : className(className){
    thisMap -> setThisMap(true);
}

std::shared_ptr<Value> ObjectValue::copy(){
    std::shared_ptr<ObjectValue> val = SHARE(ObjectValue, this -> className);
    val -> thisMap = CAST(MapValue, this -> thisMap -> copy());
    return val;
}

std::shared_ptr<MapValue> ObjectValue::getThisMap(){
    return thisMap;
}

void ObjectValue::addField(std::string name, std::shared_ptr<Value> value){
    thisMap -> set(SHARE(StringValue, name), value);
}

std::shared_ptr<Value> ObjectValue::access(std::shared_ptr<Value> value){
    if (thisMap -> containsKey(value)) return thisMap -> get(value);
    std::shared_ptr<ClassMethod> method = Classes::get(className) -> get_function(value -> asString());
    return SHARE(FunctionValue, CAST(Function, method));
}

std::shared_ptr<Value> ObjectValue::getConstructor(){
    std::shared_ptr<Value> value = SHARE(StringValue, className);
    if (thisMap -> containsKey(value)) return thisMap -> get(value);
    std::shared_ptr<ClassValue> cls = Classes::get(className);
    if (!cls -> isExists(className)) return nullptr;
    std::shared_ptr<ClassMethod> method = cls -> get_function(className);
    return SHARE(FunctionValue, CAST(Function, method));
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
