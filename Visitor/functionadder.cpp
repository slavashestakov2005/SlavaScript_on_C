#include "functionadder.h"
#include "../Lib/functions.h"
#include "../Statement/functiondefinestatement.h"

using namespace SlavaScript::lang;

void FunctionAdder::visit(FunctionDefineStatement* v){
    v -> body -> accept(this);
    if (Functions::isExists(v -> name)){
        std::string str = "Cannot redefinition function \"" + v -> name + "\" from import";
        throw std::logic_error(str.c_str());
    }
    v -> execute(true);
}
