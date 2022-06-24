#ifndef PARSEERROR_H_INCLUDED
#define PARSEERROR_H_INCLUDED

#include "../Exception/exceptions.h"

namespace SlavaScript::lang{
    class ParseError{
    private:
        int line;
        exceptions::ParseException exception;
    public:
        ParseError(int line, exceptions::ParseException exception);
        int getLine();
        exceptions::ParseException getException();
        operator std::string();
    };
}

#endif // PARSEERROR_H_INCLUDED
