#ifndef EXPRSTATEMENT_H_INCLUDED
#define EXPRSTATEMENT_H_INCLUDED

#include "../Expression/expression.h"
#include "statement.h"

namespace SlavaScript::lang{
    class ExprStatement : public Statement{
        Expression* expression;
    public:
        ExprStatement(Expression* expression);

        void execute() override;
        Statements type() const override;
        operator std::string() override;

        ~ExprStatement();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}

#endif // EXPRSTATEMENT_H_INCLUDED
