#ifndef CONTAINERASSIGNMENTSTATEMENT_H_INCLUDED
#define CONTAINERASSIGNMENTSTATEMENT_H_INCLUDED

#include "../Expression/assignmentexpression.h"
#include "../Expression/containeraccessexpression.h"
#include "../Expression/expression.h"
#include "../Visitor/assignvalidator.h"

namespace SlavaScript{ namespace lang{
    class ContainerAssignmentExpression : public Expression{
    private:
        AssignmentOperator operation;
        ContainerAccessExpression* containerExpr;
        Expression* expression;
    public:
        ContainerAssignmentExpression(AssignmentOperator operation, ContainerAccessExpression* containerExpr, Expression* expression) : operation(operation), containerExpr(containerExpr), expression(expression) {}
        Expressions type(){ return Expressions::ContainerAssignmentExpression; }
        std::shared_ptr<Value> eval();
        operator std::string();
        ~ContainerAssignmentExpression();
        void accept(Visitor* visitor);
        friend Visitor;
        friend AssignValidator;
        friend compiler::CompilerVisitor;
    };
}}

#endif // CONTAINERASSIGNMENTSTATEMENT_H_INCLUDED
