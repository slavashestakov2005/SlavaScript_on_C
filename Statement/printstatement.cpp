#include <iostream>
#include "printstatement.h"

using namespace SlavaScript::lang;

void PrintStatement::execute(){
    std::cout << std::string(*(expression -> eval()));
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
