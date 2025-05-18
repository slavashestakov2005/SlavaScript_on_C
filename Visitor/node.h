#pragma once

#include <Visitor/visitor.h>


namespace SlavaScript::lang {
    class Node {
    public:
        virtual void accept(Visitor* visitor) = 0;
    };
}
