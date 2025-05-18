#pragma once

#include <vector>

#include <Expression/expression.h>
#include <Expression/suffixelement.h>
#include <Visitor/assignvalidator.h>


namespace SlavaScript::lang {
    class SuffixExpression : public Expression {
    private:
        Expression* root;
        std::vector<SuffixElement*> access;
        std::shared_ptr<Value> container, lastContainer;
    public:
        SuffixExpression(Expression* root, std::vector<SuffixElement*> access);

        std::shared_ptr<Value> get();
        std::shared_ptr<Value> set(std::shared_ptr<Value> value);

        std::shared_ptr<Value> eval() override;
        Expressions type() const override;
        operator std::string() override;

        ~SuffixExpression();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend AssignValidator;
        friend compiler::CompilerVisitor;
    };
}
