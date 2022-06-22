#ifndef BINARYEXPRESSION_H_INCLUDED
#define BINARYEXPRESSION_H_INCLUDED

#include "binaryoperator.h"
#include "expression.h"

namespace SlavaScript::lang{
    class BinaryExpression : public Expression{
    private:
        Expression* expr1, *expr2;
        BinaryOperator operation;
    public:
        /** @return  throw: TypeException*, OperationIsNotSupportedException*. */
        static std::shared_ptr<Value> calculate(BinaryOperator operation, std::shared_ptr<Value> left, std::shared_ptr<Value> right);

        BinaryExpression(BinaryOperator operation);
        BinaryExpression(BinaryOperator operation, Expression* expr1, Expression* expr2);

        std::shared_ptr<Value> eval() override;
        Expressions type() const override;
        operator std::string() override;

        ~BinaryExpression();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}

#endif // BINARYEXPRESSION_H_INCLUDED
