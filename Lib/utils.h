#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "function.h"

namespace SlavaScript::lang{
    CMP(int);
    CMP(std::string);

    template<typename T>
    std::shared_ptr<Function> get_property(std::shared_ptr<Value> value, T operation);
}

#include "utils_impl.h"

#endif // UTILS_H_INCLUDED
