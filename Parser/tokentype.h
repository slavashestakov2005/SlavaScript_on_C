#ifndef TOKENTYPE_H_INCLUDED
#define TOKENTYPE_H_INCLUDED

namespace SlavaScript::lang{
    enum class TokenType{
        NUMBER,
        HEX_NUMBER,
        WORD,
        TEXT,

        ///keywords
        PRINT,
        PRINTLN,
        IF,
        ELIF,
        ELSE,
        WHILE,
        FOR,
        DO,
        BREAK,
        CONTINUE,
        DEF,
        RETURN,
        IMPORT,
        AS,
        SWITCH,
        CASE,
        DEFAULT,
        TRY,
        THROW,
        CATCH,
        CLASS,
        NEW,

        PLUS,       /// +
        MINUS,      /// -
        STAR,       /// *
        SLASH,      /// /
        PERCENT,    /// %
        STARSTAR,   /// **

        PLUSEQ,     /// +=
        MINUSEQ,    /// -=
        STAREQ,     /// *=
        SLASHEQ,    /// /=
        PERCENTEQ,  /// %=
        STARSTAREQ, /// **=

        LTLT,       /// <<
        LTLTEQ,     /// <<=
        GTGT,       /// >>
        GTGTEQ,     /// >>=

        PLUSPLUS,   /// ++
        MINUSMINUS, /// --

        EQ,         /// =
        EQEQ,       /// ==
        EXCL,       /// !
        EXCLEQ,     /// !=
        LT,         /// <
        LTEQ,       /// <=
        GT,         /// >
        GTEQ,       /// >=

        BAR,        /// |
        BARBAR,     /// ||
        AMP,        /// &
        AMPAMP,     /// &&
        CARET,      /// ^
        TILDE,      /// ~

        BAREQ,      /// |=
        AMPEQ,      /// &=
        CARETEQ,    /// ^=

        QUESTION,   /// ?
        COLON,      /// :
        COMMA,      /// ,
        DOT,        /// .
        GRIDGRID,   /// ##

        LPAREN,     /// (
        RPAREN,     /// )
        LBRACE,     /// {
        RBRACE,     /// }
        LBRACKET,   /// [
        RBRACKET,   /// ]

        END_OF_FILE
    };
}

#endif // TOKENTYPE_H_INCLUDED
