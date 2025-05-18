#pragma once

#include <Statement/statement.h>


namespace SlavaScript::lang {
    class ContinueStatement : public Statement {
    public:
        /** @return  throw: ContinueStatement*. */
        void execute() override;
        Statements type() const override;
        operator std::string() override;

        void accept(Visitor* visitor) override;
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}
