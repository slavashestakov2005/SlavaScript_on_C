#include "containeracceselement.h"
#include "../Value/value.h"

using namespace SlavaScript::lang;

Value* ContainerAccessElement::eval(){
    return expression -> eval();
}

bool ContainerAccessElement::isDot() {
    return dot;
}

ContainerAccessElement::operator std::string(){
    if (dot) return "." + std::string(*expression);
    else return "[" + std::string(*expression) + "]";
}
