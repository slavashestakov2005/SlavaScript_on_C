#ifndef FORSTATEMENT_H_INCLUDED
#define FORSTATEMENT_H_INCLUDED

#include "statement.h"
#include "../Expression/expression.h"

namespace SlavaScript{ namespace lang{
    class ForStatement: public Statement{
    private:
        Statement* initialization;
        Expression* termination;
        Statement* increment;
        Statement* body;
    public:
        ForStatement(Statement* initialization, Expression* termination, Statement* increment, Statement* statement)
        : initialization(initialization), termination(termination), increment(increment), body(body) {}
        Statements type(){ return Statements::ForStatement; }
        void execute();
        operator std::string();
        ~ForStatement();
        void accept(Visitor* visitor);
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}}

#endif // FORSTATEMENT_H_INCLUDED
