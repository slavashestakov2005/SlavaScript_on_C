#ifndef VISITOR_H_INCLUDED
#define VISITOR_H_INCLUDED

namespace SlavaScript::lang{
    class ArrayExpression;
    class AssignmentExpression;
    class BinaryExpression;
    class BlockStatement;
    class BreakStatement;
    class ClassDeclarationsStatement;
    class ConditionalExpression;
    class ContinueStatement;
    class DoWhileStatement;
    class ExprStatement;
    class ForeachArrayStatement;
    class ForeachMapStatement;
    class ForStatement;
    class FunctionDefineStatement;
    class IfStatement;
    class IntegrationStatement;
    class ImportStatement;
    class MapExpression;
    class PrintlnStatement;
    class PrintStatement;
    class ReturnStatement;
    class SuffixExpression;
    class SuffixAssignmentExpression;
    class SwitchStatement;
    class TernaryExpression;
    class ThrowStatement;
    class TryStatement;
    class UnaryExpression;
    class ValueExpression;
    class VariableExpression;
    class WhileStatement;

    class Visitor{
    public:
        virtual void visit(ArrayExpression* v);
        virtual void visit(AssignmentExpression* v);
        virtual void visit(BinaryExpression* v);
        virtual void visit(BlockStatement* v);
        virtual void visit(BreakStatement* v);
        virtual void visit(ClassDeclarationsStatement* v);
        virtual void visit(ConditionalExpression* v);
        virtual void visit(ContinueStatement* v);
        virtual void visit(DoWhileStatement* v);
        virtual void visit(ExprStatement* v);
        virtual void visit(ForeachArrayStatement* v);
        virtual void visit(ForeachMapStatement* v);
        virtual void visit(ForStatement* v);
        virtual void visit(FunctionDefineStatement* v);
        virtual void visit(IfStatement* v);
        virtual void visit(IntegrationStatement* v);
        virtual void visit(ImportStatement* v);
        virtual void visit(MapExpression* v);
        virtual void visit(PrintlnStatement* v);
        virtual void visit(PrintStatement* v);
        virtual void visit(ReturnStatement* v);
        virtual void visit(SuffixAssignmentExpression* v);
        virtual void visit(SuffixExpression* v);
        virtual void visit(SwitchStatement* v);
        virtual void visit(TernaryExpression* v);
        virtual void visit(ThrowStatement* v);
        virtual void visit(TryStatement* v);
        virtual void visit(UnaryExpression* v);
        virtual void visit(ValueExpression* v);
        virtual void visit(VariableExpression* v);
        virtual void visit(WhileStatement* v);
    };
}

#endif // VISITOR_H_INCLUDED
