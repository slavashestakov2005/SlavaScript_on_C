#ifndef PARSEERROR_H_INCLUDED
#define PARSEERROR_H_INCLUDED

#include <exception>
#include <string>

namespace SlavaScript::lang{
    class ParseError{
    private:
        int line;
        std::exception* exception;
    public:
        ParseError(int line, std::exception* exception) : line(line), exception(exception) {}
        int getLine();
        std::exception* getException();
        operator std::string();
    };
}

#endif // PARSEERROR_H_INCLUDED
