#include <Statement/functiondefinestatement.h>
#include <Visitor/functionadder.h>


using namespace SlavaScript::lang;

void FunctionAdder::visit(FunctionDefineStatement* v) {
    v -> body -> accept(this);
    v -> execute(true);
}
