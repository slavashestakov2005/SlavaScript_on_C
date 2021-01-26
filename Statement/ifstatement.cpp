#include "ifstatement.h"

using namespace SlavaScript::lang;

void IfStatement::execute(){
    if (expression -> eval() -> asBool()) ifStatement -> execute();
    else if (elseStatement != nullptr) elseStatement -> execute();
}

IfStatement::operator std::string(){
    std::string result = "if " + std::string(*expression) + " " + std::string(*ifStatement);
    if (elseStatement != nullptr){
        result += "\nelse " + std::string(*elseStatement);
    }
    return result;
}

IfStatement::~IfStatement(){
    delete expression;
    expression = nullptr;
    delete ifStatement;
    ifStatement = nullptr;
    delete elseStatement;
    elseStatement = nullptr;
}

void IfStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}
