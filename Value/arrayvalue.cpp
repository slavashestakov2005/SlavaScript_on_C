#include "arrayvalue.h"
#include "../Exception/exceptions.h"
#include "../Lib/classmethod.h"
#include "../Lib/utils.h"
#include "boolvalue.h"
#include "numbervalue.h"
#include <algorithm>

using namespace SlavaScript::lang;
using SlavaScript::exceptions::CastException;
using SlavaScript::exceptions::UnknownPropertyException;


namespace {
    CLASS_METHOD(IsEmpty, ArrayValue::container_type)
        argsCount(0, values.size());
        return BoolValue::fromBool(instance.empty());
    CME

    CLASS_METHOD(Length, ArrayValue::container_type)
        argsCount(0, values.size());
        SH_RET(NumberValue, instance.size());
    CME

    CLASS_METHOD(Sort, ArrayValue::container_type)
        argsCount({0, 1, 2}, values.size());
        if (values.size() == 0) std::sort(instance.begin(), instance.end(), comparator);
        else {
            argType(Values::FUNCTION, values[0]);
            std::shared_ptr<Function> func = CAST(FunctionValue, values[0]) -> getFunction();
            bool binary = false;
            if (values.size() == 2) binary = values[1] -> asBool();
            if (!binary) std::sort(instance.begin(), instance.end(), [func](std::shared_ptr<Value> l, std::shared_ptr<Value> r) -> bool { return comparator(func -> execute({l}), func -> execute({r})); });
            else std::sort(instance.begin(), instance.end(), [func](std::shared_ptr<Value> l, std::shared_ptr<Value> r) -> bool { return func -> execute({l, r}) -> asBool(); });
        }
        return SHARE(ArrayValue, instance);
    CME
}


std::shared_ptr<ArrayValue> ArrayValue::add(std::shared_ptr<ArrayValue> array, std::shared_ptr<Value> value){
    container_type vec;
    int size = array -> elements.size() + 1;
    for(int i = 0; i < size - 1; ++i) vec.push_back(array -> get(i));
    vec.push_back(value);
    SH_RET(ArrayValue, vec);
}

std::shared_ptr<ArrayValue> ArrayValue::add(std::shared_ptr<ArrayValue> array1, std::shared_ptr<ArrayValue> array2){
    container_type vec;
    int size = array1 -> elements.size();
    for(int i = 0; i < size; ++i) vec.push_back(array1 -> get(i));
    size = array2 -> elements.size();
    for(int i = 0; i < size; ++i) vec.push_back(array2 -> get(i));
    SH_RET(ArrayValue, vec);
}


ArrayValue::ArrayValue() {}

ArrayValue::ArrayValue(int size){
    elements = container_type(size);
}

ArrayValue::ArrayValue(ArrayValue::container_type elem){
    elements = container_type(elem.size());
    for(int i = 0; i < elem.size(); ++i){
        elements[i] = elem[i];
    }
}

ArrayValue::ArrayValue(const ArrayValue& arra){
    (*this) = ArrayValue(arra.elements);
}


std::shared_ptr<Value> ArrayValue::get(int index) const{
    return elements[index];
}

void ArrayValue::set(int index, std::shared_ptr<Value> value){
    elements[index] = value;
}


std::shared_ptr<Value> ArrayValue::copy(){
    int size = elements.size();
    std::shared_ptr<ArrayValue> arr = SHARE(ArrayValue, size);
    for(int i = 0; i < size; ++i) arr -> set(i, get(i) -> copy());
    return arr;
}

double ArrayValue::asDouble(){
    throw CastException(Values::ARRAY, Values::NUMBER);
}

std::string ArrayValue::asString(){
    std::string result = "[";
    for(unsigned i = 0; i < elements.size(); ++i){
        result += std::string(*elements[i]);
        if (i < elements.size() - 1) result += ", ";
    }
    result += "]";
    return result;
}

bool ArrayValue::asBool(){
    throw CastException(Values::ARRAY, Values::BOOL);
}

Bignum ArrayValue::asBignum(){
    throw CastException(Values::ARRAY, Values::NUMBER);
}

Values ArrayValue::type() const{
    return Values::ARRAY;
}

ArrayValue::operator std::string(){
    return asString();
}

std::shared_ptr<Value> ArrayValue::getDot(std::shared_ptr<Value> property){
    std::string prop = property -> asString();
    ADD_METHOD("length", Length, elements);
    ADD_METHOD("is_empty", IsEmpty, elements);
    ADD_METHOD("sort", Sort, elements);
    throw UnknownPropertyException(prop);
}

std::shared_ptr<Value> ArrayValue::getBracket(std::shared_ptr<Value> property){
    return get((int)property -> asDouble());
}

void ArrayValue::setBracket(std::shared_ptr<Value> key, std::shared_ptr<Value> value){
    int arrayIndex = (int) key -> asDouble();
    set(arrayIndex, value);
}


int ArrayValue::size() const{
    return elements.size();
}

ArrayValue::container_type::iterator ArrayValue::begin(){
    return elements.begin();
}

ArrayValue::container_type::iterator ArrayValue::end(){
    return elements.end();
}


namespace SlavaScript::lang{
    CMP(ArrayValue){
        CHECK(a.size(), b.size());
        for(int i = 0; i < a.size(); ++i){
            std::shared_ptr<Value> val1 = a.get(i);
            std::shared_ptr<Value> val2 = b.get(i);
            CHECK(val1 -> type(), val2 -> type());
            CHECK(*val1, *val2);
        }
        return 0;
    }

    DEF_CMP(ArrayValue)
}
