#include "breakstatement.h"
#include "continuestatement.h"
#include "forstatement.h"

using namespace SlavaScript::lang;

void ForStatement::execute(){
    for(initialization -> execute(); termination -> eval() -> asBool(); increment -> execute()){
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

ForStatement::operator std::string(){
    return "for " + std::string(*initialization) + ", " + std::string(*termination) + ", " + std::string(*increment) + " " + std::string(*body);
}

ForStatement::~ForStatement(){
    delete initialization;
    initialization = nullptr;
    delete termination;
    termination = nullptr;
    delete increment;
    increment = nullptr;
    delete body;
    body = nullptr;
}

void ForStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}
