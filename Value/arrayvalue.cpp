#include "arrayvalue.h"
#include "boolvalue.h"
#include "classvalue.h"
#include "stringvalue.h"
#include "../Exception/argumentsmismatchexception.h"
#include "../Exception/typeexception.h"
#include "../Exception/unknownpropertyexception.h"
#include "../Expression/valueexpression.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::ArgumentsMismatchException;
using SlavaScript::exceptions::UnknownPropertyException;
using SlavaScript::exceptions::TypeException;

namespace {
    CLASS_METHOD(IsEmpty, std::vector<std::shared_ptr<Value>>)
        if (values.size()) throw new ArgumentsMismatchException("Zero arguments expected");
        return BoolValue::fromBool(instance.empty());
    CME

    CLASS_METHOD(Length, std::vector<std::shared_ptr<Value>>)
        if (values.size()) throw new ArgumentsMismatchException("Zero arguments expected");
        SH_RET(NumberValue, instance.size());
    CME
}

ArrayValue::ArrayValue(int size){
    elements = std::vector<std::shared_ptr<Value>>(size);
}

ArrayValue::ArrayValue(std::vector<std::shared_ptr<Value>> elem){
    elements = std::vector<std::shared_ptr<Value>>(elem.size());
    for(int i = 0; i < elem.size(); ++i){
        elements[i] = elem[i];
    }
}

ArrayValue::ArrayValue(const ArrayValue& arra){
    (*this) = ArrayValue(arra.elements);
}

std::shared_ptr<Value> ArrayValue::copy(){
    int size = elements.size();
    std::shared_ptr<ArrayValue> arr = SHARE(ArrayValue, size);
    for(int i = 0; i < size; ++i) arr -> set(i, get(i) -> copy());
    return arr;
}

std::shared_ptr<Value> ArrayValue::get(int index) const{
    return elements[index];
}

void ArrayValue::set(int index, std::shared_ptr<Value> value){
    elements[index] = value;
}

std::shared_ptr<ArrayValue> ArrayValue::add(std::shared_ptr<ArrayValue> array, std::shared_ptr<Value> value){
    std::vector<std::shared_ptr<Value>> vec;
    int size = array -> elements.size() + 1;
    for(int i = 0; i < size - 1; ++i) vec.push_back(array -> get(i));
    vec.push_back(value);
    SH_RET(ArrayValue, vec);
}

std::shared_ptr<ArrayValue> ArrayValue::add(std::shared_ptr<ArrayValue> array1, std::shared_ptr<ArrayValue> array2){
    std::vector<std::shared_ptr<Value>> vec;
    int size = array1 -> elements.size();
    for(int i = 0; i < size; ++i) vec.push_back(array1 -> get(i));
    size = array2 -> elements.size();
    for(int i = 0; i < size; ++i) vec.push_back(array2 -> get(i));
    SH_RET(ArrayValue, vec);
}

int ArrayValue::size() const{
    return elements.size();
}

std::vector<std::shared_ptr<Value>>::iterator ArrayValue::begin(){
    return elements.begin();
}

std::vector<std::shared_ptr<Value>>::iterator ArrayValue::end(){
    return elements.end();
}

std::shared_ptr<Value> ArrayValue::accessDot(std::shared_ptr<Value> property){
    std::string prop = property -> asString();
    if (prop == "length") SH_RET(FunctionValue, new Length(elements));
    if (prop == "is_empty") SH_RET(FunctionValue, new IsEmpty(elements));
    throw new UnknownPropertyException(prop);
}

std::shared_ptr<Value> ArrayValue::accessBracket(std::shared_ptr<Value> property){
    return get((int)property -> asDouble());
}

double ArrayValue::asDouble(){
    throw new TypeException("Cannot cast array to double");
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
    throw new TypeException("Cannot cast array to bool");
}

Bignum ArrayValue::asBignum(){
    throw new TypeException("Cannot cast array to number");
}

Values ArrayValue::type() const{
    return Values::ARRAY;
}

ArrayValue::operator std::string(){
    return asString();
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
