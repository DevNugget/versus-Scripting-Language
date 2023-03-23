#include <iostream>

#include "versus.hpp"

int main() {
    Lexer lexer;
    lexer.text = "1 + 1";
    std::vector<Token> tokens = lexer.tokenize();

    for (auto x : tokens) {
        std::cout << "Type: " << x.type << "; Value: " << x.value << "; Line Number: " << x.line << '\n';
    }

    return 0;
}