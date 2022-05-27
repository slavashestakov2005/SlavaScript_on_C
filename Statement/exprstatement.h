#ifndef EXPRSTATEMENT_H_INCLUDED
#define EXPRSTATEMENT_H_INCLUDED

#include "statement.h"
#include "../Expression/expression.h"

namespace SlavaScript::lang{
    class ExprStatement : public Statement{
        Expression* expression;
    public:
        ExprStatement(Expression* expression) : expression(expression) {}
        Statements type(){ return Statements::ExprStatement; }
        void execute();
        operator std::string();
        ~ExprStatement();
        void accept(Visitor* visitor);
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}

#endif // EXPRSTATEMENT_H_INCLUDED
