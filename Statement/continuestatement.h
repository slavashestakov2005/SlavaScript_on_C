#ifndef CONTINUESTATEMENT_H_INCLUDED
#define CONTINUESTATEMENT_H_INCLUDED

#include "statement.h"

namespace SlavaScript{ namespace lang{
    class ContinueStatement : public Statement{
    public:
        Statements type(){ return Statements::ContinueStatement; }
        /** @return  throw: ContinueStatement*. */
        void execute();
        operator std::string();
        void accept(Visitor* visitor);
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}}

#endif // CONTINUESTATEMENT_H_INCLUDED
