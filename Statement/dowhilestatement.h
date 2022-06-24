#ifndef DOWHILESTATEMENT_H_INCLUDED
#define DOWHILESTATEMENT_H_INCLUDED

#include "../Expression/expression.h"
#include "statement.h"

namespace SlavaScript::lang{
    class DoWhileStatement : public Statement{
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

#endif // DOWHILESTATEMENT_H_INCLUDED
