#include "breakstatement.h"

using namespace SlavaScript::lang;

void BreakStatement::execute(){
    throw this;
}

BreakStatement::operator std::string(){
    return "break";
}

void BreakStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}
