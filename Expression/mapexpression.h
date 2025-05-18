#pragma once

#include <map>

#include <Expression/expression.h>


namespace SlavaScript::lang {
    class MapExpression : public Expression {
    private:
        std::map<Expression*, Expression*> elements;
    public:
        MapExpression(std::map<Expression*, Expression*> elements);

        std::shared_ptr<Value> eval() override;
        Expressions type() const override;
        operator std::string() override;

        ~MapExpression();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}
