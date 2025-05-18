#pragma once

#include <map>
#include <string>
#include <vector>

#include <Parser/token.h>


namespace SlavaScript::lang {
    class Lexer {
    private:
        static std::map<std::string, TokenType> OPERATORS, KEYWORDS;
        static std::string OPERATOR_CHARS;
        int pos, length, row, col, last_row, last_col;
        std::string input;
        std::vector<Token*> tokens;
        void tokenizeToken();
        void tokenizeNumber();
        void tokenizeHexNumber();
        void tokenizeOperator();
        void tokenizeWord();
        void tokenizeExtendedWord();
        void tokenizeText();
        void tokenizeComment();
        void tokenizeMultilineComment();
        void tokenizeIntegration();
        void addToken(TokenType type);
        void addToken(TokenType type, std::string text);
        char peek(int position);
        char next();
        void error(std::string s);
    public:
        Lexer(std::string input);
        std::vector<Token*> tokenize();
    };
}
