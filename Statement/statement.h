#pragma once

#include <string>

#include <Compiler/compilervisitor.h>
#include <Visitor/node.h>


namespace SlavaScript::lang {
    enum class Statements {
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

    class Statement : public Node {
    public:
        virtual void execute() = 0;
        virtual Statements type() const = 0;
        virtual operator std::string() = 0;

        virtual ~Statement() {}
    };
}
