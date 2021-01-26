#ifndef LEXEREXCEPTION_H_INCLUDED
#define LEXEREXCEPTION_H_INCLUDED

#include <string>

namespace SlavaScript{ namespace exceptions{
    class LexerException : public std::exception{
    private:
        std::string text;
    public:
        explicit LexerException(std::string text) : text(text) {}
        explicit LexerException(std::string text, int row, int col);
        const char* what() const noexcept;
        virtual ~LexerException() noexcept {}
    };
}}

#endif // LEXEREXCEPTION_H_INCLUDED
