#ifndef ASSIGNVALIDATOR_H_INCLUDED
#define ASSIGNVALIDATOR_H_INCLUDED

#include "visitor.h"

namespace SlavaScript::lang{
    class AssignValidator : public Visitor{
    public:
        /** @return  throw: std::logic_error. */
        void visit(AssignmentExpression* v) override;
        /** @return  throw: std::logic_error. */
        void visit(SuffixAssignmentExpression* v) override;
    };
}

#endif // ASSIGNVALIDATOR_H_INCLUDED
