#include "mapvalue.h"
#include "nullvalue.h"
#include "functionvalue.h"
#include "../Exception/typeexception.h"
#include "../Exception/unknownpropertyexception.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::TypeException;
using SlavaScript::exceptions::UnknownPropertyException;

std::shared_ptr<Value> MapValue::copy(){
    std::shared_ptr<MapValue> newMap = SHARE(MapValue, );
    for(auto now : map){
        newMap -> set(now.first -> copy(), now.second -> copy());
    }
    return newMap;
}

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

int MapValue::size() const{
    return map.size();
}

bool MapValue::containsKey(std::shared_ptr<Value> key){
    return map.find(key) != map.cend();
}

std::shared_ptr<MapValue> MapValue::add(std::shared_ptr<MapValue> map1, std::shared_ptr<MapValue> map2){
    std::shared_ptr<MapValue> result = SHARE(MapValue, );
    for(auto now : map1 -> map) result -> set(now.first, now.second);
    for(auto now : map2 -> map) result -> set(now.first, now.second);
    return result;
}

std::shared_ptr<Value> MapValue::accessDot(std::shared_ptr<Value> prop){
    if (thisMap){
        if (containsKey(prop)) return map[prop];
        throw new std::logic_error("Cannot add property to 'this'");
    }
    throw new UnknownPropertyException(prop -> asString());
}

std::shared_ptr<Value> MapValue::accessBracket(std::shared_ptr<Value> prop){
    if (!thisMap) return get(prop);
    throw new std::logic_error("Cannot used [] for 'this'");
}

std::map<std::shared_ptr<Value>, std::shared_ptr<Value>>::iterator MapValue::begin(){
    return map.begin();
}

std::map<std::shared_ptr<Value>, std::shared_ptr<Value>>::iterator MapValue::end(){
    return map.end();
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

bool SlavaScript::lang::operator==(MapValue const& a, MapValue const& b){
    if (a.size() != b.size()) return false;
    auto nowa = a.map.begin();
    auto nowb = b.map.begin();
    while(nowa != a.map.end()){
        if (nowa -> first -> type() != nowb -> first -> type()) return false;
        if (nowa -> second -> type() != nowb -> second -> type()) return false;
        if (*(nowa -> first) != *(nowb -> first)) return false;
        if (*(nowa -> second) != *(nowb -> second)) return false;
        ++nowa;
        ++nowb;
    }
    return true;
}

bool SlavaScript::lang::operator!=(MapValue const& a, MapValue const& b){
    return !(a == b);
}

bool SlavaScript::lang::operator<(MapValue const& a, MapValue const& b){
    if (a.size() < b.size()) return true;
    if (a.size() > b.size()) return false;
    auto nowa = a.map.begin();
    auto nowb = b.map.begin();
    while(nowa != a.map.end()){
        if (nowa -> first -> type() < nowb -> first -> type()) return true;
        if (nowa -> first -> type() > nowb -> first -> type()) return false;
        if (*(nowa -> first) < *(nowb -> first)) return true;
        if (*(nowa -> first) > *(nowb -> first)) return false;
        if (nowa -> second -> type() < nowb -> second -> type()) return true;
        if (nowa -> second -> type() > nowb -> second -> type()) return false;
        if (*(nowa -> second) < *(nowb -> second)) return true;
        if (*(nowa -> second) > *(nowb -> second)) return false;
        ++nowa;
        ++nowb;
    }
    return false;
}

bool SlavaScript::lang::operator<=(MapValue const& a, MapValue const& b){
    return !(a > b);
}

bool SlavaScript::lang::operator>(MapValue const& a, MapValue const& b){
    return b < a;
}

bool SlavaScript::lang::operator>=(MapValue const& a, MapValue const& b){
    return !(a < b);
}
