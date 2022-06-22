#include "throwstatement.h"
#include "trystatement.h"
#include "../Lib/names.h"

using namespace SlavaScript::lang;

TryStatement::TryStatement(Statement* body, std::string name, Statement* catchBlock) : body(body), name(name), catchBlock(catchBlock) {}

void TryStatement::execute(){
    NamedValue start = Names::getNamed(name);
    try{
        body -> execute();
    } catch(ThrowStatement* ex){
        Names::setVariable(name, ex -> getResult());
        catchBlock -> execute();
    }
    Names::restore(start);
}

Statements TryStatement::type() const{
    return Statements::TryStatement;
}

TryStatement::operator std::string(){
    std::string result = "try " + std::string(*body) + " catch '" + name + "' " + std::string(*catchBlock);
    return result;
}

TryStatement::~TryStatement(){
    delete body;
    body = nullptr;
    delete catchBlock;
    catchBlock = nullptr;
}

void TryStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}
