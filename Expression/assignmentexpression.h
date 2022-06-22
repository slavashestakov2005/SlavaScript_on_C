#ifndef ASSIGNMENTEXPRESSION_H_INCLUDED
#define ASSIGNMENTEXPRESSION_H_INCLUDED

#include "assignmentoperator.h"
#include "expression.h"
#include "../Visitor/assignvalidator.h"
#include "../Visitor/variableprinter.h"

namespace SlavaScript::lang{
    class AssignmentExpression : public Expression{
    private:
        AssignmentOperator operation;
        Expression* expression;
        std::string variable;
    public:
        /** @return  throw: OperationIsNotSupportedException*. */
        static std::shared_ptr<Value> calculate(AssignmentOperator operation, std::shared_ptr<Value> left, std::shared_ptr<Value> right);

        AssignmentExpression(AssignmentOperator operation, std::string variable, Expression* expression);

        std::shared_ptr<Value> eval() override;
        Expressions type() const override;
        operator std::string() override;

        ~AssignmentExpression();
        void accept(Visitor* visitor) override;
        friend Visitor;
        friend VariablePrinter;
        friend AssignValidator;
        friend compiler::CompilerVisitor;
    };
}

#endif // ASSIGNMENTEXPRESSION_H_INCLUDED
