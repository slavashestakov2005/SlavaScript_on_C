#ifndef UNKNOWNCLASSEXCEPTION_H_INCLUDED
#define UNKNOWNCLASSEXCEPTION_H_INCLUDED

#include <string>

namespace SlavaScript::exceptions{
    class UnknownClassException : public std::exception{
    private:
        std::string text;
    public:
        explicit UnknownClassException(std::string text) : text(text) {}
        const char* what() const noexcept { return ("Unknown class " + text).c_str(); }
        virtual ~UnknownClassException () noexcept {}
    };
}

#endif // UNKNOWNCLASSEXCEPTION_H_INCLUDED
