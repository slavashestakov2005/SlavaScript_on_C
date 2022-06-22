#ifndef VARIABLEEXPRESSION_H_INCLUDED
#define VARIABLEEXPRESSION_H_INCLUDED

#include "expression.h"
#include "../Visitor/variableprinter.h"

namespace SlavaScript::lang{
    class VariableExpression : public Expression{
    public:
        std::string name;
        VariableExpression(std::string name);

        /** @return  throw: VariableDoesNotExistsException*. */
        std::shared_ptr<Value> eval() override;
        Expressions type() const override;
        operator std::string() override;

        ~VariableExpression();
        void accept(Visitor* visitor);
        friend Visitor;
        friend VariablePrinter;
        friend compiler::CompilerVisitor;
    };
}

#endif // VARIABLEEXPRESSION_H_INCLUDED
