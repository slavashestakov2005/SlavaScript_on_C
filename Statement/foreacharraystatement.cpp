#include "foreacharraystatement.h"
#include "../Lib/names.h"
#include "../Lib/utils.h"
#include "breakstatement.h"
#include "continuestatement.h"
#include "../Value/arrayvalue.h"

using namespace SlavaScript::lang;


ForeachArrayStatement::ForeachArrayStatement(std::string variable, Expression* container, Statement* body) : variable(variable), container(container), body(body) {}

void ForeachArrayStatement::execute(){
    NamedValue start = Names::getNamed(variable);
    std::shared_ptr<Value> containerValue = container -> eval();
    argType(Values::ARRAY, containerValue);
    for (auto now : *CAST(ArrayValue, containerValue)){
        Names::setVariable(variable, now);
        try{
            body -> execute();
        }
        catch(BreakStatement& bs){
            break;
        }
        catch(ContinueStatement& cs){
            //continue;
        }
    }
    Names::restore(start);
}


Statements ForeachArrayStatement::type() const{
    return Statements::ForeachArrayStatement;
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
