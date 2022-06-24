#ifndef SUFFIXaSSIGNMENTSTATEMENT_H_INCLUDED
#define SUFFIXASSIGNMENTSTATEMENT_H_INCLUDED

#include "assignmentoperator.h"
#include "expression.h"
#include "suffixexpression.h"
#include "../Visitor/assignvalidator.h"

namespace SlavaScript::lang{
    class SuffixAssignmentExpression : public Expression{
    private:
        AssignmentOperator operation;
        SuffixExpression* containerExpr;
        Expression* expression;
    public:
        SuffixAssignmentExpression(AssignmentOperator operation, SuffixExpression* containerExpr, Expression* expression);

        std::shared_ptr<Value> eval() override;
        Expressions type() const override;
        operator std::string() override;

        ~SuffixAssignmentExpression();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend AssignValidator;
        friend compiler::CompilerVisitor;
    };
}

#endif // SUFFIXASSIGNMENTSTATEMENT_H_INCLUDED
