#pragma once

#include <Expression/expression.h>
#include <Statement/statement.h>


namespace SlavaScript::lang {
    class ForeachArrayStatement : public Statement {
    private:
        std::string variable;
        Expression* container;
        Statement* body;
    public:
        ForeachArrayStatement(std::string variable, Expression* container, Statement* body);

        void execute() override;
        Statements type() const override;
        operator std::string() override;

        ~ForeachArrayStatement();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}
