#include <Statement/breakstatement.h>
#include <Statement/continuestatement.h>
#include <Statement/dowhilestatement.h>


using namespace SlavaScript::lang;

DoWhileStatement::DoWhileStatement(Expression* condition, Statement* body) : condition(condition), body(body) {}

void DoWhileStatement::execute() {
    do {
        try {
            body -> execute();
        } catch (BreakStatement& bs) {
            break;
        } catch (ContinueStatement& cs) {
            // continue;
        }
    } while (condition -> eval() -> asBool());
}

Statements DoWhileStatement::type() const {
    return Statements::DoWhileStatement;
}

DoWhileStatement::operator std::string() {
    return "do " + std::string(*body) + " while " + std::string(*condition);
}

DoWhileStatement::~DoWhileStatement() {
    delete body;
    body = nullptr;
    delete condition;
    condition = nullptr;
}

void DoWhileStatement::accept(Visitor* visitor) {
    visitor -> visit(this);
}
