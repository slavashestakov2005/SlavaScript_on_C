#pragma once

#include <vector>

#include <Expression/expression.h>
#include <Statement/statement.h>


namespace SlavaScript::lang {
    class SwitchStatement : public Statement {
    private:
        Expression* start;
        std::vector<std::pair<Expression*, Statement*>> body;
        Statement* defaultCase;
    public:
        SwitchStatement(Expression* start, std::vector<std::pair<Expression*, Statement*>> body, Statement* defaultCase);

        void execute() override;
        Statements type() const override;
        operator std::string() override;

        ~SwitchStatement();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}
