#include "breakstatement.h"
#include "continuestatement.h"
#include "whilestatement.h"

using namespace SlavaScript::lang;

WhileStatement::WhileStatement(Expression* condition, Statement* body) : condition(condition), body(body) {}

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

Statements WhileStatement::type() const{
    return Statements::WhileStatement;
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
