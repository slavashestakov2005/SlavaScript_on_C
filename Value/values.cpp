#include "values.h"
#include "../Lib/utils.h"

using namespace SlavaScript::lang;

namespace {
    std::string mas[] = {
        "Bool", "Number", "String", "Array", "Map", "Null", "Function", "Object", "Class", "Integration"
    };
}

namespace SlavaScript::lang{
    std::string getValueName(Values value){
        return mas[(int) value];
    }

    CMP(Values){
        RCHECK(int(a), int(b));
    }
}
