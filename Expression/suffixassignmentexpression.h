#ifndef SUFFIXaSSIGNMENTSTATEMENT_H_INCLUDED
#define SUFFIXASSIGNMENTSTATEMENT_H_INCLUDED

#include "../Expression/assignmentexpression.h"
#include "../Expression/suffixexpression.h"
#include "../Expression/expression.h"
#include "../Visitor/assignvalidator.h"

namespace SlavaScript::lang{
    class SuffixAssignmentExpression : public Expression{
    private:
        AssignmentOperator operation;
        SuffixExpression* containerExpr;
        Expression* expression;
    public:
        SuffixAssignmentExpression(AssignmentOperator operation, SuffixExpression* containerExpr, Expression* expression) : operation(operation), containerExpr(containerExpr), expression(expression) {}
        Expressions type(){ return Expressions::SuffixAssignmentExpression; }
        std::shared_ptr<Value> eval();
        operator std::string();
        ~SuffixAssignmentExpression();
        void accept(Visitor* visitor);
        friend Visitor;
        friend AssignValidator;
        friend compiler::CompilerVisitor;
    };
}

#endif // SUFFIXASSIGNMENTSTATEMENT_H_INCLUDED
