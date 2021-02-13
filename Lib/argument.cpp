#include "argument.h"

using namespace SlavaScript::lang;

Argument::Argument(std::string name) : name(name), expression(nullptr) {}

Argument::Argument(std::string name, Expression* expression) : name(name), expression(expression) {}

Argument::Argument(std::string name, bool array) : name(name), expression(nullptr), arrayArgument(array) {}

std::string Argument::getName(){
    return name;
}

Expression* Argument::getExpression(){
    return expression;
}

bool Argument::isArrayArgument(){
    return arrayArgument;
}

Argument::operator std::string(){
    return (arrayArgument ? "*'" : "'") + name + "'" + (expression == nullptr ? "" : " = " + std::string(*expression));
}
