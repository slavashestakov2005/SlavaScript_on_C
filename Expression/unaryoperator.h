#ifndef UNARYOPERATOR_H_INCLUDED
#define UNARYOPERATOR_H_INCLUDED

namespace SlavaScript{ namespace lang{
    enum class UnaryOperator{
        PLUS,           /// +
        NEGATIVE,       /// -
        NOT,            /// !
        COMPLEMENT,     /// ~
        PLUSPLUS,       /// ++
        MINUSMINUS,     /// --
    };
}}

#endif // UNARYOPERATOR_H_INCLUDED
