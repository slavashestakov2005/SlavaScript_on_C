#pragma once

#include <Expression/expression.h>
#include <Statement/statement.h>


namespace SlavaScript::lang {
    class PrintlnStatement : public Statement {
    private:
        Expression* expression;
    public:
        PrintlnStatement(Expression* expression);

        void execute() override;
        Statements type() const override;
        operator std::string() override;

        ~PrintlnStatement();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}
