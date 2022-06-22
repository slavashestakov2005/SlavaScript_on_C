#ifndef VARIABLEPRINTER_H_INCLUDED
#define VARIABLEPRINTER_H_INCLUDED

#include "visitor.h"

namespace SlavaScript::lang{
    class VariablePrinter : public Visitor{
    public:
        void visit(AssignmentExpression* v) override;
        void visit(VariableExpression* v) override;
    };
}

#endif // VARIABLEPRINTER_H_INCLUDED
