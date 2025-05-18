#pragma once

#include <memory>
#include <string>

#include <Compiler/compilervisitor.h>
#include <Value/value.h>
#include <Visitor/node.h>


namespace SlavaScript::lang {
    enum class Expressions {
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

    class Expression : public Node {
    public:
        virtual std::shared_ptr<Value> eval() = 0;
        virtual Expressions type() const = 0;
        virtual operator std::string() = 0;

        virtual ~Expression() {}
    };
}
