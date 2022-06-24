#include "breakstatement.h"

using namespace SlavaScript::lang;

void BreakStatement::execute(){
    throw *this;
}

Statements BreakStatement::type() const{
    return Statements::BreakStatement;
}

BreakStatement::operator std::string(){
    return "break";
}

void BreakStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}
