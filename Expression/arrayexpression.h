#ifndef ARRAYEXPRESSION_H_INCLUDED
#define ARRAYEXPRESSION_H_INCLUDED

#include "expression.h"
#include <vector>

namespace SlavaScript::lang{
    class ArrayExpression : public Expression{
    private:
        std::vector<Expression*> elements;
    public:
        ArrayExpression(std::vector<Expression*> elements);

        std::shared_ptr<Value> eval() override;
        Expressions type() const override;
        operator std::string() override;

        ~ArrayExpression();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}

#endif // ARRAYEXPRESSION_H_INCLUDED
