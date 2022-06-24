#ifndef BLOCKSTATEMENT_H_INCLUDED
#define BLOCKSTATEMENT_H_INCLUDED

#include "statement.h"
#include <vector>

namespace SlavaScript::lang{
    class BlockStatement : public Statement{
    private:
        std::vector<Statement*> statements;
    public:
        BlockStatement();

        void add(Statement* statement);

        void execute() override;
        Statements type() const override;
        operator std::string() override;

        ~BlockStatement();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}

#endif // BLOCKSTATEMENT_H_INCLUDED
