#pragma once

#include <Expression/expression.h>


namespace SlavaScript::lang {
    class Argument {
    private:
        std::string name;
        Expression* expression = nullptr;
        bool arrayArgument = false;
    public:
        Argument(std::string name);
        Argument(std::string name, Expression* expression);
        Argument(std::string name, bool array);
        std::string getName();
        Expression* getExpression();
        bool isArrayArgument();
        operator std::string();
    };
}
