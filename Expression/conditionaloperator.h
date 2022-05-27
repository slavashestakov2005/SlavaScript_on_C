#ifndef CONDITIONALOPERATOR_H_INCLUDED
#define CONDITIONALOPERATOR_H_INCLUDED

#include <string>

namespace SlavaScript::lang{
    enum class ConditionalOperator{
        EQUALS,     /// ==
        NOT_EQUALS, /// !=

        LT,         /// <
        LTEQ,       /// <=
        GT,         /// >
        GTEQ,       /// >=

        AND,        /// &&
        OR          /// ||
    };

    std::string getOperator(ConditionalOperator);
}

#endif // CONDITIONALOPERATOR_H_INCLUDED
