#include <Statement/importstatement.h>
#include <Visitor/importadder.h>


using namespace SlavaScript::lang;

void ImportAdder::visit(ImportStatement* v) {
    v -> execute();
}
