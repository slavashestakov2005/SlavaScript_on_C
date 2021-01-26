#ifndef CONTAINER_H_INCLUDED
#define CONTAINER_H_INCLUDED

#include "value.h"

namespace SlavaScript{ namespace lang{
    class Container{
    public:
        virtual Value* accessDot(Value* property) = 0;
        virtual Value* accessBracket(Value* property) = 0;
    };
}}

#endif // CONTAINER_H_INCLUDED
