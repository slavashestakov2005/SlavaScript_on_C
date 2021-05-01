#include "throwstatement.h"
#include "trystatement.h"
#include "../Lib/variables.h"

using namespace SlavaScript::lang;

void TryStatement::execute(){
    std::shared_ptr<Value> start = Variables::isExists(name) ? Variables::get(name) : nullptr;
    try{
        body -> execute();
    } catch(ThrowStatement* ex){
        Variables::set(name, ex -> getResult());
        catchBlock -> execute();
    }
    if (start != nullptr) Variables::set(name, start);
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
