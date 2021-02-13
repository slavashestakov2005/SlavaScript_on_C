#include "breakstatement.h"
#include "continuestatement.h"
#include "foreacharraystatement.h"
#include "../Lib/variables.h"
#include "../Value/arrayvalue.h"
#include "../Exception/typeexception.h"
#include "../Value/value.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::TypeException;

void ForeachArrayStatement::execute(){
    Value* start = Variables::isExists(variable) ? Variables::get(variable) : nullptr;
    Value* containerValue = container -> eval();
    if (containerValue -> type() != Values::ARRAY) throw new TypeException("Array expected in foreach");
    for (auto now : *(ArrayValue*) containerValue){
        Variables::set(variable, now);
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
    if (start != nullptr){
        Variables::set(variable, start);
    }
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
