#include "breakstatement.h"
#include "continuestatement.h"
#include "foreacharraystatement.h"
#include "../Lib/names.h"
#include "../Value/arrayvalue.h"
#include "../Exception/typeexception.h"
#include "../Value/value.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::TypeException;

void ForeachArrayStatement::execute(){
    NamedValue start = Names::getNamed(variable);
    std::shared_ptr<Value> containerValue = container -> eval();
    if (containerValue -> type() != Values::ARRAY) throw new TypeException("Array expected in foreach");
    for (auto now : *CAST(ArrayValue, containerValue)){
        Names::setVariable(variable, now);
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
    Names::restore(start);
}

ForeachArrayStatement::operator std::string(){
    return "for '" + variable + "' : " + std::string(*container) + " " + std::string(*body);
}

ForeachArrayStatement::~ForeachArrayStatement(){
    delete container;
    delete body;
}

void ForeachArrayStatement::accept(Visitor* visitor){
    visitor -> visit(this);
}
