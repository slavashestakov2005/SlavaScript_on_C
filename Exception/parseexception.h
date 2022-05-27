#ifndef PARSEEXCEPTION_H_INCLUDED
#define PARSEEXCEPTION_H_INCLUDED

#include <string>

namespace SlavaScript::exceptions{
    class ParseException : public std::exception{
    private:
        std::string text;
    public:
        explicit ParseException() : text("") {}
        explicit ParseException(std::string text) : text(text) {}
        const char* what() const noexcept{ return text.c_str(); }
        virtual ~ParseException() noexcept {}
    };
}

#endif // PARSEEXCEPTION_H_INCLUDED
