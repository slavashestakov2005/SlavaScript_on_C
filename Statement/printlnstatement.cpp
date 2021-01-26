#include <iostream>
#include "printlnstatement.h"

using namespace SlavaScript::lang;

void PrintlnStatement::execute(){
    std::cout << std::string(*(expression -> eval())) << std::endl;
}

PrintlnStatement::operator std::string(){
    return "println " + std::string(*expression);
}

PrintlnStatement::~PrintlnStatement(){
    delete expression;
    expression = nullptr;
}

void PrintlnStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}
