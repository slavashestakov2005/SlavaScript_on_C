#pragma once

#include <vector>

#include <Statement/statement.h>


namespace SlavaScript::lang {
    class BlockStatement : public Statement {
    private:
        std::vector<Statement*> statements;
    public:
        BlockStatement();

        void add(Statement* statement);

        void execute() override;
        Statements type() const override;
        operator std::string() override;

        ~BlockStatement();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}
