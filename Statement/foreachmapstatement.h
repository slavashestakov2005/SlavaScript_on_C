#pragma once

#include <Expression/expression.h>
#include <Statement/statement.h>


namespace SlavaScript::lang {
    class ForeachMapStatement : public Statement {
    private:
        std::string key, value;
        Expression* container;
        Statement* body;
    public:
        ForeachMapStatement(std::string key, std::string value, Expression* container, Statement* body);

        void execute() override;
        Statements type() const override;
        operator std::string() override;

        ~ForeachMapStatement();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}
