#pragma once

#include <string>

#include <Parser/tokentype.h>


namespace SlavaScript::lang {
    class Token {
    private:
        TokenType type;
        std::string text;
        int row, col;
    public:
        Token();
        Token(TokenType type, std::string text, int row = 0, int col = 0);
        int getRow();
        int getCol();
        std::string position();
        void setType(TokenType type);
        TokenType getType();
        void setText(std::string text);
        std::string getText();
        operator std::string();
    };
}

std::ostream& operator<<(std::ostream& os, const SlavaScript::lang::Token& tok);
std::ostream& operator<<(std::ostream& os, SlavaScript::lang::Token* tok);
