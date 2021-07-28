#include "names.h"
#include "variables.h"
#include "functions.h"
#include "classdeclarations.h"
#include "../Value/functionvalue.h"
#include "../Value/nullvalue.h"
#include "../Exception/variabledoesnotexistsexception.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::VariableDoesNotExistsException;

std::shared_ptr<Value> Names::get(std::string name, bool ignore){
    if (Variables::isExists(name)) return Variables::get(name);
    if (Functions::isExists(name)) SH_RET(FunctionValue, Functions::get(name));
    /** Classes **/
    if (ignore) return NullValue::NULL_;
    throw new VariableDoesNotExistsException(name);
}

NamedValue Names::getNamed(std::string name){
    NamedValue value;
    value.name = name;
    value.variable = Variables::save(name);
    value.function = Functions::save(name);
    value.classDec = ClassDeclarations::save(name);
    return value;
}

void Names::erase(std::string name){
    Variables::erase(name);
    Functions::erase(name);
    ClassDeclarations::erase(name);
}

void Names::erase(std::string name, int type){
    if (type != 1) Variables::erase(name);
    if (type != 2) Functions::erase(name);
    if (type != 3) ClassDeclarations::erase(name);
}

void Names::pushScope(){
    Variables::pushScope();
    Functions::pushScope();
    ClassDeclarations::pushScope();
}

void Names::popScope(){
    Variables::popScope();
    Functions::popScope();
    ClassDeclarations::popScope();
}

void Names::copyScope(){
    Variables::copyScope();
    Functions::copyScope();
    ClassDeclarations::copyScope();
}

void Names::init(){
    Variables::init();
    Functions::init();
    ClassDeclarations::init();
}

bool Names::isExists(std::string name){
    return Variables::isExists(name) || Functions::isExists(name) || ClassDeclarations::isExists(name);
}

void Names::setVariable(std::string key, std::shared_ptr<Value> value){
    erase(key, 1);
    Variables::set(key, value);
}

void Names::setFunction(std::string key, std::shared_ptr<Function> function, ArgumentsInfo info){
    erase(key, 2);
    Functions::set(key, function, info);
}

void Names::setClass(std::string key, ClassDeclarationsStatement* classDef){
    erase(key, 3);
    ClassDeclarations::set(key, classDef);
}
#include <iostream>
void Names::restore(NamedValue named){
    std::cout << "S\n";
    erase(named.name);
    std::cout << "T\n";
    if (named.variable != nullptr) Variables::restore(named);
    if (named.function.size() != 0) Functions::restore(named);
    if (named.classDec != nullptr) ClassDeclarations::restore(named);
}
