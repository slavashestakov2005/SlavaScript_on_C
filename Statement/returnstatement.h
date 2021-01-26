#ifndef RETURNSTATEMENT_H_INCLUDED
#define RETURNSTATEMENT_H_INCLUDED

#include "statement.h"
#include "../Expression/expression.h"
#include "../Value/value.h"

namespace SlavaScript{ namespace lang{
    class ReturnStatement : public Statement{
    private:
        Expression* expression;
        Value* result;
    public:
        ReturnStatement(Expression* expression) : expression(expression) {}
        Statements type(){ return Statements::ReturnStatement; }
        Value* getResult();
        /** @return  throw: ReturnStatement*. */
        void execute();
        operator std::string();
        ~ReturnStatement();
        void accept(Visitor* visitor);
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}}

#endif // RETURNSTATEMENT_H_INCLUDED
