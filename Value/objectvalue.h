#ifndef OBJECTVALUE_H_INCLUDED
#define OBJECTVALUE_H_INCLUDED

#include "mapvalue.h"
#include "../Lib/classmethod.h"

namespace SlavaScript::lang{
    class ObjectValue : public Value{
    private:
        std::string className;
        std::shared_ptr<MapValue> thisMap = SHARE(MapValue, 1);
        std::shared_ptr<Value> get(std::shared_ptr<Value> key);
    public:
        ObjectValue(std::string className);
        std::shared_ptr<Value> copy();

        std::shared_ptr<MapValue> getThisMap();
        void addField(std::string name, std::shared_ptr<Value> value);
        std::shared_ptr<Value> getConstructor();
        std::shared_ptr<Value> access(std::shared_ptr<Value> value);
        void set(std::shared_ptr<Value> key, std::shared_ptr<Value> value);
        std::string getName();

        double asDouble();
        std::string asString();
        bool asBool();
        Bignum asBignum();
        Values type() const;
        std::string stringType() const;
        operator std::string();
        ~ObjectValue(){}

        friend CMP(ObjectValue);
    };

    DEC_CMP(ObjectValue)
}

#endif // OBJECTVALUE_H_INCLUDED
