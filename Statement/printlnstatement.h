#ifndef PRINTLNSTATEMENT_H_INCLUDED
#define PRINTLNSTATEMENT_H_INCLUDED

#include "statement.h"
#include "../Expression/expression.h"

namespace SlavaScript::lang{
    class PrintlnStatement : public Statement{
    private:
        Expression* expression;
    public:
        PrintlnStatement(Expression* expression);

        void execute() override;
        Statements type() const override;
        operator std::string() override;

        ~PrintlnStatement();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}

#endif // PRINTLNSTATEMENT_H_INCLUDED
