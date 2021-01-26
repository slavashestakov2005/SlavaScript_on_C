#ifndef BINARYOPERATOR_H_INCLUDED
#define BINARYOPERATOR_H_INCLUDED

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
}}

#endif // BINARYOPERATOR_H_INCLUDED
