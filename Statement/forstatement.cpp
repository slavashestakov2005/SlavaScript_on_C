#include <Statement/breakstatement.h>
#include <Statement/continuestatement.h>
#include <Statement/forstatement.h>


using namespace SlavaScript::lang;

ForStatement::ForStatement(Statement* initialization, Expression* termination, Statement* increment, Statement* body) : initialization(initialization), termination(termination), increment(increment), body(body) {}

void ForStatement::execute() {
    for (initialization -> execute(); termination -> eval() -> asBool(); increment -> execute()) {
        try {
            body -> execute();
        } catch (BreakStatement& bs) {
            break;
        } catch (ContinueStatement& cs) {
            // continue;
        }
    }
}

Statements ForStatement::type() const {
    return Statements::ForStatement;
}

ForStatement::operator std::string() {
    return "for " + std::string(*initialization) + ", " + std::string(*termination) + ", " + std::string(*increment) + " " + std::string(*body);
}

ForStatement::~ForStatement() {
    delete initialization;
    initialization = nullptr;
    delete termination;
    termination = nullptr;
    delete increment;
    increment = nullptr;
    delete body;
    body = nullptr;
}

void ForStatement::accept(Visitor* visitor) {
    visitor -> visit(this);
}
