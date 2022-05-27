#include "arrayvalue.h"
#include "numbervalue.h"
#include "boolvalue.h"
#include "classvalue.h"
#include "functionvalue.h"
#include "integrationvalue.h"
#include "mapvalue.h"
#include "nullvalue.h"
#include "stringvalue.h"
#include "value.h"

using namespace SlavaScript::lang;

namespace SlavaScript::lang{
    bool operator==(Value const& a, Value const& b){
        if (a.type() != b.type()) return false;
        switch(a.type()){
            case Values::ARRAY : return *(ArrayValue*)(&a) == *(ArrayValue*)(&b);
            case Values::BOOL : return *(BoolValue*)(&a) == *(BoolValue*)(&b);
            case Values::NUMBER : return *(NumberValue*)(&a) == *(NumberValue*)(&b);
            case Values::FUNCTION : return *(FunctionValue*)(&a) == *(FunctionValue*)(&b);
            case Values::MAP : return *(MapValue*)(&a) == *(MapValue*)(&b);
            case Values::STRING : return *(StringValue*)(&a) == *(StringValue*)(&b);
            case Values::NULL_ : return *(NullValue*)(&a) == *(NullValue*)(&b);
            case Values::CLASS : return *(ClassValue*)(&a) == *(ClassValue*)(&b);
            case Values::INTEGRATION : return *(IntegrationValue*)(&a) == *(IntegrationValue*)(&b);
        }
    }

    bool operator<(Value const& a, Value const& b){
        if (a.type() != b.type()) return int(a.type()) < int(b.type());
        switch(a.type()){
            case Values::ARRAY : return *(ArrayValue*)(&a) < *(ArrayValue*)(&b);
            case Values::BOOL : return *(BoolValue*)(&a) < *(BoolValue*)(&b);
            case Values::NUMBER : return *(NumberValue*)(&a) < *(NumberValue*)(&b);
            case Values::FUNCTION : return *(FunctionValue*)(&a) < *(FunctionValue*)(&b);
            case Values::MAP : return *(MapValue*)(&a) < *(MapValue*)(&b);
            case Values::STRING : return *(StringValue*)(&a) < *(StringValue*)(&b);
            case Values::NULL_ : return *(NullValue*)(&a) < *(NullValue*)(&b);
            case Values::CLASS : return *(ClassValue*)(&a) < *(ClassValue*)(&b);
            case Values::INTEGRATION : return *(IntegrationValue*)(&a) < *(IntegrationValue*)(&b);
        }
    }

    COND_OPS(Value)
}
