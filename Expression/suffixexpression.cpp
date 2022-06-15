#include "suffixexpression.h"
#include "../Lib/variables.h"
#include "../Value/numbervalue.h"
#include "../Value/stringvalue.h"
#include "../Lib/moduleobject.h"
#include "../Value/objectvalue.h"
#include "../Value/integrationvalue.h"
#include "../Exception/typeexception.h"
#include "variableexpression.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::TypeException;

SuffixExpression::SuffixExpression(std::string variable, std::vector<SuffixElement*> access){
    (*this) = SuffixExpression(new VariableExpression(variable), access);
}

SuffixExpression::SuffixExpression(Expression* root, std::vector<SuffixElement*> access) : root(root), access(access) {}

std::shared_ptr<Value> SuffixExpression::eval(){
    container = root -> eval();
    return get();
}

std::shared_ptr<Value> SuffixExpression::get(){
    for(SuffixElement* element : access) {
        lastContainer = element -> get(lastContainer, container);
        container.swap(lastContainer);
    }
    return container;
}

std::shared_ptr<Value> SuffixExpression::set(std::shared_ptr<Value> value){
    access.back() -> set(lastContainer, value);
    return value;
}

SuffixExpression::operator std::string(){
    std::string result = std::string(*root);
    for(SuffixElement* element : access) result += std::string(*element);
    return result;
}

void SuffixExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}
