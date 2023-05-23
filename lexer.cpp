#include "lexer.h"


Token::Token(TokenType type, std::string lexeme)
    : type(type), lexeme(std::move(lexeme)) {}


Lexer::Lexer(const std::string& source)
    : source(source), start(0), current(0), line(1) {}


bool Lexer::is_at_end() const {
    return current >= source.size();
}


char Lexer::advance() {
    return source[current++];
}


void Lexer::add_token(TokenType type) {
    add_token(type, "");
}


void Lexer::add_token(TokenType type, const std::string& text) {
    std::string lexeme = source.substr(start, current - start);
    tokens.push_back(Token(type, text.empty() ? std::move(lexeme) : text));
}


char Lexer::peek() const {
    if (is_at_end()) {
        return '\0';
    }
    return source[current];
}


char Lexer::peek_next() const {
    if (current + 1 >= source.size()) {
        return '\0';
    }
    return source[current + 1];
}


bool Lexer::match(char expected) {
    if (is_at_end() || source[current] != expected) {
        return false;
    }

    ++current;
    return true;
}


void Lexer::identifier() {
    while (std::isalnum(peek())) {
        advance();
    }

    std::string text = source.substr(start, current - start);

    std::map<std::string, TokenType> keywords = {
        {"mate", TokenType::Mate},
        {"blabber", TokenType::Blabber},
        {"fairDinkum", TokenType::FairDinkum},
        {"else", TokenType::Else},
        {"barbie", TokenType::Barbie},
        {"goodOnYa", TokenType::GoodOnYa},
        {"backToYa", TokenType::BackToYa}
    };

    if (keywords.count(text)) {
        add_token(keywords[text]);
    } else {
        add_token(TokenType::Identifier);
    }
}


void Lexer::number() {
    while (std::isdigit(peek())) {
        advance();
    }

    // decimal
    if (peek() == '.' && std::isdigit(peek_next())) {
        advance();
        while (std::isdigit(peek())) {
            advance();
        }
    }

    add_token(TokenType::Number);
}


void Lexer::scan_token() {
    char c = advance();
    switch (c) {
        case '=':
            add_token(TokenType::Equal);
            break;
        case ';':
            add_token(TokenType::SemiColon);
            break;
        case '(':
            add_token(TokenType::OpenParen);
            break;
        case ')':
            add_token(TokenType::CloseParen);
            break;
        case '{':
            add_token(TokenType::OpenBrace);
            break;
        case '}':
            add_token(TokenType::CloseBrace);
            break;
        case ',':
            add_token(TokenType::Comma);
            break;
        case '+':
            add_token(TokenType::Plus);
            break;
        case '-':
            add_token(TokenType::Minus);
            break;
        case '*':
            add_token(TokenType::Star);
            break;
        case '/':
            add_token(TokenType::Slash);
            break;
        case '<':
            add_token(TokenType::LessThan);
            break;
        case '>':
            add_token(TokenType::GreaterThan);
            break;
        case ' ':
        case '\r':
        case '\t':
            // whitespace
            break;
        case '\n':
            ++line;
            break;
        default:
            if (std::isalpha(c)) {
                identifier();
            } else if (std::isdigit(c)) {
                number();
            } else {
                std::string error_message = "Unrecognized symbol: ";
                error_message += c;
                throw std::runtime_error(error_message);
            }
    }
}


std::vector<Token> Lexer::scan_tokens() {
    while (!is_at_end()) {
        start = current;
        scan_token();
    }

    tokens.push_back(Token(TokenType::Eof, ""));
    return tokens;
}
