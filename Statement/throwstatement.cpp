#include <Statement/throwstatement.h>


using namespace SlavaScript::lang;

ThrowStatement::ThrowStatement(Expression* expression) : expression(expression) {}

std::shared_ptr<Value> ThrowStatement::getResult() {
    return result;
}

void ThrowStatement::execute() {
    result = expression -> eval();
    throw this;
}

Statements ThrowStatement::type() const {
    return Statements::ThrowStatement;
}

ThrowStatement::operator std::string() {
    return "throw " + std::string(*expression);
}

ThrowStatement::~ThrowStatement() {
    delete expression;
    expression = nullptr;
}

void ThrowStatement::accept(Visitor* visitor) {
    visitor -> visit(this);
}
