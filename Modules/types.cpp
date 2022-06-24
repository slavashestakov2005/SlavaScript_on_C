#include "types.h"
#include "../Lib/functions.h"
#include "../Lib/utils.h"
#include "../Lib/variables.h"
#include "../Value/boolvalue.h"
#include "../Value/classvalue.h"
#include "../Value/numbervalue.h"
#include "../Value/objectvalue.h"

using namespace SlavaScript::lang;
using namespace SlavaScript::modules::types_f;
using SlavaScript::modules::Types;

namespace SlavaScript::modules::types_f{
    CREATE_FUNCTION(float_)
        argsCount(1, values.size());
        SH_RET(NumberValue, values[0] -> asBignum());
    FE

    CREATE_FUNCTION(int_)
        argsCount(1, values.size());
        std::string str = std::string(NumberValue(values[0] -> asBignum())), cop;
        for(int i = 0; i < str.size(); ++i){
            if (str[i] == '.') break;
            else cop += str[i];
        }
        SH_RET(NumberValue, cop);
    FE

    CREATE_FUNCTION(isinstance)
        argsCount(2, values.size());
        if (values[0] -> type() != Values::OBJECT) return BoolValue::fromBool(false);
        if (values[1] -> type() != Values::CLASS) return BoolValue::fromBool(false);
        return BoolValue::fromBool(CAST(ObjectValue, values[0]) -> getName() == CAST(ClassValue, values[1]) -> getName());
    FE

    CREATE_FUNCTION(string)
        argsCount(1, values.size());
        SH_RET(StringValue, values[0] -> asString());
    FE

    CREATE_FUNCTION(type_to_string)
        argsCount(1, values.size());
        SH_RET(StringValue, values[0] -> stringType());
    FE

    CREATE_FUNCTION(typeof)
        argsCount(1, values.size());
        SH_RET(NumberValue, int(values[0] -> type()));
    FE
}

void Types::initConstants(){
    Variables::set("BOOL", SHARE(NumberValue, int(Values::BOOL)));
    Variables::set("NUMBER", SHARE(NumberValue, int(Values::NUMBER)));
    Variables::set("STRING", SHARE(NumberValue, int(Values::STRING)));
    Variables::set("ARRAY", SHARE(NumberValue, int(Values::ARRAY)));
    Variables::set("MAP", SHARE(NumberValue, int(Values::MAP)));
    Variables::set("NULL", SHARE(NumberValue, int(Values::NULL_)));
    Variables::set("FUNCTION", SHARE(NumberValue, int(Values::FUNCTION)));
    Variables::set("OBJECT", SHARE(NumberValue, int(Values::OBJECT)));
    Variables::set("CLASS", SHARE(NumberValue, int(Values::CLASS)));
    Variables::set("INTEGRATION", SHARE(NumberValue, int(Values::INTEGRATION)));
}

void Types::initFunctions(){
    _INFO_F(float_, "float", ArgumentsInfo::unary)
    _INFO_F(int_, "int", ArgumentsInfo::unary)
    BINARY_F(isinstance)
    UNARY_F(string)
    UNARY_F(type_to_string)
    UNARY_F(typeof)
}
