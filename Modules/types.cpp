#include "types.h"
#include "../Lib/variables.h"
#include "../Lib/functions.h"
#include "../Value/numbervalue.h"
#include "../Value/stringvalue.h"

using namespace SlavaScript::lang;
using namespace SlavaScript::modules::types_f;
using SlavaScript::modules::Types;

namespace SlavaScript{ namespace modules{ namespace types_f{
    Function* float_ = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw std::logic_error("One argument expected");
        return new NumberValue(values[0] -> asBignum());
    });

    Function* int_ = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw std::logic_error("One argument expected");
        std::string str = std::string(NumberValue(values[0] -> asBignum())), cop;
        for(int i = 0; i < str.size(); ++i){
            if (str[i] == '.') break;
            else cop += str[i];
        }
        return new NumberValue(cop);
    });

    Function* string = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw std::logic_error("One argument expected");
        else return new StringValue(values[0] -> asString());
    });

    Function* type_to_string = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw std::logic_error("One argument expected");
        else return new StringValue(getValueName(values[0] -> type()));
    });

    Function* typeof = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 1) throw std::logic_error("One argument expected");
        else return new NumberValue(int(values[0] -> type()));
    });
}}}

void Types::initConstants(){
    Variables::set("BOOL", new NumberValue(int(Values::BOOL)));
    Variables::set("NUMBER", new NumberValue(int(Values::NUMBER)));
    Variables::set("STRING", new NumberValue(int(Values::STRING)));
    Variables::set("ARRAY", new NumberValue(int(Values::ARRAY)));
    Variables::set("MAP", new NumberValue(int(Values::MAP)));
    Variables::set("NULL", new NumberValue(int(Values::NULL_)));
    Variables::set("FUNCTION", new NumberValue(int(Values::FUNCTION)));
    Variables::set("CLASS", new NumberValue(int(Values::CLASS)));
}

void Types::initFunctions(){
    Functions::set("float", float_);
    Functions::set("int", int_);
    Functions::set("string", string);
    Functions::set("type_to_string", type_to_string);
    Functions::set("typeof", typeof);
}
