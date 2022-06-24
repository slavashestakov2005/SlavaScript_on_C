#include "assignmentoperator.h"
#include "binaryoperator.h"
#include "conditionaloperator.h"
#include "unaryoperator.h"

using namespace SlavaScript::lang;


namespace{
    std::string assign_op[int(AssignmentOperator::_MINUSMINUS) + 1] = {
        "=", "+=", "-=", "*=", "/=", "%=", "**=", "&=", "|=", "^=", "<<=", ">>=", "++", "--", "++", "--"
    };

    std::string binary_op[int(BinaryOperator::RSHIFT) + 1] = {
        "+", "-", "*", "/", "%", "**", "&", "|", "^", "<<", ">>"
    };

    std::string conditional_op[int(ConditionalOperator::OR) + 1] = {
        "==", "!=", "<", "<=", ">", ">=", "<=>", "&&", "||"
    };

    std::string unary_op[int(UnaryOperator::MINUSMINUS) + 1] = {
        "+", "-", "!", "~", "++", "--"
    };
}


std::string SlavaScript::lang::getOperator(AssignmentOperator a){
    return assign_op[int(a)];
}

std::string SlavaScript::lang::getOperator(BinaryOperator b){
    return binary_op[int(b)];
}

std::string SlavaScript::lang::getOperator(ConditionalOperator c){
    return conditional_op[int(c)];
}

std::string SlavaScript::lang::getOperator(UnaryOperator u){
    return unary_op[int(u)];
}
