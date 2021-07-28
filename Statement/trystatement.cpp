#include "throwstatement.h"
#include "trystatement.h"
#include "../Lib/names.h"

using namespace SlavaScript::lang;

void TryStatement::execute(){
    std::shared_ptr<Value> start = Names::isExists(name) ? Names::get(name) : nullptr;
    try{
        body -> execute();
    } catch(ThrowStatement* ex){
        Names::setVariable(name, ex -> getResult());
        catchBlock -> execute();
    }
    if (start != nullptr) Names::setVariable(name, start);
    else Names::erase(name);
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
