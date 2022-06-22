#ifndef CONTINUESTATEMENT_H_INCLUDED
#define CONTINUESTATEMENT_H_INCLUDED

#include "statement.h"

namespace SlavaScript::lang{
    class ContinueStatement : public Statement{
    public:
        /** @return  throw: ContinueStatement*. */
        void execute() override;
        Statements type() const override;
        operator std::string() override;

        void accept(Visitor* visitor) override;
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}

#endif // CONTINUESTATEMENT_H_INCLUDED
