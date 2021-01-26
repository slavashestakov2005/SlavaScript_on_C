#include "breakstatement.h"
#include "continuestatement.h"
#include "dowhilestatement.h"

using namespace SlavaScript::lang;

void DoWhileStatement::execute(){
    do{
        try{
            body -> execute();
        }
        catch(BreakStatement* bs){
            break;
        }
        catch(ContinueStatement* cs){
            //continue;
        }
    }while(condition -> eval() -> asBool());
}

DoWhileStatement::operator std::string(){
    return "do " + std::string(*body) + " while " + std::string(*condition);
}

DoWhileStatement::~DoWhileStatement(){
    delete body;
    body = nullptr;
    delete condition;
    condition = nullptr;
}

void DoWhileStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}
