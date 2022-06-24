#ifndef TRYSTATEMENT_H_INCLUDED
#define TRYSTATEMENT_H_INCLUDED

#include "../Expression/expression.h"
#include "statement.h"

namespace SlavaScript::lang{
    class TryStatement : public Statement{
    private:
        Statement* body, *catchBlock;
        std::string name;
    public:
        TryStatement(Statement* body, std::string name, Statement* catchBlock);

        void execute() override;
        Statements type() const override;
        operator std::string() override;

        ~TryStatement();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}

#endif // TRYSTATEMENT_H_INCLUDED
