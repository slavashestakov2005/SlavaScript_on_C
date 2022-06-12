#include "values.h"

using namespace SlavaScript::lang;

namespace {
    std::string mas[] = {
        "Bool", "Number", "String", "Array", "Map", "Null", "Function", "Object", "Class", "Integration"
    };
}

std::string SlavaScript::lang::getValueName(Values value){
    return mas[(int) value];
}
