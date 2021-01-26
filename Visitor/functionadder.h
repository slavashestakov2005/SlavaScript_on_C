#ifndef FUNCTIONADDER_H_INCLUDED
#define FUNCTIONADDER_H_INCLUDED

#include "visitor.h"

namespace SlavaScript{ namespace lang{
    class FunctionDefineStatement;

    class FunctionAdder : public Visitor{
    public:
        /** @return  throw: std::logic_error. */
        void visit(FunctionDefineStatement* v);
    };
}}

#endif // FUNCTIONADDER_H_INCLUDED
