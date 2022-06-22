#ifndef ARRAYVALUE_H_INCLUDED
#define ARRAYVALUE_H_INCLUDED

#include <vector>
#include "container.h"
#include "value.h"

namespace SlavaScript::lang{
    class ArrayValue : public Value, public Container<std::vector<std::shared_ptr<Value>>>{
    private:
        container_type elements;
    public:
        static std::shared_ptr<ArrayValue> add(std::shared_ptr<ArrayValue> array, std::shared_ptr<Value> value);
        static std::shared_ptr<ArrayValue> add(std::shared_ptr<ArrayValue> array1, std::shared_ptr<ArrayValue> array2);

        ArrayValue();
        ArrayValue(int size);
        ArrayValue(container_type elem);
        ArrayValue(const ArrayValue& arra);

        std::shared_ptr<Value> get(int index) const;
        void set(int index, std::shared_ptr<Value> value);

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

        friend CMP(ArrayValue);
    };

    DEC_CMP(ArrayValue)
}

#endif // ARRAYVALUE_H_INCLUDED
