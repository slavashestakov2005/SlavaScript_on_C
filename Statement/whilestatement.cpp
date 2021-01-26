#include "breakstatement.h"
#include "continuestatement.h"
#include "whilestatement.h"

using namespace SlavaScript::lang;

void WhileStatement::execute(){
    while(condition -> eval() -> asBool()){
        try{
            body -> execute();
        }
        catch(BreakStatement* bs){
            break;
        }
        catch(ContinueStatement* cs){
            //continue;
        }
    }
}

WhileStatement::operator std::string(){
    return "while " + std::string(*condition) + " " + std::string(*body);
}

WhileStatement::~WhileStatement(){
    delete condition;
    condition = nullptr;
    delete body;
    body = nullptr;
}

void WhileStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}
