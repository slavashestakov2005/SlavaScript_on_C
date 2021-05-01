#ifndef STATEMENT_H_INCLUDED
#define STATEMENT_H_INCLUDED

#include <string>
#include "../Visitor/node.h"
#include "../Compiler/compilervisitor.h"

namespace SlavaScript{ namespace lang{
    enum class Statements{
        BlockStatement,
        BreakStatement,
        ClassDeclarationsStatement,
        ContinueStatement,
        DoWhileStatement,
        ExprStatement,
        ForeachArrayStatement,
        ForeachMapStatement,
        ForStatement,
        FunctionDefineStatement,
        FunctionStatement,
        IfStatement,
        IntegrationStatement,
        ImportStatement,
        PrintStatement,
        PrintlnStatement,
        ReturnStatement,
        SwitchStatement,
        ThrowStatement,
        TryStatement,
        WhileStatement
    };

    class Statement : public Node{
    public:
        virtual void execute() = 0;
        virtual operator std::string() = 0;
        virtual ~Statement(){}
        virtual Statements type() = 0;
    };
}}

#endif // STATEMENT_H_INCLUDED
