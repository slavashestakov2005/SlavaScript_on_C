#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include "parseerrors.h"
#include "token.h"
#include "../Expression/expression.h"
#include "../Statement/foreacharraystatement.h"
#include "../Statement/foreachmapstatement.h"
#include "../Statement/functiondefinestatement.h"
#include "../Statement/statement.h"
#include <vector>

namespace SlavaScript::lang{
    class Parser{
    private:
        std::vector<Token*> tokens;
        int pos, size;
        ParseErrors parseErrors;
        int getErrorsLine();
        void recover();

        Statement* statementOrBlock();
        Statement* block();
        Statement* statement();

        Statement* ifelseStatement();
        Statement* whileStatement();
        Statement* doWhileStatement();
        Statement* forStatement();
        ForeachArrayStatement* foreachArrayStatement();
        ForeachMapStatement* foreachMapStatement();
        Statement* tryStatement();
        Statement* switchStatement();
        Statement* classDeclaration();
        Statement* integrationStatement();
        Statement* importStatement();

        Arguments functionArguments();
        Statement* functionBody();
        FunctionDefineStatement* functionDefine();
        std::vector<Expression*> functionCallArguments();
        Statement* exprStatement();

        Expression* expression();
        Expression* assignment();
        Expression* ternary();
        Expression* logicalOr();
        Expression* logicalAnd();
        Expression* bitOr();
        Expression* bitXor();
        Expression* bitAnd();
        Expression* equality();
        Expression* conditional();
        Expression* shift();
        Expression* additive();
        Expression* multiplicative();
        Expression* unary();
        Expression* exponential();
        Expression* primaryWithSuffix();
        Expression* primary();
        Expression* value();
        Expression* array();
        Expression* map();

        Expression* suffix(Expression* root);
        Token* get(int position);
        bool lookMatch(int position, TokenType type);
        bool match(TokenType type);
        Token* consume(TokenType type);
    public:
        Parser(std::vector<Token*> tokens) : tokens(tokens), pos(0) { size = tokens.size(); }
        Statement* parse();
        ParseErrors getParseErrors();
    };
}

#endif // PARSER_H_INCLUDED
