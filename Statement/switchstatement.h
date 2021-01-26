#ifndef SWITCHSTATEMENT_H_INCLUDED
#define SWITCHSTATEMENT_H_INCLUDED

#include <vector>
#include "statement.h"
#include "../Expression/expression.h"

namespace SlavaScript{ namespace lang{
    class SwitchStatement : public Statement{
    private:
        Expression* start;
        std::vector<std::pair<Expression*, Statement*>> body;
        Statement* defaultCase;
    public:
        SwitchStatement(Expression* start, std::vector<std::pair<Expression*, Statement*>> body, Statement* defaultCase)
        : start(start), body(body), defaultCase(defaultCase) {}
        Statements type(){ return Statements::SwitchStatement; }
        void execute();
        operator std::string();
        ~SwitchStatement();
        void accept(Visitor* visitor);
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}}

#endif // SWITCHSTATEMENT_H_INCLUDED
