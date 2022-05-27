#ifndef IMPORTADDER_H_INCLUDED
#define IMPORTADDER_H_INCLUDED

#include "visitor.h"

namespace SlavaScript::lang{
    class ImportAdder : public Visitor{
    public:
        void visit(ImportStatement* v);
    };
}

#endif // IMPORTADDER_H_INCLUDED
