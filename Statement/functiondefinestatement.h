#ifndef FUNCTIONDEFINESTATEMENT_H_INCLUDED
#define FUNCTIONDEFINESTATEMENT_H_INCLUDED

#include "../Lib/arguments.h"
#include "statement.h"
#include "../Visitor/functionadder.h"
#include <vector>

namespace SlavaScript::lang{
    class FunctionDefineStatement : public Statement{
    public:
        Arguments arguments;
        Statement* body;
        std::string name;

        FunctionDefineStatement(std::string name, Arguments arguments, Statement* body);

        void execute(bool set);
        std::string getName();

        void execute() override;
        Statements type() const override;
        operator std::string() override;

        ~FunctionDefineStatement();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend FunctionAdder;
        friend compiler::CompilerVisitor;
    };
}

#endif // FUNCTIONDEFINESTATEMENT_H_INCLUDED
