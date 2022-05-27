#ifndef CONTAINER_H_INCLUDED
#define CONTAINER_H_INCLUDED

#include <memory>
#include "value.h"
#include "../Lib/macros.h"

namespace SlavaScript::lang{
    template<typename T>
    class Container{
    public:
        virtual int size() const = 0;
        virtual std::shared_ptr<Value> accessDot(std::shared_ptr<Value> property) = 0;
        virtual std::shared_ptr<Value> accessBracket(std::shared_ptr<Value> property) = 0;
        virtual typename T::iterator begin() = 0;
        virtual typename T::iterator end() = 0;
    };
}

#endif // CONTAINER_H_INCLUDED
