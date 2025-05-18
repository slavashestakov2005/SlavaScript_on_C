#pragma once

#include <Expression/expression.h>
#include <Statement/statement.h>


namespace SlavaScript::lang {
    class DoWhileStatement : public Statement {
    private:
        Expression* condition;
        Statement* body;
    public:
        DoWhileStatement(Expression* condition, Statement* body);

        void execute() override;
        Statements type() const override;
        operator std::string() override;

        ~DoWhileStatement();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}
