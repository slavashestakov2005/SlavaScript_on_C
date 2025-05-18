#include <Exception/exceptions.h>
#include <Lib/classmethod.h>
#include <Lib/utils.h>
#include <Value/arrayvalue.h>
#include <Value/boolvalue.h>
#include <Value/mapvalue.h>


using namespace SlavaScript::lang;
using SlavaScript::exceptions::CastException;
using SlavaScript::exceptions::UnknownPropertyException;


namespace {
    CLASS_METHOD(Exists, MapValue::container_type)
        argsCount(1, values.size());
        return BoolValue::fromBool(instance.find(values[0]) != instance.end());
    CME

    CLASS_METHOD(Keys, MapValue::container_type)
        argsCount(0, values.size());
        std::vector<std::shared_ptr<Value>> keys;
        for (auto p : instance) keys.push_back(p.first);
        SH_RET(ArrayValue, keys);
    CME

    CLASS_METHOD(ValuesMap, MapValue::container_type)
        argsCount(0, values.size());
        std::vector<std::shared_ptr<Value>> keys;
        for (auto p : instance) keys.push_back(p.second);
        SH_RET(ArrayValue, keys);
    CME
}


std::shared_ptr<MapValue> MapValue::add(std::shared_ptr<MapValue> map1, std::shared_ptr<MapValue> map2) {
    std::shared_ptr<MapValue> result = SHARE(MapValue);
    for (auto now : map1 -> map) result -> set(now.first, now.second);
    for (auto now : map2 -> map) result -> set(now.first, now.second);
    return result;
}


MapValue::MapValue() {}


std::shared_ptr<Value> MapValue::get(std::shared_ptr<Value> key) {
    if (containsKey(key)) return map[key];
    else return NullValue::NULL_;
}

void MapValue::set(std::shared_ptr<Value> key, std::shared_ptr<Value> value) {
    map[key] = value;
}

void MapValue::set(std::shared_ptr<Value> key, std::shared_ptr<Function> value) {
    map[key] = SHARE(FunctionValue, value);
}

bool MapValue::containsKey(std::shared_ptr<Value> key) {
    return map.find(key) != map.cend();
}


std::shared_ptr<Value> MapValue::copy() {
    std::shared_ptr<MapValue> newMap = SHARE(MapValue);
    for (auto now : map) {
        newMap -> set(now.first -> copy(), now.second -> copy());
    }
    return newMap;
}

double MapValue::asDouble() {
    throw CastException(Values::MAP, Values::NUMBER);
}

std::string MapValue::asString() {
    std::string result = "{";
    int siz = map.size(), i = 0;
    for (auto now : map) {
        result += std::string(*now.first);
        result += ": ";
        result += std::string(*now.second);
        if (i < siz - 1) result += ", ";
        ++i;
    }
    result += "}";
    return result;
}

bool MapValue::asBool() {
    throw CastException(Values::MAP, Values::BOOL);
}

Bignum MapValue::asBignum() {
    throw CastException(Values::MAP, Values::NUMBER);
}

Values MapValue::type() const {
    return Values::MAP;
}

MapValue::operator std::string() {
    return asString();
}

std::shared_ptr<Value> MapValue::getDot(std::shared_ptr<Value> property) {
    std::string prop = property -> asString();
    ADD_METHOD("exists", Exists, map);
    ADD_METHOD("keys", Keys, map);
    ADD_METHOD("values", ValuesMap, map);
    throw UnknownPropertyException(prop);
}

std::shared_ptr<Value> MapValue::getBracket(std::shared_ptr<Value> prop) {
    return get(prop);
}

void MapValue::setBracket(std::shared_ptr<Value> key, std::shared_ptr<Value> value) {
    set(key, value);
}


int MapValue::size() const {
    return map.size();
}

MapValue::container_type::iterator MapValue::begin() {
    return map.begin();
}

MapValue::container_type::iterator MapValue::end() {
    return map.end();
}


namespace SlavaScript::lang {
    CMP(MapValue) {
        CHECK(a.size(), b.size());
        auto nowa = a.map.begin();
        auto nowb = b.map.begin();
        while (nowa != a.map.end()) {
            CHECK(nowa -> first -> type(), nowb -> first -> type());
            CHECK(*(nowa -> first), *(nowb -> first));
            CHECK(nowa -> second -> type(), nowb -> second -> type());
            CHECK(*(nowa -> second), *(nowb -> second));
            ++nowa;
            ++nowb;
        }
        return std::strong_ordering::equal;
    }

    DEF_EQ(MapValue)
}
