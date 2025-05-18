#pragma once

#include <string>

#include <Lib/macros.h>


namespace SlavaScript::lang {
    enum class Values {
        BOOL,
        NUMBER,
        STRING,
        ARRAY,
        MAP,
        NULL_,
        FUNCTION,
        OBJECT,
        CLASS,
        INTEGRATION,
    };

    std::string getValueName(Values value);
}
