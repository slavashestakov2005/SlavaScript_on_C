#pragma once

#include <string>


namespace SlavaScript::lang {
    enum class UnaryOperator {
        PLUS,           /// +
        NEGATIVE,       /// -
        NOT,            /// !
        COMPLEMENT,     /// ~
        PLUSPLUS,       /// ++
        MINUSMINUS,     /// --
    };

    std::string getOperator(UnaryOperator);
}
