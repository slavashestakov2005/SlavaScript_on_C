#include "mapvalue.h"
#include "nullvalue.h"
#include "functionvalue.h"
#include "../Exception/typeexception.h"
#include "../Exception/unknownpropertyexception.h"
#include "../Lib/utils.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::TypeException;
using SlavaScript::exceptions::UnknownPropertyException;


std::shared_ptr<MapValue> MapValue::add(std::shared_ptr<MapValue> map1, std::shared_ptr<MapValue> map2){
    std::shared_ptr<MapValue> result = SHARE(MapValue, );
    for(auto now : map1 -> map) result -> set(now.first, now.second);
    for(auto now : map2 -> map) result -> set(now.first, now.second);
    return result;
}


MapValue::MapValue() {}


std::shared_ptr<Value> MapValue::get(std::shared_ptr<Value> key){
    if (containsKey(key)) return map[key];
    else return NullValue::NULL_;
}

void MapValue::set(std::shared_ptr<Value> key, std::shared_ptr<Value> value){
    map[key] = value;
}

void MapValue::set(std::shared_ptr<Value> key, std::shared_ptr<Function> value){
    map[key] = SHARE(FunctionValue, value);
}

bool MapValue::isThisMap(){
    return thisMap;
}

void MapValue::setThisMap(bool thisMap){
    this -> thisMap = thisMap;
}

bool MapValue::containsKey(std::shared_ptr<Value> key){
    return map.find(key) != map.cend();
}


std::shared_ptr<Value> MapValue::copy(){
    std::shared_ptr<MapValue> newMap = SHARE(MapValue, );
    for(auto now : map){
        newMap -> set(now.first -> copy(), now.second -> copy());
    }
    return newMap;
}

double MapValue::asDouble(){
    throw new TypeException("Cannot cast map to number");
}

std::string MapValue::asString(){
    std::string result = "{";
    int siz = map.size(), i = 0;
    for(auto now : map){
        bool str = now.first -> type() == Values::STRING;
        result += std::string(*now.first);
        result += ": ";
        str = now.second -> type() == Values::STRING;
        result += std::string(*now.second);
        if (i < siz - 1) result += ", ";
        ++i;
    }
    result += "}";
    return result;
}

bool MapValue::asBool(){
    throw new TypeException("Cannot cast map to bool");
}

Bignum MapValue::asBignum(){
    throw new TypeException("Cannot cast map to number");
}

Values MapValue::type() const{
    return Values::MAP;
}

MapValue::operator std::string(){
    return asString();
}

std::shared_ptr<Value> MapValue::getDot(std::shared_ptr<Value> prop){
    if (!thisMap) throw new UnknownPropertyException(prop -> asString());
    if (containsKey(prop)) return map[prop];
    throw new std::logic_error("Cannot add property to 'this'");
}

std::shared_ptr<Value> MapValue::getBracket(std::shared_ptr<Value> prop){
    if (thisMap) throw new std::logic_error("Cannot used [] for 'this'");
    return get(prop);
}

void MapValue::setDot(std::shared_ptr<Value> key, std::shared_ptr<Value> value){
    if (!thisMap) throw new std::logic_error("Cannot used DOT for map");
    set(key, value);
}

void MapValue::setBracket(std::shared_ptr<Value> key, std::shared_ptr<Value> value){
    if (thisMap) throw new std::logic_error("Cannot used [] for 'this'");
    set(key, value);
}


int MapValue::size() const{
    return map.size();
}

std::map<std::shared_ptr<Value>, std::shared_ptr<Value>>::iterator MapValue::begin(){
    return map.begin();
}

std::map<std::shared_ptr<Value>, std::shared_ptr<Value>>::iterator MapValue::end(){
    return map.end();
}


namespace SlavaScript::lang{
    CMP(MapValue){
        CHECK(a.size(), b.size());
        auto nowa = a.map.begin();
        auto nowb = b.map.begin();
        while(nowa != a.map.end()){
            CHECK(nowa -> first -> type(), nowb -> first -> type());
            CHECK(*(nowa -> first), *(nowb -> first));
            CHECK(nowa -> second -> type(), nowb -> second -> type());
            CHECK(*(nowa -> second), *(nowb -> second));
            ++nowa;
            ++nowb;
        }
        return 0;
    }

    DEF_CMP(MapValue)
}
