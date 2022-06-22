#include <iostream>
#include "printstatement.h"

using namespace SlavaScript::lang;

PrintStatement::PrintStatement(Expression* expression) : expression(expression) {}

void PrintStatement::execute(){
    std::cout << std::string(*(expression -> eval()));
}

Statements PrintStatement::type() const{
    return Statements::PrintStatement;
}

PrintStatement::operator std::string(){
    return "print " + std::string(*expression);
}

PrintStatement::~PrintStatement(){
    delete expression;
    expression = nullptr;
}

void PrintStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}
