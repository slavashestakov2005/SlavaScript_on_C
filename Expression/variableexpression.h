#ifndef VARIABLEEXPRESSION_H_INCLUDED
#define VARIABLEEXPRESSION_H_INCLUDED

#include "expression.h"
#include "../Visitor/variableprinter.h"

namespace SlavaScript{ namespace lang{
    class VariableExpression : public Expression{
    public:
        std::string name;
        VariableExpression(std::string name) : name(name) {}
        Expressions type(){ return Expressions::VariableExpression; }
        /** @return  throw: VariableDoesNotExistsException*. */
        Value* eval();
        operator std::string();
        void accept(Visitor* visitor);
        friend Visitor;
        friend VariablePrinter;
        friend compiler::CompilerVisitor;
    };
}}

#endif // VARIABLEEXPRESSION_H_INCLUDED
