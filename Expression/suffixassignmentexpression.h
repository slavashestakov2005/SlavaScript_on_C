#pragma once

#include <Expression/assignmentoperator.h>
#include <Expression/expression.h>
#include <Expression/suffixexpression.h>
#include <Visitor/assignvalidator.h>


namespace SlavaScript::lang {
    class SuffixAssignmentExpression : public Expression {
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
