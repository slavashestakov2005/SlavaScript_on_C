#include "value.h"
#include "../Exception/exceptions.h"
#include "arrayvalue.h"
#include "boolvalue.h"
#include "classvalue.h"
#include "functionvalue.h"
#include "integrationvalue.h"
#include "mapvalue.h"
#include "nullvalue.h"
#include "numbervalue.h"
#include "stringvalue.h"
#include "objectvalue.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::TypeException;


#define RCHECK_CAST(cs, type) case Values::cs : RCHECK(*(type*)(&a), *(type*)(&b))


std::shared_ptr<Value> Value::getDot(std::shared_ptr<Value> property){
    throw TypeException("Cannot get property using . for " + stringType());
}

std::shared_ptr<Value> Value::getBracket(std::shared_ptr<Value> property){
    throw TypeException("Cannot get property using [] for " + stringType());
}

void Value::setDot(std::shared_ptr<Value> key, std::shared_ptr<Value> value){
    throw TypeException("Cannot set property using . for " + stringType());
}

void Value::setBracket(std::shared_ptr<Value> key, std::shared_ptr<Value> value){
    throw TypeException("Cannot set property using [] for " + stringType());
}

std::string Value::stringType() const{
    return getValueName(type());
}

Value::~Value() {}


namespace SlavaScript::lang{
    CMP(Value){
        CHECK(a.type(), b.type());
        switch(a.type()){
            RCHECK_CAST(ARRAY, ArrayValue);
            RCHECK_CAST(BOOL, BoolValue);
            RCHECK_CAST(NUMBER, NumberValue);
            RCHECK_CAST(FUNCTION, FunctionValue);
            RCHECK_CAST(MAP, MapValue);
            RCHECK_CAST(STRING, StringValue);
            RCHECK_CAST(NULL_, NullValue);
            RCHECK_CAST(OBJECT, ObjectValue);
            RCHECK_CAST(CLASS, ClassValue);
            RCHECK_CAST(INTEGRATION, IntegrationValue);
        }
    }

    DEF_EQ(Value)

    bool comparator(std::shared_ptr<Value> const& a, std::shared_ptr<Value> const& b){
        return (*a) < (*b);
    }

    bool equals(std::shared_ptr<Value> const& a, std::shared_ptr<Value> const& b){
        return (*a) == (*b);
    }

    bool Comparator::operator()(std::shared_ptr<Value> const& a, std::shared_ptr<Value> const& b) const{
        return comparator(a, b);
    }
}
