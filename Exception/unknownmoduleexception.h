#ifndef UNKNOWNMODULEEXCEPTION_H_INCLUDED
#define UNKNOWNMODULEEXCEPTION_H_INCLUDED

#include <string>

namespace SlavaScript{ namespace exceptions{
    class UnknownModuleException  : public std::exception{
    private:
        std::string text;
    public:
        explicit UnknownModuleException (std::string text) : text(text) {}
        const char* what() const noexcept { return ("Unknown module " + text).c_str(); }
        virtual ~UnknownModuleException () noexcept {}
    };
}}

#endif // UNKNOWNMODULEEXCEPTION_H_INCLUDED
