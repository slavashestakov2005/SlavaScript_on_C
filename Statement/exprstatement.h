#pragma once

#include <Expression/expression.h>
#include <Statement/statement.h>


namespace SlavaScript::lang {
    class ExprStatement : public Statement {
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
