// [[not imported module]]
#include "global.h"
#include "../Lib/functions.h"
#include "../Lib/utils.h"
#include "../Lib/variables.h"
#include "../Value/boolvalue.h"
#include "../Value/nullvalue.h"
#include "../Value/stringvalue.h"
#include <iostream>
#include <windows.h>

using namespace SlavaScript::lang;
using namespace SlavaScript::modules::global_f;
using SlavaScript::modules::Global;

namespace SlavaScript::modules::global_out{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
}

namespace SlavaScript::modules::global_f{
    CREATE_FUNCTION(input)
        for(int i = 0; i < values.size(); ++i) std::cout << std::string(*(values[i]));
        std::string str;
        getline(std::cin, str);
        SH_RET(StringValue, str);
    FE

    CREATE_FUNCTION(max)
        argsCountLtEq(1, values.size());
        std::shared_ptr<Value> ans = values[0];
        for(int i = 1; i < values.size(); ++i) ans = comparator(ans, values[i]) ? values[i] : ans;
        return ans;
    FE

    CREATE_FUNCTION(min)
        argsCountLtEq(1, values.size());
        std::shared_ptr<Value> ans = values[0];
        for(int i = 1; i < values.size(); ++i) ans = comparator(ans, values[i]) ? ans : values[i];
        return ans;
    FE

    CREATE_FUNCTION(set_color)
        int color = 0;
        argsCount(0, 1, values.size());
        if (values.size() == 1){
            argType(Values::NUMBER, values[0]);
            color = values[0] -> asDouble();
        }
        SetConsoleTextAttribute(global_out::handle, color);
        return NullValue::NULL_;
    FE
}

void Global::initConstants(){
    Variables::set("true", BoolValue::TRUE_);
    Variables::set("false", BoolValue::FALSE_);
    Variables::set("null", NullValue::NULL_);
}

void Global::initFunctions(){
    INF_F(input)
    INF1_F(max)
    INF1_F(min)
    INFO_F(set_color, ArgumentsInfo(0, 1))
}
