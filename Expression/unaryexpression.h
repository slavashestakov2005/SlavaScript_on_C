#pragma once

#include <Expression/expression.h>
#include <Expression/unaryoperator.h>


namespace SlavaScript::lang {
    class UnaryExpression : public Expression {
    private:
        Expression* expr;
        UnaryOperator operation;
    public:
        /** @return  throw: OperationIsNotSupportedException*. */
        static std::shared_ptr<Value> calculate(UnaryOperator operation, std::shared_ptr<Value> value);

        UnaryExpression(UnaryOperator operation, Expression* expr);

        std::shared_ptr<Value> eval() override;
        Expressions type() const override;
        operator std::string() override;

        ~UnaryExpression();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}
