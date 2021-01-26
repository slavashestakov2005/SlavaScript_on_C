#ifndef ARRAYVALUE_H_INCLUDED
#define ARRAYVALUE_H_INCLUDED

#include <vector>
#include "container.h"
#include "value.h"

namespace SlavaScript{ namespace lang{
    class ArrayValue : public Value, Container{
    private:
        std::vector<Value*>* elements;
    public:
        ArrayValue(){}
        ArrayValue(int size);
        ArrayValue(std::vector<Value*> elem);
        ArrayValue(const ArrayValue& arra);
        std::vector<Value*> getCopyElement();
        Value* get(int index) const;
        void set(int index, Value* value);
        static ArrayValue* add(ArrayValue* array, Value* value);
        static ArrayValue* add(ArrayValue* array1, ArrayValue* array2);
        int size() const;
        std::vector<Value*>::iterator begin();
        std::vector<Value*>::iterator end();
        /** @return  throw: UnknownPropertyException*. */
        Value* accessDot(Value* property);
        Value* accessBracket(Value* property);
        /** @return  throw: TypeException*. */
        double asDouble();
        std::string asString();
        /** @return  throw: TypeException*. */
        bool asBool();
        /** @return  throw: TypeException*. */
        Bignum asBignum();
        Values type() const;
        operator std::string();
        ~ArrayValue();
        friend bool operator==(ArrayValue const& a, ArrayValue const& b);
        friend bool operator!=(ArrayValue const& a, ArrayValue const& b);
        friend bool operator<(ArrayValue const& a, ArrayValue const& b);
        friend bool operator<=(ArrayValue const& a, ArrayValue const& b);
        friend bool operator>(ArrayValue const& a, ArrayValue const& b);
        friend bool operator>=(ArrayValue const& a, ArrayValue const& b);
    };
}}

#endif // ARRAYVALUE_H_INCLUDED
