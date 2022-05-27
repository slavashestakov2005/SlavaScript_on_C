#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include "visitor.h"

namespace SlavaScript::lang{
    class Node{
    public:
        virtual void accept(Visitor* visitor) = 0;
    };
}

#endif // NODE_H_INCLUDED
