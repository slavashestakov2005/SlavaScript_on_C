#include <Exception/exceptions.h>
#include <Lib/class.h>


using namespace SlavaScript::lang;
using SlavaScript::exceptions::UnknownPropertyException;


std::string Class::getName() const {
    return name;
}

void Class::addMethod(std::string name, std::shared_ptr<Function> method) {
    methods[name] = method;
}

std::shared_ptr<Function> Class::getFunction(std::string name) {
    if (!isExists(name)) throw UnknownPropertyException(name);
    return methods[name];
}

bool Class::isExists(std::string name) {
    return methods.find(name) != methods.end();
}

Class::~Class() {}
