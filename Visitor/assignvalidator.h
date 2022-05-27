#ifndef ASSIGNVALIDATOR_H_INCLUDED
#define ASSIGNVALIDATOR_H_INCLUDED

#include "visitor.h"

namespace SlavaScript::lang{
    class AssignValidator : public Visitor{
    public:
        /** @return  throw: std::logic_error. */
        void visit(AssignmentExpression* v);
        /** @return  throw: std::logic_error. */
        void visit(ContainerAssignmentExpression* v);
    };
}

#endif // ASSIGNVALIDATOR_H_INCLUDED
