#include "objectvalue.h"
#include "../Exception/exceptions.h"
#include "../Lib/classmethod.h"
#include "../Lib/classes.h"
#include "../Lib/utils.h"
#include "classvalue.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::CastException;
using SlavaScript::exceptions::LogicException;
using SlavaScript::exceptions::UnknownPropertyException;


std::shared_ptr<Value> ObjectValue::get(std::shared_ptr<Value> value){
    if (thisMap -> containsKey(value)) return thisMap -> get(value);
    argType(Values::STRING, value);
    std::string key = value -> asString();
    std::shared_ptr<ClassValue> cls = Classes::get(className);
    if (!cls -> isExists(key)) return nullptr;
    std::shared_ptr<Function> func = Classes::get(className) -> getFunction(key);
    std::shared_ptr<ClassMethodObject> method = SHARE_2(ClassMethodObject, func, shared_from_this());
    return SHARE(FunctionValue, CAST(Function, method));
}


ObjectValue::ObjectValue(std::string className) : className(className) {}


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
    throw CastException(Values::CLASS, Values::NUMBER);
}

std::string ObjectValue::asString(){
    return "class " + className + "@" + std::string(*thisMap);
}

bool ObjectValue::asBool(){
    throw CastException(Values::CLASS, Values::BOOL);
}

Bignum ObjectValue::asBignum(){
    throw CastException(Values::CLASS, Values::NUMBER);
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
    throw UnknownPropertyException(value -> asString());
}

void ObjectValue::setDot(std::shared_ptr<Value> key, std::shared_ptr<Value> value){
    if (!thisMap -> containsKey(key)) throw LogicException("Unable to add new field " + key -> asString() + " to class " + className);
    thisMap -> set(key, value);
}


namespace SlavaScript::lang{
    CMP(ObjectValue){
        RCHECK(a.className, b.className);
    }

    DEF_CMP(ObjectValue)
}
