#ifndef PARSEERRORS_H_INCLUDED
#define PARSEERRORS_H_INCLUDED

#include <vector>
#include "parseerror.h"

namespace SlavaScript{ namespace lang{
    class ParseErrors{
    private:
        std::vector<ParseError*> errors;
    public:
        ParseErrors(){}
        void clear();
        void add(std::exception* ex, int line);
        bool hasError();
        operator std::string();
    };
}}

#endif // PARSEERRORS_H_INCLUDED
