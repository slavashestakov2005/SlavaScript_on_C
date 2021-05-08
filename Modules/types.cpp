#include "types.h"
#include "../Lib/variables.h"
#include "../Lib/functions.h"
#include "../Value/numbervalue.h"
#include "../Value/stringvalue.h"

using namespace SlavaScript::lang;
using namespace SlavaScript::modules::types_f;
using SlavaScript::modules::Types;

namespace SlavaScript{ namespace modules{ namespace types_f{
    CREATE_FUNCTION(float_)
        if (values.size() != 1) throw std::logic_error("One argument expected");
        SH_RET(NumberValue, values[0] -> asBignum());
    FE

    CREATE_FUNCTION(int_)
        if (values.size() != 1) throw std::logic_error("One argument expected");
        std::string str = std::string(NumberValue(values[0] -> asBignum())), cop;
        for(int i = 0; i < str.size(); ++i){
            if (str[i] == '.') break;
            else cop += str[i];
        }
        SH_RET(NumberValue, cop);
    FE

    CREATE_FUNCTION(string)
        if (values.size() != 1) throw std::logic_error("One argument expected");
        SH_RET(StringValue, values[0] -> asString());
    FE

    CREATE_FUNCTION(type_to_string)
        if (values.size() != 1) throw std::logic_error("One argument expected");
        SH_RET(StringValue, getValueName(values[0] -> type()));
    FE

    CREATE_FUNCTION(typeof)
        if (values.size() != 1) throw std::logic_error("One argument expected");
        SH_RET(NumberValue, int(values[0] -> type()));
    FE
}}}

void Types::initConstants(){
    Variables::set("BOOL", SHARE(NumberValue, int(Values::BOOL)));
    Variables::set("NUMBER", SHARE(NumberValue, int(Values::NUMBER)));
    Variables::set("STRING", SHARE(NumberValue, int(Values::STRING)));
    Variables::set("ARRAY", SHARE(NumberValue, int(Values::ARRAY)));
    Variables::set("MAP", SHARE(NumberValue, int(Values::MAP)));
    Variables::set("NULL", SHARE(NumberValue, int(Values::NULL_)));
    Variables::set("FUNCTION", SHARE(NumberValue, int(Values::FUNCTION)));
    Variables::set("CLASS", SHARE(NumberValue, int(Values::CLASS)));
}

void Types::initFunctions(){
    Functions::set("float", float_);
    Functions::set("int", int_);
    Functions::set("string", string);
    Functions::set("type_to_string", type_to_string);
    Functions::set("typeof", typeof);
}
