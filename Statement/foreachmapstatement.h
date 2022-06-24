#ifndef FOREACHMAPSTATEMENT_H_INCLUDED
#define FOREACHMAPSTATEMENT_H_INCLUDED

#include "../Expression/expression.h"
#include "statement.h"

namespace SlavaScript::lang{
    class ForeachMapStatement : public Statement{
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

#endif // FOREACHMAPSTATEMENT_H_INCLUDED
