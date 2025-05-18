#include <Lib/names.h>
#include <Lib/utils.h>
#include <Statement/breakstatement.h>
#include <Statement/continuestatement.h>
#include <Statement/foreachmapstatement.h>
#include <Value/mapvalue.h>


using namespace SlavaScript::lang;

ForeachMapStatement::ForeachMapStatement(std::string key, std::string value, Expression* container, Statement* body) : key(key), value(value), container(container), body(body) {}

void ForeachMapStatement::execute() {
    NamedValue startKey = Names::getNamed(key), startValue = Names::getNamed(value);
    std::shared_ptr<Value> containerValue = container -> eval();
    argType(Values::MAP, containerValue);
    for (auto now : *CAST(MapValue, containerValue)) {
        Names::setVariable(key, now.first);
        Names::setVariable(value, now.second);
        try {
            body -> execute();
        } catch (BreakStatement& bs) {
            break;
        } catch (ContinueStatement& cs) {
            // continue;
        }
    }
    Names::restore(startKey);
    Names::restore(startValue);
}

Statements ForeachMapStatement::type() const {
    return Statements::ForeachMapStatement;
}

ForeachMapStatement::operator std::string() {
    return "for '" + key + "', '" + value + "' : " + std::string(*container) + " " + std::string(*body);
}

ForeachMapStatement::~ForeachMapStatement() {
    delete container;
    delete body;
}

void ForeachMapStatement::accept(Visitor* visitor) {
    visitor -> visit(this);
}
