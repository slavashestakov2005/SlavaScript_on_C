#ifndef CONTAINER_H_INCLUDED
#define CONTAINER_H_INCLUDED

#include <memory>
#include "value.h"

namespace SlavaScript{ namespace lang{
    class Container{
    public:
        virtual std::shared_ptr<Value> accessDot(std::shared_ptr<Value> property) = 0;
        virtual std::shared_ptr<Value> accessBracket(std::shared_ptr<Value> property) = 0;
        virtual int size() const = 0;
    };
}}

#endif // CONTAINER_H_INCLUDED
