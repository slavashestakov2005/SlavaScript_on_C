#ifndef MATHEXCEPTION_H_INCLUDED
#define MATHEXCEPTION_H_INCLUDED

#include <string>

namespace SlavaScript{ namespace exceptions{
    class MathException : public std::exception{
    private:
        std::string text;
    public:
        explicit MathException(std::string text) : text(text) {}
        const char* what() const noexcept { return ("MathError : " + text).c_str(); }
        virtual ~MathException() noexcept {}
    };
}}

#endif // MATHEXCEPTION_H_INCLUDED
