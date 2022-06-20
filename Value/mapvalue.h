#ifndef MAPVALUE_H_INCLUDED
#define MAPVALUE_H_INCLUDED

#include <map>
#include "value.h"
#include "container.h"
#include "../Lib/function.h"

namespace SlavaScript::lang{
    class MapValue : public Value, Container<std::map<std::shared_ptr<Value>, std::shared_ptr<Value>, Comparator>>{
    private:
        std::map<std::shared_ptr<Value>, std::shared_ptr<Value>, Comparator> map;
        bool thisMap = false;
    public:
        static std::shared_ptr<MapValue> add(std::shared_ptr<MapValue> map1, std::shared_ptr<MapValue> map2);

        MapValue(int size){}
        MapValue(){}
        std::shared_ptr<Value> copy();

        std::shared_ptr<Value> get(std::shared_ptr<Value> key);
        void set(std::shared_ptr<Value> key, std::shared_ptr<Value> value);
        void set(std::shared_ptr<Value> key, std::shared_ptr<lang::Function> value);
        bool isThisMap();
        void setThisMap(bool thisMap);
        bool containsKey(std::shared_ptr<Value> key);

        int size() const;
        std::shared_ptr<Value> accessDot(std::shared_ptr<Value> property);
        std::shared_ptr<Value> accessBracket(std::shared_ptr<Value> property);
        std::map<std::shared_ptr<Value>, std::shared_ptr<Value>>::iterator begin();
        std::map<std::shared_ptr<Value>, std::shared_ptr<Value>>::iterator end();

        double asDouble();
        std::string asString();
        bool asBool();
        Bignum asBignum();
        Values type() const;
        operator std::string();
        ~MapValue(){}

        friend CMP(MapValue);
    };

    DEC_CMP(MapValue)
}

#endif // MAPVALUE_H_INCLUDED
