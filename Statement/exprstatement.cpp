#include "exprstatement.h"

using namespace SlavaScript::lang;

ExprStatement::ExprStatement(Expression* expression) : expression(expression) {}

void ExprStatement::execute(){
    expression -> eval();
}

Statements ExprStatement::type() const{
    return Statements::ExprStatement;
}

ExprStatement::operator std::string(){
    return std::string(*expression);
}

ExprStatement::~ExprStatement(){
    delete expression;
}

void ExprStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}
