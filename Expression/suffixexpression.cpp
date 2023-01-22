#include "suffixexpression.h"
#include "variableexpression.h"

using namespace SlavaScript::lang;


SuffixExpression::SuffixExpression(Expression* root, std::vector<SuffixElement*> access) : root(root), access(access) {}

std::shared_ptr<Value> SuffixExpression::get(){
    for(SuffixElement* element : access) {
        lastContainer = container;
        container = element -> get(container);
    }
    return container;
}

std::shared_ptr<Value> SuffixExpression::set(std::shared_ptr<Value> value){
    access.back() -> set(lastContainer, value);
    return value;
}

std::shared_ptr<Value> SuffixExpression::eval(){
    container = root -> eval();
    return get();
}

Expressions SuffixExpression::type() const{
    return Expressions::SuffixExpression;
}

SuffixExpression::operator std::string(){
    std::string result = std::string(*root);
    for(SuffixElement* element : access) result += std::string(*element);
    return result;
}

SuffixExpression::~SuffixExpression() {}

void SuffixExpression::accept(Visitor* visitor){
    visitor -> visit(this);
}
