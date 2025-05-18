#pragma once

#include <Visitor/visitor.h>


namespace SlavaScript::lang {
    class VariablePrinter : public Visitor {
    public:
        void visit(AssignmentExpression* v) override;
        void visit(VariableExpression* v) override;
    };
}
