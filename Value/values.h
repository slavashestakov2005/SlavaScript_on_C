#ifndef VALUES_H_INCLUDED
#define VALUES_H_INCLUDED

#include <string>
#include "../Lib/macros.h"

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

    CMP(int);
    CMP(std::string);
    CMP(Values);
}

#endif // VALUES_H_INCLUDED
