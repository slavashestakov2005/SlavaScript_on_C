#pragma once

#include <string>


namespace SlavaScript::lang {
    enum class ConditionalOperator {
        EQUALS,     /// ==
        NOT_EQUALS, /// !=

        LT,         /// <
        LTEQ,       /// <=
        GT,         /// >
        GTEQ,       /// >=
        LTEQGT,     /// <=>

        AND,        /// &&
        OR          /// ||
    };

    std::string getOperator(ConditionalOperator);
}
