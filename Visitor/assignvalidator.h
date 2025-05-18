#pragma once

#include <Visitor/visitor.h>


namespace SlavaScript::lang {
    class AssignValidator : public Visitor {
    public:
        /** @return  throw: std::logic_error. */
        void visit(AssignmentExpression* v) override;
        /** @return  throw: std::logic_error. */
        void visit(SuffixAssignmentExpression* v) override;
    };
}
