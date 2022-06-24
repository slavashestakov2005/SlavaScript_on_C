#include "names.h"
#include "../Exception/exceptions.h"
#include "classes.h"
#include "variables.h"
#include "../Value/functionvalue.h"
#include "../Value/nullvalue.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::UnknownVariableException;


std::shared_ptr<Value> Names::get(std::string name, bool ignore){
    if (Variables::isExists(name)) return Variables::get(name);
    if (Functions::isExists(name)) SH_RET(FunctionValue, Functions::get(name));
    if (Classes::isExists(name)) return Classes::get(name);
    if (ignore) return NullValue::NULL_;
    throw UnknownVariableException(name);
}

NamedValue Names::getNamed(std::string name){
    NamedValue value;
    value.name = name;
    value.variable = Variables::save(name);
    value.function = Functions::save(name);
    value.classDec = Classes::save(name);
    return value;
}

void Names::erase(std::string name){
    Variables::erase(name);
    Functions::erase(name);
    Classes::erase(name);
}

void Names::erase(std::string name, int type){
    if (type != 1) Variables::erase(name);
    if (type != 2) Functions::erase(name);
    if (type != 3) Classes::erase(name);
}

void Names::pushScope(){
    Variables::pushScope();
    Functions::pushScope();
    Classes::pushScope();
}

void Names::popScope(){
    Variables::popScope();
    Functions::popScope();
    Classes::popScope();
}

void Names::copyScope(){
    Variables::copyScope();
    Functions::copyScope();
    Classes::copyScope();
}

void Names::init(){
    Variables::init();
    Functions::init();
    Classes::init();
}

bool Names::isExists(std::string name){
    return Variables::isExists(name) || Functions::isExists(name) || Classes::isExists(name);
}

void Names::setVariable(std::string key, std::shared_ptr<Value> value){
    erase(key, 1);
    Variables::set(key, value);
}

void Names::setFunction(std::string key, std::shared_ptr<Function> function, ArgumentsInfo info){
    erase(key, 2);
    Functions::set(key, function, info);
}

void Names::setClass(std::string key, std::shared_ptr<ClassValue> classDef){
    erase(key, 3);
    Classes::set(key, classDef);
}

void Names::restore(NamedValue named){
    erase(named.name);
    if (named.variable != nullptr) Variables::restore(named);
    if (named.function.size() != 0) Functions::restore(named);
    if (named.classDec != nullptr) Classes::restore(named);
}
