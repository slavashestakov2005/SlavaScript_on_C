#include "visitor.h"
#include "../Expression/all.h"
#include "../Statement/all.h"

using namespace SlavaScript::lang;

void Visitor::visit(ArrayExpression* v){
    for(auto now : v -> elements){
        now -> accept(this);
    }
}

void Visitor::visit(AssignmentExpression* v){
    v -> expression -> accept(this);
}

void Visitor::visit(BinaryExpression* v){
    v -> expr1 -> accept(this);
    v -> expr2 -> accept(this);
}

void Visitor::visit(BlockStatement* v){
    for(auto now : v -> statements){
        now -> accept(this);
    }
}

void Visitor::visit(BreakStatement* v){ }

void Visitor::visit(ClassDeclarationsStatement* v){ }

void Visitor::visit(ConditionalExpression* v){
    v -> expr1 -> accept(this);
    v -> expr2 -> accept(this);
}

void Visitor::visit(ContinueStatement* v){}

void Visitor::visit(DoWhileStatement* v){
    v -> condition -> accept(this);
    v -> body -> accept(this);
}

void Visitor::visit(ExprStatement* v){
    v -> expression -> accept(this);
}

void Visitor::visit(ForeachArrayStatement* v){
    v -> container -> accept(this);
    v -> body -> accept(this);
}

void Visitor::visit(ForeachMapStatement* v){
    v -> container -> accept(this);
    v -> body -> accept(this);
}

void Visitor::visit(ForStatement* v){
    v -> increment -> accept(this);
    v -> initialization -> accept(this);
    v -> body -> accept(this);
    v -> termination -> accept(this);
}

void Visitor::visit(FunctionDefineStatement* v){
    v -> body -> accept(this);
}

void Visitor::visit(IfStatement* v){
    v -> expression -> accept(this);
    v -> ifStatement -> accept(this);
    if (v -> elseStatement != nullptr) v -> elseStatement -> accept(this);
}

void Visitor::visit(IntegrationStatement* v){ }

void Visitor::visit(ImportStatement* v){ }

void Visitor::visit(MapExpression* v){
    for (auto now : v -> elements){
        now.first -> accept(this);
        now.second -> accept(this);
    }
}

void Visitor::visit(PrintlnStatement* v){
    v -> expression -> accept(this);
}

void Visitor::visit(PrintStatement* v){
    v -> expression -> accept(this);
}

void Visitor::visit(ReturnStatement* v){ }

void Visitor::visit(SuffixExpression* v){
    v -> root -> accept(this);
    for(SuffixElement* element : v -> access) element -> accept(this);
}

void Visitor::visit(SuffixAssignmentExpression* v){
    v -> containerExpr -> accept(this);
    v -> expression -> accept(this);
}

void Visitor::visit(SwitchStatement* v){
    v -> start -> accept(this);
    for(unsigned i = 0; i < v -> body.size(); ++i){
        v -> body[i].first -> accept(this);
        v -> body[i].second -> accept(this);
    }
    if (v -> defaultCase != nullptr) v -> defaultCase -> accept(this);
}

void Visitor::visit(TernaryExpression* v){
    v -> condition -> accept(this);
    v -> trueExpr -> accept(this);
    v -> falseExpr -> accept(this);
}

void Visitor::visit(ThrowStatement* v){
    v -> expression -> accept(this);
}

void Visitor::visit(TryStatement* v){
    v -> body -> accept(this);
    v -> catchBlock -> accept(this);
}

void Visitor::visit(UnaryExpression* v){
    v -> expr -> accept(this);
}

void Visitor::visit(ValueExpression* v){ }

void Visitor::visit(VariableExpression* v){ }

void Visitor::visit(WhileStatement* v){
    v -> condition -> accept(this);
    v -> body -> accept(this);
}
