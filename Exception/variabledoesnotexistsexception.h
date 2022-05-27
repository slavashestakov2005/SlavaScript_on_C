#ifndef VARIABLEDOESNOTEXISTSEXCEPTION_H_INCLUDED
#define VARIABLEDOESNOTEXISTSEXCEPTION_H_INCLUDED

#include <string>

namespace SlavaScript::exceptions{
    class VariableDoesNotExistsException : public std::exception{
    private:
        std::string text;
    public:
        explicit VariableDoesNotExistsException (std::string text) : text(text) {}
        const char* what() const noexcept { return ("Variable " + text + " does not exists").c_str(); }
        std::string getVariable(){ return text; }
        virtual ~VariableDoesNotExistsException () noexcept {}
    };
}

#endif // VARIABLEDOESNOTEXISTSEXCEPTION_H_INCLUDED
