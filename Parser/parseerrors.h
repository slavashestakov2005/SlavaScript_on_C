#pragma once

#include <vector>

#include <Parser/parseerror.h>


namespace SlavaScript::lang {
    class ParseErrors {
    private:
        std::vector<ParseError> errors;
    public:
        ParseErrors();
        void clear();
        void add(exceptions::ParseException ex, int line);
        bool hasError();
        operator std::string();
    };
}
