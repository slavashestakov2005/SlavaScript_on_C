#include "continuestatement.h"

using namespace SlavaScript::lang;

void ContinueStatement::execute(){
    throw this;
}

Statements ContinueStatement::type() const{
    return Statements::ContinueStatement;
}

ContinueStatement::operator std::string(){
    return "continue";
}

void ContinueStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}
