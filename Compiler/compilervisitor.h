#ifndef COMPILERVISITOR_H_INCLUDED
#define COMPILERVISITOR_H_INCLUDED

#include "../Visitor/visitor.h"

namespace SlavaScript::compiler{
    class CompilerVisitor : public lang::Visitor{
    public:
        void visit(lang::BlockStatement* v);
        void visit(lang::BreakStatement* v);
        void visit(lang::ClassDeclarationsStatement* v);
        void visit(lang::ContinueStatement* v);
        void visit(lang::DoWhileStatement* v);
        void visit(lang::ExprStatement* v);
        void visit(lang::ForeachArrayStatement* v);
        void visit(lang::ForeachMapStatement* v);
        void visit(lang::ForStatement* v);
        void visit(lang::FunctionDefineStatement* v);
        void visit(lang::IfStatement* v);
        void visit(lang::IntegrationStatement* v);
        void visit(lang::ImportStatement* v);
        void visit(lang::PrintlnStatement* v);
        void visit(lang::PrintStatement* v);
        void visit(lang::ReturnStatement* v);
        void visit(lang::SwitchStatement* v);
        void visit(lang::ThrowStatement* v);
        void visit(lang::TryStatement* v);
        void visit(lang::WhileStatement* v);

        void visit(lang::ArrayExpression* v);
        void visit(lang::AssignmentExpression* v);
        void visit(lang::BinaryExpression* v);
        void visit(lang::ConditionalExpression* v);
        void visit(lang::MapExpression* v);
        void visit(lang::SuffixExpression* v);
        void visit(lang::SuffixAssignmentExpression* v);
        void visit(lang::TernaryExpression* v);
        void visit(lang::UnaryExpression* v);
        void visit(lang::ValueExpression* v);
        void visit(lang::VariableExpression* v);
    };
}

#endif // COMPILERVISITOR_H_INCLUDED
