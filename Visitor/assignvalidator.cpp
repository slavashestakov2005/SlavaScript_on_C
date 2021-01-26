#include <stdexcept>
#include "assignvalidator.h"
#include "../Expression/assignmentexpression.h"
#include "../Expression/containerassignmentexpression.h"
#include "../Expression/variableexpression.h"
#include "../Lib/variables.h"

using namespace SlavaScript::lang;

void AssignValidator::visit(AssignmentExpression* v){
    v -> expression -> accept(this);
    if (Variables::isExists(v -> variable)) throw std::logic_error("Cannot assign value to constant");
}

void AssignValidator::visit(ContainerAssignmentExpression* v){
    v -> containerExpr -> accept(this);
    v -> expression -> accept(this);
    if (v -> containerExpr -> root -> type() == Expressions::VariableExpression && Variables::isExists(((VariableExpression*) v -> containerExpr -> root) -> name)) throw std::logic_error("Cannot assign value to constant");
}
