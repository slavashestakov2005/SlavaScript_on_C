// [[not imported module]]
#include "global.h"
#include "../Value/arrayvalue.h"
#include "../Value/numbervalue.h"
#include "../Lib/functions.h"
#include "../Value/functionvalue.h"
#include "../Value/classvalue.h"
#include "../Value/mapvalue.h"
#include "../Lib/variables.h"
#include "../Value/boolvalue.h"
#include "../Value/nullvalue.h"
#include "../Value/stringvalue.h"
#include "../Exception/argumentsmismatchexception.h"
#include <iostream>

using namespace SlavaScript::lang;
using namespace SlavaScript::modules::global_f;
using SlavaScript::modules::Global;
using SlavaScript::exceptions::ArgumentsMismatchException;

namespace SlavaScript{ namespace modules{ namespace global_out{
    bool operator_lt(Value const& a, Value const& b){
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
        }
    }
}}}

namespace SlavaScript{ namespace modules{ namespace global_f{
    Function* input = new FunctionModule([](std::vector<Value*> values) -> Value*{
        for(int i = 0; i < values.size(); ++i) std::cout << std::string(*(values[i]));
        std::string str;
        getline(std::cin, str);
        return new StringValue(str);
    });

    Function* max = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() == 0) throw new ArgumentsMismatchException("One and least arguments expected");
        Value* ans = values[0];
        for(int i = 1; i < values.size(); ++i) ans = global_out::operator_lt(*ans, *values[i]) ? values[i] : ans;
        return ans;
    });

    Function* min = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() == 0) throw new ArgumentsMismatchException("One and least arguments expected");
        Value* ans = values[0];
        for(int i = 1; i < values.size(); ++i) ans = global_out::operator_lt(*ans, *values[i]) ? ans : values[i];
        return ans;
    });
}}}

void Global::initConstants(){
    Variables::set("true", BoolValue::TRUE_);
    Variables::set("false", BoolValue::FALSE_);
    Variables::set("null", NullValue::NULL_);
}

void Global::initFunctions(){
    Functions::set("input", input);
    Functions::set("max", max);
    Functions::set("min", min);
}
