#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <map>


enum class TokenType {
    Mate,
    Equal,
    SemiColon,
    Identifier,
    Number,
    Plus,
    Minus,
    Star,
    Slash,
    Blabber,
    OpenParen,
    CloseParen,
    OpenBrace,
    CloseBrace,
    FairDinkum,
    Else,
    LessThan,
    GreaterThan,
    Barbie,
    GoodOnYa,
    BackToYa,
    Comma,
    Eof
};


class Token {
public:
    TokenType type;
    std::string lexeme;

    Token(TokenType type, std::string lexeme);
};


class Lexer {
public:
    explicit Lexer(const std::string& source);

    std::vector<Token> scan_tokens();

private:
    const std::string& source;
    std::vector<Token> tokens;

    int start;
    int current;
    int line;

    bool is_at_end() const;
    void scan_token();
    char advance();
    bool match(char expected);
    char peek() const;
    char peek_next() const;
    void add_token(TokenType type);
    void add_token(TokenType type, const std::string& text);
    void identifier();
    void number();
};


#endif  // LEXER_H
