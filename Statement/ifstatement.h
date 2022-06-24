#ifndef IFSTATEMENT_H_INCLUDED
#define IFSTATEMENT_H_INCLUDED

#include "../Expression/expression.h"
#include "statement.h"

namespace SlavaScript::lang{
    class IfStatement : public Statement{
    private:
        Expression* expression;
        Statement* ifStatement, *elseStatement;
    public:
        IfStatement(Expression* expression, Statement* ifStatement, Statement* elseStatement);

        void execute() override;
        Statements type() const override;
        operator std::string() override;

        ~IfStatement();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}

#endif // IFSTATEMENT_H_INCLUDED
