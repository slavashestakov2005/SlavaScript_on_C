#pragma once

#include <map>

#include <Lib/function.h>
#include <Value/container.h>
#include <Value/value.h>


namespace SlavaScript::lang {
    class MapValue : public Value, public Container<std::map<std::shared_ptr<Value>, std::shared_ptr<Value>, Comparator>>{
    private:
        container_type map;
    public:
        static std::shared_ptr<MapValue> add(std::shared_ptr<MapValue> map1, std::shared_ptr<MapValue> map2);

        MapValue();

        std::shared_ptr<Value> get(std::shared_ptr<Value> key);
        void set(std::shared_ptr<Value> key, std::shared_ptr<Value> value);
        void set(std::shared_ptr<Value> key, std::shared_ptr<lang::Function> value);
        bool containsKey(std::shared_ptr<Value> key);

        std::shared_ptr<Value> copy() override;
        double asDouble() override;
        std::string asString() override;
        bool asBool() override;
        Bignum asBignum() override;
        Values type() const override;
        operator std::string() override;
        std::shared_ptr<Value> getDot(std::shared_ptr<Value> property) override;
        std::shared_ptr<Value> getBracket(std::shared_ptr<Value> property) override;
        void setBracket(std::shared_ptr<Value> key, std::shared_ptr<Value> value) override;

        int size() const override;
        container_type::iterator begin() override;
        container_type::iterator end() override;

        friend CMP(MapValue);
        friend EQ(MapValue);
    };
}
