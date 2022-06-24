#ifndef EXCEPTIONS_H_INCLUDED
#define EXCEPTIONS_H_INCLUDED

#include "exception.h"
#include <memory>

namespace SlavaScript::lang{
    class Value;
    enum class Values;
}

namespace SlavaScript::exceptions{
    class ArgumentsMismatchException : public Exception{
    public:
        explicit ArgumentsMismatchException(int expected, int got);
        explicit ArgumentsMismatchException(std::string expected, int got);
    };


    class CastException : public Exception{
    public:
        explicit CastException(std::string tp1, std::string tp2);
        explicit CastException(lang::Values tp1, lang::Values tp2);
    };


    class LexerException : public Exception{
    public:
        explicit LexerException(std::string text);
        explicit LexerException(std::string text, int row, int col);
    };

    class LogicException : public Exception{
    public:
        explicit LogicException(std::string text);
    };

    class MathException : public Exception{
    public:
        explicit MathException(std::string text);
    };


    class ParseException : public Exception{
    public:
        explicit ParseException(std::string text = "");
    };


    class TypeException : public Exception{
    public:
        explicit TypeException(std::string info);
        explicit TypeException(std::string tp1, std::string tp2);
        explicit TypeException(std::string tp1, std::string tp2, std::string info);
    };


    class UnknownClassException : public Exception{
    public:
        explicit UnknownClassException(std::string text);
    };


    class UnknownFunctionException : public Exception{
    public:
        explicit UnknownFunctionException(std::string text);
    };


    class UnknownModuleException : public Exception{
    public:
        explicit UnknownModuleException (std::string text);
    };


    class UnknownOperationException : public Exception{
    public:
        explicit UnknownOperationException(std::string op, std::shared_ptr<lang::Value> left = nullptr, std::shared_ptr<lang::Value> right = nullptr);
        explicit UnknownOperationException(std::string op, const lang::Value* left = nullptr, const lang::Value* right = nullptr);
    };


    class UnknownPropertyException : public Exception{
    public:
        explicit UnknownPropertyException(std::string text);
    };


    class UnknownVariableException : public Exception{
    public:
        explicit UnknownVariableException(std::string text);
    };

}

#endif // EXCEPTIONS_H_INCLUDED
