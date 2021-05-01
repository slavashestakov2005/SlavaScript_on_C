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
#include <windows.h>

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

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
}}}

namespace SlavaScript{ namespace modules{ namespace global_f{
    CREATE_FUNCTION(input)
        for(int i = 0; i < values.size(); ++i) std::cout << std::string(*(values[i]));
        std::string str;
        getline(std::cin, str);
        SH_RET(StringValue, str);
    });

    CREATE_FUNCTION(max)
        if (values.size() == 0) throw new ArgumentsMismatchException("One and least arguments expected");
        std::shared_ptr<Value> ans = values[0];
        for(int i = 1; i < values.size(); ++i) ans = global_out::operator_lt(*ans, *values[i]) ? values[i] : ans;
        return ans;
    });

    CREATE_FUNCTION(min)
        if (values.size() == 0) throw new ArgumentsMismatchException("One and least arguments expected");
        std::shared_ptr<Value> ans = values[0];
        for(int i = 1; i < values.size(); ++i) ans = global_out::operator_lt(*ans, *values[i]) ? ans : values[i];
        return ans;
    });

    CREATE_FUNCTION(set_color)
        int color = 0;
        if (values.size() > 1) throw new ArgumentsMismatchException("Zero or one argument expected");
        if (values.size() > 0 && values[0] -> type() != Values::NUMBER) throw new TypeException("Number expected in first argument");
        if (values.size() == 1) color = values[0] -> asDouble();
        SetConsoleTextAttribute(global_out::handle, color);
        return NullValue::NULL_;
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
    Functions::set("set_color", set_color);
}
