#include "objectvalue.h"
#include "stringvalue.h"
#include "functionvalue.h"
#include "../Lib/classes.h"
#include "../Exception/typeexception.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::TypeException;


std::shared_ptr<Value> ObjectValue::get(std::shared_ptr<Value> value){
    if (thisMap -> containsKey(value)) return thisMap -> get(value);
    if (value -> type() != Values::STRING) throw new TypeException("Cannot get non string member from class");
    std::string key = value -> asString();
    std::shared_ptr<ClassValue> cls = Classes::get(className);
    if (!cls -> isExists(key)) return nullptr;
    std::shared_ptr<Function> func = Classes::get(className) -> getFunction(key);
    std::shared_ptr<ClassMethodObject> method = SHARE_2(ClassMethodObject, func, shared_from_this());
    return SHARE(FunctionValue, CAST(Function, method));
}


ObjectValue::ObjectValue(std::string className) : className(className){
    thisMap -> setThisMap(true);
}


std::shared_ptr<MapValue> ObjectValue::getThisMap(){
    return thisMap;
}

void ObjectValue::addField(std::string name, std::shared_ptr<Value> value){
    thisMap -> set(SHARE(StringValue, name), value);
}

std::shared_ptr<Value> ObjectValue::getConstructor(){
    return get(SHARE(StringValue, className));
}

std::string ObjectValue::getName(){
    return className;
}


std::shared_ptr<Value> ObjectValue::copy(){
    std::shared_ptr<ObjectValue> val = SHARE(ObjectValue, this -> className);
    val -> thisMap = CAST(MapValue, this -> thisMap -> copy());
    return val;
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

ObjectValue::operator std::string(){
    return asString();
}

std::string ObjectValue::stringType() const{
    return "UserObject " + className;
}

std::shared_ptr<Value> ObjectValue::getDot(std::shared_ptr<Value> value){
    std::shared_ptr<Value> result = get(value);
    if (result) return result;
    throw new TypeException("Cannot get " + value -> asString() + " from " + className);
}

void ObjectValue::setDot(std::shared_ptr<Value> key, std::shared_ptr<Value> value){
    if (!thisMap -> containsKey(key)) throw new std::logic_error("Unable to add new field " + key -> asString() + " to class " + className);
    thisMap -> set(key, value);
}


namespace SlavaScript::lang{
    CMP(ObjectValue){
        RCHECK(a.className, b.className);
    }

    DEF_CMP(ObjectValue)
}
