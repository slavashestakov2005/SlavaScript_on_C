#ifndef SUFFIXEXPRESSION_H_INCLUDED
#define SUFFIXEXPRESSION_H_INCLUDED

#include <vector>
#include "suffixelement.h"
#include "expression.h"
#include "../Value/arrayvalue.h"
#include "../Value/mapvalue.h"
#include "../Visitor/assignvalidator.h"

namespace SlavaScript::lang{
    class SuffixExpression : public Expression{
    private:
        Expression* root;
        std::vector<SuffixElement*> access;
        std::shared_ptr<Value> container, lastContainer;
    public:
        SuffixExpression(std::string variable, std::vector<SuffixElement*> access);
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

#endif // SUFFIXEXPRESSION_H_INCLUDED
