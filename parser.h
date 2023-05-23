#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "token.h"
#include <vector>
#include <optional>


class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);
    std::optional<Expr> parse();

private:
    std::vector<Token> tokens;
    int current = 0;

    Expr expression();
    Expr term();
    Expr factor();
    Expr unary();
    Expr number();

    Token advance();
    Token peek() const;
    Token previous() const;
    bool is_at_end() const;
    bool check(TokenType type) const;
    bool match(std::initializer_list<TokenType> types);
    Token consume(TokenType type, const std::string& message);
    void synchronize();
}


#endif  // PARSER_H
