#include "parser.h"
#include "expr.h"


Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens) {}


Expr Parser::expression() {
    return equality();
}


Expr Parser::equality() {
    Expr expr = comparison();

    while (match({TokenType::BangEqual, TokenType::EqualEqual})) {
        Token operator_token = previous();
        Expr right = comparison();
        expr = Expr(Binary(std::move(expr), operator_token, std::move(right)));
    }

    return expr;
}


Expr Parser::comparison() {
    Expr expr = addition();


}
