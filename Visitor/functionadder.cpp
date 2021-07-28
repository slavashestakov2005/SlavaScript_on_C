#include "functionadder.h"
#include "../Lib/functions.h"
#include "../Statement/functiondefinestatement.h"

using namespace SlavaScript::lang;

void FunctionAdder::visit(FunctionDefineStatement* v){
    v -> body -> accept(this);
    v -> execute(true);
}
