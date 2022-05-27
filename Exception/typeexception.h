#ifndef TYPEEXCEPTION_H_INCLUDED
#define TYPEEXCEPTION_H_INCLUDED

#include <string>

namespace SlavaScript::exceptions{
    class TypeException : public std::exception{
    private:
        std::string text;
    public:
        explicit TypeException(std::string text) : text(text) {}
        const char* what() const noexcept { return text.c_str(); }
        virtual ~TypeException () noexcept {}
    };
}

#endif // TYPEEXCEPTION_H_INCLUDED
