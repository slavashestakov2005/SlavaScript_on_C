#ifndef VARIABLEPRINTER_H_INCLUDED
#define VARIABLEPRINTER_H_INCLUDED

#include "visitor.h"

namespace SlavaScript::lang{
    class VariablePrinter : public Visitor{
    public:
        void visit(AssignmentExpression* v);
        void visit(VariableExpression* v);
    };
}

#endif // VARIABLEPRINTER_H_INCLUDED
