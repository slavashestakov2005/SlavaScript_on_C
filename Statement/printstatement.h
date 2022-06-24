#ifndef PRINTSTATEMENT_H_INCLUDED
#define PRINTSTATEMENT_H_INCLUDED

#include "../Expression/expression.h"
#include "statement.h"

namespace SlavaScript::lang{
    class PrintStatement : public Statement{
    private:
        Expression* expression;
    public:
        PrintStatement(Expression* expression);

        void execute() override;
        Statements type() const override;
        operator std::string() override;

        ~PrintStatement();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}

#endif // PRINTSTATEMENT_H_INCLUDED
