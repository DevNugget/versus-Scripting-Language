#include "versus.hpp"

void Lexer::advance() {
    pos++;
    if (pos < text.size()) {
        current_char = text[pos];
    } else { current_char = '\0'; }
}

Token Lexer::create_number() {
    std::string num_str;
    int dot_count = 0;

    while (current_char != '\0' && (isdigit(current_char) || current_char == '.')) {
        if (current_char == '.') {
            if (dot_count == 1) { break; }
            dot_count++;
            num_str.push_back('.');
        } else { num_str += current_char; }

        advance();
    }

    if (dot_count == 0) {
        Token token;
        token.type = Int;
        token.value = num_str;
        token.line = line_count;

        return token;
    } else {
        Token token;
        token.type = Float;
        token.value = num_str;
        token.line = line_count;

        return token;
    }
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
        } else if (isdigit(current_char)) {
            tokens.push_back(create_number());

        } else if (current_char == '+') {
            Token token;
            token.type = Plus;
            token.value = current_char;
            token.line = line_count;

            tokens.push_back(token);
            advance();
        } else if (current_char == '-') {
            Token token;
            token.type = Minus;
            token.value = current_char;
            token.line = line_count;

            tokens.push_back(token);
            advance();
        } else if (current_char == '*') {
            Token token;
            token.type = Mul;
            token.value = current_char;
            token.line = line_count;

            tokens.push_back(token);
            advance();
        } else if (current_char == '/') {
            Token token;
            token.type = Div;
            token.value = current_char;
            token.line = line_count;

            tokens.push_back(token);
            advance();
        } else if (current_char == '(') {
            Token token;
            token.type = LeftParan;
            token.value = current_char;
            token.line = line_count;

            tokens.push_back(token);
            advance();
        } else if (current_char == ')') {
            Token token;
            token.type = RightParan;
            token.value = current_char;
            token.line = line_count;

            tokens.push_back(token);
            advance();
        } else {
            advance();
        }
    }

    return tokens;
}
