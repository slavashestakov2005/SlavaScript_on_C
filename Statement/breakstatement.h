#ifndef BREAKSTATEMENT_H_INCLUDED
#define BREAKSTATEMENT_H_INCLUDED

#include "statement.h"

namespace SlavaScript{ namespace lang{
    class BreakStatement : public Statement{
    public:
        Statements type(){ return Statements::BreakStatement; }
        /** @return  throw: BreakStatement*. */
        void execute();
        operator std::string();
        void accept(Visitor* visitor);
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}}

#endif // BREAKSTATEMENT_H_INCLUDED
