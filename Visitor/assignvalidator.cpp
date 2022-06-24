#include "assignvalidator.h"
#include "../Exception/exceptions.h"
#include "../Expression/assignmentexpression.h"
#include "../Expression/suffixassignmentexpression.h"
#include "../Expression/variableexpression.h"
#include "../Lib/variables.h"

using namespace SlavaScript::lang;
using SlavaScript::exceptions::LogicException;

void AssignValidator::visit(AssignmentExpression* v){
    v -> expression -> accept(this);
    if (Variables::isExists(v -> variable)) throw LogicException("Cannot assign value to constant");
}

void AssignValidator::visit(SuffixAssignmentExpression* v){
    v -> containerExpr -> accept(this);
    v -> expression -> accept(this);
    if (v -> containerExpr -> root -> type() == Expressions::VariableExpression && Variables::isExists(((VariableExpression*) v -> containerExpr -> root) -> name)) throw LogicException("Cannot assign value to constant");
}
