#ifndef FORSTATEMENT_H_INCLUDED
#define FORSTATEMENT_H_INCLUDED

#include "../Expression/expression.h"
#include "statement.h"

namespace SlavaScript::lang{
    class ForStatement: public Statement{
    private:
        Statement* initialization;
        Expression* termination;
        Statement* increment;
        Statement* body;
    public:
        ForStatement(Statement* initialization, Expression* termination, Statement* increment, Statement* body);

        void execute() override;
        Statements type() const override;
        operator std::string() override;

        ~ForStatement();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}

#endif // FORSTATEMENT_H_INCLUDED
