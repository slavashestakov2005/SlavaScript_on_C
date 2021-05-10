#ifndef BINARYOPERATOR_H_INCLUDED
#define BINARYOPERATOR_H_INCLUDED

#include <string>

namespace SlavaScript{ namespace lang{
    enum class BinaryOperator{
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
}}

#endif // BINARYOPERATOR_H_INCLUDED
