#ifndef EXPRESSION_H_INCLUDED
#define EXPRESSION_H_INCLUDED

#include <memory>
#include <string>
#include "../Value/value.h"
#include "../Visitor/node.h"
#include "../Compiler/compilervisitor.h"

namespace SlavaScript::lang{
    enum class Expressions{
        ArrayExpression,
        AssignmentExpression,
        BinaryExpression,
        ConditionalExpression,
        MapExpression,
        SuffixExpression,
        SuffixAssignmentExpression,
        TernaryExpression,
        UnaryExpression,
        ValueExpression,
        VariableExpression
    };

    class Expression : public Node{
    public:
        virtual std::shared_ptr<Value> eval() = 0;
        virtual operator std::string() = 0;
        virtual ~Expression(){}
        virtual Expressions type() = 0;
    };
}

#endif // EXPRESSION_H_INCLUDED
