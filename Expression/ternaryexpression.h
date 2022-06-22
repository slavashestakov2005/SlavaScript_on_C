#ifndef TERNARYEXPRESSION_H_INCLUDED
#define TERNARYEXPRESSION_H_INCLUDED

#include "expression.h"

namespace SlavaScript::lang{
    class TernaryExpression : public Expression{
    private:
        Expression* condition, *trueExpr, *falseExpr;
    public:
        TernaryExpression(Expression* condition, Expression* trueExpr, Expression* falseExpr);

        std::shared_ptr<Value> eval() override;
        Expressions type() const override;
        operator std::string() override;

        ~TernaryExpression();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}

#endif // TERNARYEXPRESSION_H_INCLUDED
