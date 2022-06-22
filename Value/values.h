#ifndef VALUES_H_INCLUDED
#define VALUES_H_INCLUDED

#include "../Lib/macros.h"
#include <string>

namespace SlavaScript::lang{
    enum class Values{
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

    CMP(Values);
}

#endif // VALUES_H_INCLUDED
