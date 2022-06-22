#include "class.h"

using namespace SlavaScript::lang;

std::string Class::getName() const{
    return name;
}

void Class::addMethod(std::string name, std::shared_ptr<Function> method){
    methods[name] = method;
}

std::shared_ptr<Function> Class::getFunction(std::string name){
    if (!isExists(name)) throw new exceptions::TypeException("Cannot get method " + name + " from class");
    return methods[name];
}

bool Class::isExists(std::string name){
    return methods.find(name) != methods.end();
}
