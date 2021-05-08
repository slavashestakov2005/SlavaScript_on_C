#ifndef ARRAYVALUE_H_INCLUDED
#define ARRAYVALUE_H_INCLUDED

#include <vector>
#include "container.h"
#include "value.h"

namespace SlavaScript{ namespace lang{
    class ArrayValue : public Value, Container<std::vector<std::shared_ptr<Value>>>{
    private:
        std::vector<std::shared_ptr<Value>> elements;
    public:
        static std::shared_ptr<ArrayValue> add(std::shared_ptr<ArrayValue> array, std::shared_ptr<Value> value);
        static std::shared_ptr<ArrayValue> add(std::shared_ptr<ArrayValue> array1, std::shared_ptr<ArrayValue> array2);

        ArrayValue(){}
        ArrayValue(int size);
        ArrayValue(std::vector<std::shared_ptr<Value>> elem);
        ArrayValue(const ArrayValue& arra);

        std::vector<std::shared_ptr<Value>> getCopyElement();
        std::shared_ptr<Value> get(int index) const;
        void set(int index, std::shared_ptr<Value> value);

        int size() const;
        std::shared_ptr<Value> accessDot(std::shared_ptr<Value> property);
        std::shared_ptr<Value> accessBracket(std::shared_ptr<Value> property);
        std::vector<std::shared_ptr<Value>>::iterator begin();
        std::vector<std::shared_ptr<Value>>::iterator end();

        double asDouble();
        std::string asString();
        bool asBool();
        Bignum asBignum();
        Values type() const;
        operator std::string();
        ~ArrayValue(){}

        friend bool operator==(ArrayValue const& a, ArrayValue const& b);
        friend bool operator!=(ArrayValue const& a, ArrayValue const& b);
        friend bool operator<(ArrayValue const& a, ArrayValue const& b);
        friend bool operator<=(ArrayValue const& a, ArrayValue const& b);
        friend bool operator>(ArrayValue const& a, ArrayValue const& b);
        friend bool operator>=(ArrayValue const& a, ArrayValue const& b);
    };
}}

#endif // ARRAYVALUE_H_INCLUDED
