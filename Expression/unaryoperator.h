#ifndef UNARYOPERATOR_H_INCLUDED
#define UNARYOPERATOR_H_INCLUDED

#include <string>

namespace SlavaScript::lang{
    enum class UnaryOperator{
        PLUS,           /// +
        NEGATIVE,       /// -
        NOT,            /// !
        COMPLEMENT,     /// ~
        PLUSPLUS,       /// ++
        MINUSMINUS,     /// --
    };

    std::string getOperator(UnaryOperator);
}

#endif // UNARYOPERATOR_H_INCLUDED
