#include <Statement/ifstatement.h>


using namespace SlavaScript::lang;

IfStatement::IfStatement(Expression* expression, Statement* ifStatement, Statement* elseStatement) : expression(expression), ifStatement(ifStatement), elseStatement(elseStatement) {}

void IfStatement::execute() {
    if (expression -> eval() -> asBool()) ifStatement -> execute();
    else if (elseStatement != nullptr) elseStatement -> execute();
}

Statements IfStatement::type() const {
    return Statements::IfStatement;
}

IfStatement::operator std::string() {
    std::string result = "if " + std::string(*expression) + " " + std::string(*ifStatement);
    if (elseStatement != nullptr) {
        result += "\nelse " + std::string(*elseStatement);
    }
    return result;
}

IfStatement::~IfStatement() {
    delete expression;
    expression = nullptr;
    delete ifStatement;
    ifStatement = nullptr;
    delete elseStatement;
    elseStatement = nullptr;
}

void IfStatement::accept(Visitor* visitor) {
    visitor -> visit(this);
}
