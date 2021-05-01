#include "breakstatement.h"
#include "continuestatement.h"
#include "foreachmapstatement.h"
#include "../Lib/variables.h"
#include "../Value/mapvalue.h"
#include "../Exception/typeexception.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::TypeException;

void ForeachMapStatement::execute(){
    std::shared_ptr<Value> startKey = Variables::isExists(key) ? Variables::get(key) : nullptr;
    std::shared_ptr<Value> startValue = Variables::isExists(value) ? Variables::get(value) : nullptr;
    std::shared_ptr<Value> containerValue = container -> eval();
    if (containerValue -> type() != Values::MAP) throw new TypeException("Map expected in foreach");
    for(auto now : *(std::static_pointer_cast<MapValue>(containerValue))){
        Variables::set(key, now.first);
        Variables::set(value, now.second);
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
    if (startKey != nullptr) Variables::set(key, startKey);
    if (startValue != nullptr) Variables::set(value, startValue);
}

ForeachMapStatement::operator std::string(){
    return "for '" + key + "', '" + value + "' : " + std::string(*container) + " " + std::string(*body);
}

ForeachMapStatement::~ForeachMapStatement(){
    delete container;
    delete body;
}

void ForeachMapStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}
