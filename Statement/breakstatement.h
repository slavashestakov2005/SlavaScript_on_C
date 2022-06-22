#ifndef BREAKSTATEMENT_H_INCLUDED
#define BREAKSTATEMENT_H_INCLUDED

#include "statement.h"

namespace SlavaScript::lang{
    class BreakStatement : public Statement{
    public:
        /** @return  throw: BreakStatement*. */
        void execute() override;
        Statements type() const override;
        operator std::string() override;

        void accept(Visitor* visitor) override;
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}

#endif // BREAKSTATEMENT_H_INCLUDED
