#ifndef BLOCKSTATEMENT_H_INCLUDED
#define BLOCKSTATEMENT_H_INCLUDED

#include <vector>
#include "statement.h"

namespace SlavaScript{ namespace lang{
    class BlockStatement : public Statement{
    private:
        std::vector<Statement*> statements;
    public:
        BlockStatement(){}
        Statements type(){ return Statements::BlockStatement; }
        void add(Statement* statement);
        void execute();
        operator std::string();
        ~BlockStatement();
        void accept(Visitor* visitor);
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}}

#endif // BLOCKSTATEMENT_H_INCLUDED
