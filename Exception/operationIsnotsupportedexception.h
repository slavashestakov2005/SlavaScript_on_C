#ifndef OPERATIONISNOTSUPPORTEDEXCEPTION_H_INCLUDED
#define OPERATIONISNOTSUPPORTEDEXCEPTION_H_INCLUDED

#include <string>

namespace SlavaScript{ namespace exceptions{
    class OperationIsNotSupportedException  : public std::exception{
    private:
        std::string text;
    public:
        explicit OperationIsNotSupportedException (std::string text) : text(text) {}
        const char* what() const noexcept{ return ("Operation " + text + " is not supported").c_str(); }
        virtual ~OperationIsNotSupportedException () noexcept {}
    };
}}

#endif // OPERATIONISNOTSUPPORTEDEXCEPTION_H_INCLUDED
