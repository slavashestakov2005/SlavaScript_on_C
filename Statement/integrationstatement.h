#pragma once

#include <Statement/statement.h>


namespace SlavaScript::lang {
    class IntegrationStatement : public Statement {
    private:
        std::string lang, name, code;
    public:
        IntegrationStatement(std::string lang, std::string name, std::string code);

        void execute() override;
        Statements type() const override;
        operator std::string() override;

        void accept(Visitor* visitor) override;
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}
