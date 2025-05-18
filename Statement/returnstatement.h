#pragma once

#include <Expression/expression.h>
#include <Statement/statement.h>
#include <Value/value.h>


namespace SlavaScript::lang {
    class ReturnStatement : public Statement {
    private:
        Expression* expression;
        std::shared_ptr<Value> result;
    public:
        ReturnStatement(Expression* expression);

        std::shared_ptr<Value> getResult();

        /** @return  throw: ReturnStatement*. */
        void execute() override;
        Statements type() const override;
        operator std::string() override;

        ~ReturnStatement();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}
