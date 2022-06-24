#ifndef SWITCHSTATEMENT_H_INCLUDED
#define SWITCHSTATEMENT_H_INCLUDED

#include "../Expression/expression.h"
#include "statement.h"
#include <vector>

namespace SlavaScript::lang{
    class SwitchStatement : public Statement{
    private:
        Expression* start;
        std::vector<std::pair<Expression*, Statement*>> body;
        Statement* defaultCase;
    public:
        SwitchStatement(Expression* start, std::vector<std::pair<Expression*, Statement*>> body, Statement* defaultCase);

        void execute() override;
        Statements type() const override;
        operator std::string() override;

        ~SwitchStatement();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend compiler::CompilerVisitor;
    };
}

#endif // SWITCHSTATEMENT_H_INCLUDED
