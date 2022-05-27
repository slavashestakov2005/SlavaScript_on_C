#ifndef ARGUMENTSMISMATCHEXCEPTION_H_INCLUDED
#define ARGUMENTSMISMATCHEXCEPTION_H_INCLUDED

#include <string>

namespace SlavaScript::exceptions{
    class ArgumentsMismatchException : public std::exception{
    private:
        std::string text;
    public:
        explicit ArgumentsMismatchException(std::string text) : text(text) {}
        const char* what() const noexcept{ return text.c_str(); }
        virtual ~ArgumentsMismatchException() noexcept {}
    };
}

#endif // ARGUMENTSMISMATCHEXCEPTION_H_INCLUDED
