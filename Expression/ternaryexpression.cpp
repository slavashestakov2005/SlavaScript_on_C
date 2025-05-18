#include <Expression/ternaryexpression.h>


using namespace SlavaScript::lang;


TernaryExpression::TernaryExpression(Expression* condition, Expression* trueExpr, Expression* falseExpr) : condition(condition), trueExpr(trueExpr), falseExpr(falseExpr) {}

std::shared_ptr<Value> TernaryExpression::eval() {
    if (condition -> eval() -> asBool()) return trueExpr -> eval();
    else return falseExpr -> eval();
}

Expressions TernaryExpression::type() const {
    return Expressions::TernaryExpression;
}

TernaryExpression::operator std::string() {
    return "[" + std::string(*condition) + " ? " + std::string(*trueExpr) + " : " + std::string(*falseExpr) + "]";
}

TernaryExpression::~TernaryExpression() {
    delete condition;
    condition = nullptr;
    delete trueExpr;
    trueExpr = nullptr;
    delete falseExpr;
    falseExpr = nullptr;
}

void TernaryExpression::accept(Visitor* visitor) {
    visitor -> visit(this);
}
