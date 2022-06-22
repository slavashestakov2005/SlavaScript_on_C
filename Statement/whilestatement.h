#ifndef WHILESTATEMENT_H_INCLUDED
#define WHILESTATEMENT_H_INCLUDED

#include "statement.h"
#include "../Expression/expression.h"

namespace SlavaScript::lang{
    class WhileStatement : public Statement{
    private:
        Expression* condition;
        Statement* body;
    public:
        WhileStatement(Expression* condition, Statement* body);

        void execute() override;
        Statements type() const override;
        operator std::string() override;

        ~WhileStatement();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}

#endif // WHILESTATEMENT_H_INCLUDED
