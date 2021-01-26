#ifndef FOREACHARRAYSTATEMENT_H_INCLUDED
#define FOREACHARRAYSTATEMENT_H_INCLUDED

#include "statement.h"
#include "../Expression/expression.h"

namespace SlavaScript{ namespace lang{
    class ForeachArrayStatement : public Statement{
    private:
        std::string variable;
        Expression* container;
        Statement* body;
    public:
        ForeachArrayStatement(std::string variable, Expression* container, Statement* body) : variable(variable), container(container), body(body) {}
        Statements type(){ return Statements::ForeachArrayStatement; }
        void execute();
        operator std::string();
        ~ForeachArrayStatement();
        void accept(Visitor* visitor);
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}}

#endif // FOREACHARRAYSTATEMENT_H_INCLUDED
