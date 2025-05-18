#pragma once

#include <string>


namespace SlavaScript::lang {
    enum class BinaryOperator {
        ADD,        /// +
        SUBSTRACT,  /// -
        MULTIPLY,   /// *
        DIVIDE,     /// /
        REMAINDER,  /// %
        POWER,      /// **

        AND,        /// &
        OR,         /// |
        XOR,        /// ^
        LSHIFT,     /// <<
        RSHIFT      /// >>
    };

    std::string getOperator(BinaryOperator);
}
