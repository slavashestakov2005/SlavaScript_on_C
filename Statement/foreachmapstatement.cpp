#include "breakstatement.h"
#include "continuestatement.h"
#include "foreachmapstatement.h"
#include "../Lib/names.h"
#include "../Value/mapvalue.h"
#include "../Exception/typeexception.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::TypeException;

void ForeachMapStatement::execute(){
    NamedValue startKey = Names::getNamed(key), startValue = Names::getNamed(value);
    std::shared_ptr<Value> containerValue = container -> eval();
    if (containerValue -> type() != Values::MAP) throw new TypeException("Map expected in foreach");
    for(auto now : *CAST(MapValue, containerValue)){
        Names::setVariable(key, now.first);
        Names::setVariable(value, now.second);
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
    Names::restore(startKey);
    Names::restore(startValue);
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
