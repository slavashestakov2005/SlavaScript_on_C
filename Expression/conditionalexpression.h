#pragma once

#include <Expression/conditionaloperator.h>
#include <Expression/expression.h>


namespace SlavaScript::lang {
    class ConditionalExpression : public Expression {
    private:
        Expression* expr1, *expr2;
        ConditionalOperator operation;
    public:
        /** @return  throw: OperationIsNotSupportedException*. */
        static std::shared_ptr<Value> calculate(ConditionalOperator operation, std::shared_ptr<Value> left, std::shared_ptr<Value> right);

        ConditionalExpression(ConditionalOperator operation, Expression* expr1, Expression* expr2);

        std::shared_ptr<Value> eval() override;
        Expressions type() const override;
        operator std::string() override;

        ~ConditionalExpression();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}
