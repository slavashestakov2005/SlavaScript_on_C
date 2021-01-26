#include "importadder.h"
#include "../Statement/importstatement.h"

using namespace SlavaScript::lang;

void ImportAdder::visit(ImportStatement* v){
    v -> execute();
}
