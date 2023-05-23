#include "lexer.h"
#include <cassert>
#include <vector>
#include <iostream>


void test_empty_string() {
    Lexer lexer("");
    std::vector<Token> tokens = lexer.scan_tokens();
    assert(tokens.size() == 1);
    assert(tokens[0].type == TokenType::Eof);
}


void test_simple_identifiers() {
    Lexer lexer("mate blabber");
    std::vector<Token> tokens = lexer.scan_tokens();

    assert(tokens.size() == 3); // includes EOF
    assert(tokens[0].type == TokenType::Mate);
    assert(tokens[1].type == TokenType::Blabber);
    assert(tokens[2].type == TokenType::Eof);
}


int main() {
    test_empty_string();
    test_simple_identifiers();

    std::cout << "All lexer tests passed!\n";
    return 0;
}
