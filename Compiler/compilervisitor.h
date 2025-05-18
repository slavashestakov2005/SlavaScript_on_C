#pragma once

#include <Visitor/visitor.h>


namespace SlavaScript::compiler {
    class CompilerVisitor : public lang::Visitor {
    public:
        void visit(lang::BlockStatement* v) override;
        void visit(lang::BreakStatement* v) override;
        void visit(lang::ClassDeclarationsStatement* v) override;
        void visit(lang::ContinueStatement* v) override;
        void visit(lang::DoWhileStatement* v) override;
        void visit(lang::ExprStatement* v) override;
        void visit(lang::ForeachArrayStatement* v) override;
        void visit(lang::ForeachMapStatement* v) override;
        void visit(lang::ForStatement* v) override;
        void visit(lang::FunctionDefineStatement* v) override;
        void visit(lang::IfStatement* v) override;
        void visit(lang::IntegrationStatement* v) override;
        void visit(lang::ImportStatement* v) override;
        void visit(lang::PrintlnStatement* v) override;
        void visit(lang::PrintStatement* v) override;
        void visit(lang::ReturnStatement* v) override;
        void visit(lang::SwitchStatement* v) override;
        void visit(lang::ThrowStatement* v) override;
        void visit(lang::TryStatement* v) override;
        void visit(lang::WhileStatement* v) override;

        void visit(lang::ArrayExpression* v) override;
        void visit(lang::AssignmentExpression* v) override;
        void visit(lang::BinaryExpression* v) override;
        void visit(lang::ConditionalExpression* v) override;
        void visit(lang::MapExpression* v) override;
        void visit(lang::SuffixExpression* v) override;
        void visit(lang::SuffixAssignmentExpression* v) override;
        void visit(lang::TernaryExpression* v) override;
        void visit(lang::UnaryExpression* v) override;
        void visit(lang::ValueExpression* v) override;
        void visit(lang::VariableExpression* v) override;
    };
}
