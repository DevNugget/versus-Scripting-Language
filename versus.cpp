#include "versus.hpp"

void Lexer::advance() {
    pos++;
    if (pos < text.size()) {
        current_char = text[pos];
    } else { current_char = '\0'; }
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    advance();

    while (current_char != '\0') {
        if (current_char == '\t' || current_char == ' ') {
            advance();
        } else if (current_char == '\n') {
            line_count++;
            advance();
        }
    }
}
