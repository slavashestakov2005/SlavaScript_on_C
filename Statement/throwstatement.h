#ifndef THROWSTATEMENT_H_INCLUDED
#define THROWSTATEMENT_H_INCLUDED

#include "statement.h"
#include "../Expression/expression.h"
#include "../Value/value.h"

namespace SlavaScript::lang{
    class ThrowStatement : public Statement{
    private:
        Expression* expression;
        std::shared_ptr<Value> result;
    public:
        ThrowStatement(Expression* expression);

        std::shared_ptr<Value> getResult();

        /** @return  throw: ThrowStatement*. */
        void execute() override;
        Statements type() const override;
        operator std::string() override;

        ~ThrowStatement();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}

#endif // THROWSTATEMENT_H_INCLUDED
