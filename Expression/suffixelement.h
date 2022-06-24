#ifndef SUFFIXELEMENT_H_INCLUDED
#define SUFFIXELEMENT_H_INCLUDED

#include "expression.h"
#include "../Visitor/assignvalidator.h"

namespace SlavaScript::lang{
    enum class SuffixType{
        BRACKET,
        DOT,
        PAREN,
    };

    class SuffixElement : public Node{
    public:
        virtual std::shared_ptr<Value> get(std::shared_ptr<Value> container) = 0;
        virtual std::shared_ptr<Value> set(std::shared_ptr<Value> container, std::shared_ptr<Value> value) = 0;
        virtual SuffixType type() const = 0;
        virtual operator std::string() = 0;

        virtual ~SuffixElement();
    };

    class BracketSuffixElement : public SuffixElement{
    private:
        Expression* expression;
    public:
        BracketSuffixElement(Expression* expression);

        std::shared_ptr<Value> get(std::shared_ptr<Value> container) override;
        std::shared_ptr<Value> set(std::shared_ptr<Value> container, std::shared_ptr<Value> value) override;
        SuffixType type() const override;
        operator std::string() override;

        ~BracketSuffixElement();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend AssignValidator;
        friend compiler::CompilerVisitor;
    };

    class DotSuffixElement : public SuffixElement{
    private:
        Expression* expression;
    public:
        DotSuffixElement(Expression* expression);

        std::shared_ptr<Value> get(std::shared_ptr<Value> container) override;
        std::shared_ptr<Value> set(std::shared_ptr<Value> container, std::shared_ptr<Value> value) override;
        SuffixType type() const override;
        operator std::string() override;

        ~DotSuffixElement();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend AssignValidator;
        friend compiler::CompilerVisitor;
    };

    class ParenSuffixElement : public SuffixElement{
    private:
        std::vector<Expression*> arguments;
    public:
        ParenSuffixElement(std::vector<Expression*> arguments);

        std::shared_ptr<Value> get(std::shared_ptr<Value> container) override;
        std::shared_ptr<Value> set(std::shared_ptr<Value> container, std::shared_ptr<Value> value) override;
        SuffixType type() const override;
        operator std::string() override;

        ~ParenSuffixElement();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend AssignValidator;
        friend compiler::CompilerVisitor;
    };
}

#endif // SUFFIXELEMENT_H_INCLUDED
