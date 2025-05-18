#include <Lib/utils.h>
#include <Value/values.h>


using namespace SlavaScript::lang;

namespace {
    std::string mas[] = {
        "Bool", "Number", "String", "Array", "Map", "Null", "Function", "Object", "Class", "Integration"
    };
}

namespace SlavaScript::lang {
    std::string getValueName(Values value) {
        return mas[(int) value];
    }
}
