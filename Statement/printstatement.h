#ifndef PRINTSTATEMENT_H_INCLUDED
#define PRINTSTATEMENT_H_INCLUDED

#include "statement.h"
#include "../Expression/expression.h"

namespace SlavaScript::lang{
    class PrintStatement : public Statement{
    private:
        Expression* expression;
    public:
        PrintStatement(Expression* expression) : expression(expression) {}
        Statements type(){ return Statements::PrintStatement; }
        void execute();
        operator std::string();
        ~PrintStatement();
        void accept(Visitor* visitor);
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}

#endif // PRINTSTATEMENT_H_INCLUDED
