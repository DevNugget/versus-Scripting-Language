#ifndef VERSUS_HPP
#define VERSUS_HPP

#include <string>
#include <vector>

enum TokenType {
    Int,
    Float,
    Plus,
    Minus,
    Mul,
    Div,
    LeftParan,
    RightParan,
};

struct Token {
    TokenType type;
    std::string value;
    int line;
};

class Lexer {
    public:
    int pos = -1;
    int line_count = 1;

    char current_char;

    std::string text;

    std::vector<Token> tokenize();
    Token create_number();
    void advance();
};

#endif // VERSUS_HPP