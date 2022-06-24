#ifndef EXCEPTION_H_INCLUDED
#define EXCEPTION_H_INCLUDED

#include <string>

namespace SlavaScript::exceptions{
    class Exception : public std::exception{
    private:
        std::string text;
    public:
        Exception(std::string text = "");
        void setText(std::string text);
        std::string msg() const noexcept;
        const char* what() const noexcept override final;
        virtual ~Exception() noexcept;
    };
}

#endif // EXCEPTION_H_INCLUDED
