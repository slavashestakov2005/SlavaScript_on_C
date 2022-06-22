#include "returnstatement.h"

using namespace SlavaScript::lang;

ReturnStatement::ReturnStatement(Expression* expression) : expression(expression) {}

std::shared_ptr<Value> ReturnStatement::getResult(){
    return result;
}

void ReturnStatement::execute(){
    result = expression -> eval();
    throw this;
}

Statements ReturnStatement::type() const{
    return Statements::ReturnStatement;
}

ReturnStatement::operator std::string(){
    return "return " + std::string(*expression);
}

ReturnStatement::~ReturnStatement(){
    delete expression;
    expression = nullptr;
}

void ReturnStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}
