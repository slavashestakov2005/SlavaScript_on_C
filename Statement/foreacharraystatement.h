#ifndef FOREACHARRAYSTATEMENT_H_INCLUDED
#define FOREACHARRAYSTATEMENT_H_INCLUDED

#include "statement.h"
#include "../Expression/expression.h"

namespace SlavaScript::lang{
    class ForeachArrayStatement : public Statement{
    private:
        std::string variable;
        Expression* container;
        Statement* body;
    public:
        ForeachArrayStatement(std::string variable, Expression* container, Statement* body);

        void execute() override;
        Statements type() const override;
        operator std::string() override;

        ~ForeachArrayStatement();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}

#endif // FOREACHARRAYSTATEMENT_H_INCLUDED
