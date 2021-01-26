#ifndef TRYSTATEMENT_H_INCLUDED
#define TRYSTATEMENT_H_INCLUDED

#include "statement.h"
#include "../Expression/expression.h"

namespace SlavaScript{ namespace lang{
    class TryStatement : public Statement{
    private:
        Statement* body, *catchBlock;
        std::string name;
    public:
        TryStatement(Statement* body, std::string name, Statement* catchBlock)
        : body(body), name(name), catchBlock(catchBlock) {}
        Statements type(){ return Statements::TryStatement; }
        void execute();
        operator std::string();
        ~TryStatement();
        void accept(Visitor* visitor);
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}}

#endif // TRYSTATEMENT_H_INCLUDED
