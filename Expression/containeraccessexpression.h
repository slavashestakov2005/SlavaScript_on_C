#ifndef CONTAINERACCESSEXPRESSION_H_INCLUDED
#define CONTAINERACCESSEXPRESSION_H_INCLUDED

#include <vector>
#include "containeracceselement.h"
#include "expression.h"
#include "../Value/arrayvalue.h"
#include "../Value/mapvalue.h"
#include "../Visitor/assignvalidator.h"

namespace SlavaScript{ namespace lang{
    class ContainerAccessExpression : public Expression{
    private:
        Expression* root;
        std::vector<ContainerAccessElement> indices;
    public:
        ContainerAccessExpression(std::string variable, std::vector<ContainerAccessElement> indices);
        ContainerAccessExpression(Expression* root, std::vector<ContainerAccessElement> indices);
        Expressions type(){ return Expressions::ContainerAccessExpression; }
        std::shared_ptr<Value> eval();
        /** @return  throw: std::logic_error*, TypeException*. */
        std::shared_ptr<Value> get();
        /** @return  throw: std::logic_error*, TypeException*. */
        std::shared_ptr<Value> set(std::shared_ptr<Value> value);
        /** @return  throw: std::logic_error*, TypeException*. */
        std::shared_ptr<Value> getContainer();
        std::shared_ptr<Value> lastIndex();
        bool lastDot();
        std::shared_ptr<Value> index(int index);
        bool isDot(int index);
        std::shared_ptr<Value> getCopyElement();
        operator std::string();
        ~ContainerAccessExpression(){}
        void accept(Visitor* visitor);
        friend Visitor;
        friend AssignValidator;
        friend compiler::CompilerVisitor;
    };
}}

#endif // CONTAINERACCESSEXPRESSION_H_INCLUDED
