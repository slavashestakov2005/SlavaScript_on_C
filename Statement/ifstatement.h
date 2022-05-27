#ifndef IFSTATEMENT_H_INCLUDED
#define IFSTATEMENT_H_INCLUDED

#include "statement.h"
#include "../Expression/expression.h"

namespace SlavaScript::lang{
    class IfStatement : public Statement{
    private:
        Expression* expression;
        Statement* ifStatement, *elseStatement;
    public:
        IfStatement(Expression* expression, Statement* ifStatement, Statement* elseStatement)
        : expression(expression), ifStatement(ifStatement), elseStatement(elseStatement) {}
        Statements type(){ return Statements::IfStatement; }
        void execute();
        operator std::string();
        ~IfStatement();
        void accept(Visitor* visitor);
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}

#endif // IFSTATEMENT_H_INCLUDED
