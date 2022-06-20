#include "arrayvalue.h"
#include "numbervalue.h"
#include "boolvalue.h"
#include "classvalue.h"
#include "objectvalue.h"
#include "functionvalue.h"
#include "integrationvalue.h"
#include "mapvalue.h"
#include "nullvalue.h"
#include "stringvalue.h"
#include "value.h"

using namespace SlavaScript::lang;

#define RCHECK_CAST(cs, type) case Values::cs : RCHECK(*(type*)(&a), *(type*)(&b))

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

    DEF_CMP(Value)

    std::string Value::stringType() const{
        return getValueName(type());
    }

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
