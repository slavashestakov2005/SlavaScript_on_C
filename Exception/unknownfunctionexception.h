#ifndef UNKNOWNFUNCTIONEXCEPTION_H_INCLUDED
#define UNKNOWNFUNCTIONEXCEPTION_H_INCLUDED

#include <string>

namespace SlavaScript::exceptions{
    class UnknownFunctionException  : public std::exception{
    private:
        std::string text;
    public:
        explicit UnknownFunctionException (std::string text) : text(text) {}
        const char* what() const noexcept { return ("Unknown function " + text).c_str(); }
        virtual ~UnknownFunctionException () noexcept {}
    };
}

#endif // UNKNOWNFUNCTIONEXCEPTION_H_INCLUDED
