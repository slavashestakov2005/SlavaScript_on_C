#pragma once

#include <string>


namespace SlavaScript::lang {
    enum class AssignmentOperator {
        ASSIGN,         /// =
        ADD,            /// +=
        SUBSTRACT,      /// -=
        MULTIPLY,       /// *=
        DIVIDE,         /// /=
        REMAINDER,      /// %=
        POWER,          /// **=

        AND,            /// &=
        OR,             /// |=
        XOR,            /// ^=
        LSHIFT,         /// <<=
        RSHIFT,         /// >>=

        PLUSPLUS_,      /// ++_
        MINUSMINUS_,    /// --_
        _PLUSPLUS,      /// _++
        _MINUSMINUS     /// _--
    };

    std::string getOperator(AssignmentOperator);
}
