#ifndef MAPVALUE_H_INCLUDED
#define MAPVALUE_H_INCLUDED

#include <map>
#include "value.h"
#include "../Lib/function.h"

namespace SlavaScript{ namespace lang{
    class Comparator{
    public:
        bool operator()(Value* a, Value* b){
            return (*a) < (*b);
        }
    };

    class MapValue : public Value{
    private:
        std::map<Value*, Value*, Comparator> map;
        bool thisMap = false;
    public:
        MapValue(int size){}
        MapValue(){}
        Value* get(Value* key);
        void set(Value* key, Value* value);
        void set(Value* key, lang::Function* value);
        bool isThisMap();
        void setThisMap(bool thisMap);
        int size() const;
        bool containsKey(Value* key);
        MapValue* getCopyElement();
        static MapValue* add(MapValue* map1, MapValue* map2);
        std::map<Value*, Value*>::iterator begin();
        std::map<Value*, Value*>::iterator end();
        /** @return  throw: TypeException*. */
        double asDouble();
        std::string asString();
        /** @return  throw: TypeException*. */
        bool asBool();
        /** @return  throw: TypeException*. */
        Bignum asBignum();
        Values type() const;
        operator std::string();
        ~MapValue(){}
        friend bool operator==(MapValue const& a, MapValue const& b);
        friend bool operator!=(MapValue const& a, MapValue const& b);
        friend bool operator<(MapValue const& a, MapValue const& b);
        friend bool operator<=(MapValue const& a, MapValue const& b);
        friend bool operator>(MapValue const& a, MapValue const& b);
        friend bool operator>=(MapValue const& a, MapValue const& b);
    };
}}

#endif // MAPVALUE_H_INCLUDED
