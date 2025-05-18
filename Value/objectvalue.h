#pragma once

#include <Value/mapvalue.h>


namespace SlavaScript::lang {
    class ObjectValue : public Value, public std::enable_shared_from_this<ObjectValue>{
    private:
        std::string className;
        std::shared_ptr<MapValue> thisMap = SHARE(MapValue);
        std::shared_ptr<Value> get(std::shared_ptr<Value> key);
    public:
        ObjectValue(std::string className);

        void addField(std::string name, std::shared_ptr<Value> value);
        std::shared_ptr<Value> getConstructor();
        std::string getName();

        std::shared_ptr<Value> copy() override;
        double asDouble() override;
        std::string asString() override;
        bool asBool() override;
        Bignum asBignum() override;
        Values type() const override;
        operator std::string() override;
        std::string stringType() const override;
        std::shared_ptr<Value> getDot(std::shared_ptr<Value> value) override;
        void setDot(std::shared_ptr<Value> key, std::shared_ptr<Value> value) override;

        friend CMP(ObjectValue);
        friend EQ(ObjectValue);
    };
}
