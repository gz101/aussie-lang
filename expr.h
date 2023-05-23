#ifndef EXPR_H
#define EXPR_H

#include "token.h"
#include <memory>
#include <variant>


// forward declarations
class Binary;
class Unary;
class Literal;
class Grouping;


// use variant to represent any type of expression
using ExprBase = std::variant<Binary, Unary, Literal, Grouping>;


class Expr {
public:
    explicit Expr(ExprBase base) : base(base) {}

    ExprBase base;
};


class Binary {
public:
    Binary(Expr left, Token op, Expr right) : left(std::move(left)), op(op), right(std::move(right)) {}

    Expr left;
    Token op;
    Expr right;
};


class Unary {
public:
    Unary(Token op, Expr right) : op(op), right(std::move(right)) {}

    Token op;
    Expr right;
};


class Literal {
public:
    explicit Literal(Token value) : value(value) {}

    Token value;
};


class Grouping {
public:
    explicit Grouping(Expr expression) : expression(std::move(expression)) {}

    Expr expression;
};


#endif  // EXPR_H
