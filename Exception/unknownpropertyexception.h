#ifndef UNKNOWNPROPERTYEXCEPTION_H_INCLUDED
#define UNKNOWNPROPERTYEXCEPTION_H_INCLUDED

#include <string>

namespace SlavaScript::exceptions{
    class UnknownPropertyException  : public std::exception{
    private:
        std::string text;
    public:
        explicit UnknownPropertyException (std::string text) : text(text) {}
        const char* what() const noexcept { return ("Unknown property " + text).c_str(); }
        virtual ~UnknownPropertyException () noexcept {}
    };
}

#endif // UNKNOWNPROPERTYEXCEPTION_H_INCLUDED
