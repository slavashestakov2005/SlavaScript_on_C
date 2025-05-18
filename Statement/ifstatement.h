#pragma once

#include <Expression/expression.h>
#include <Statement/statement.h>


namespace SlavaScript::lang {
    class IfStatement : public Statement {
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
