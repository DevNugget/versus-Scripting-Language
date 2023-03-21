#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

enum TokenType {
  Int,
  Float,
  String,
  Plus,
  Minus,
  Identifier,
  Keyword,
  LParan,
  RParan,
  TokenDef,
};

struct Token {
  enum TokenType type;
  char value;
  int line; // Used for error reporting
};

void tokens_append(struct Token *tokens, int *token_count, struct Token token) {
  // Increase the size of the tokens array by one
  (*token_count)++;
  tokens = realloc(tokens, (*token_count) * sizeof(struct Token));
  
  tokens[(*token_count) - 1] = token;
}

void advance(int *pos, char *current_char, char *text) {
  (*pos)++;

  if (*pos < strlen(text)) {
    *current_char = text[*pos];
  } else *current_char = '\0'; // If end of text
}

struct Token* lex(char* text) {
  int pos = -1;
  int token_count = 0;
  int line_count = 1;
  
  char current_char;

  advance(&pos, &current_char, text);

  struct Token* tokens;
  tokens = malloc(sizeof(struct Token)*token_count);

  // Definition token:
  // Holds number of tokens (inclusive)
  // Always at the first index of tokens
  struct Token def_token;
  enum TokenType def_type = TokenDef;
  def_token.type = def_type;
  tokens_append(tokens, &token_count, def_token);
  advance(&pos, &current_char, text);
  
  while (current_char != '\0') {
    if (current_char == '\t' || current_char == ' ') {
      advance(&pos, &current_char, text);
    } else if (current_char == '\n') {
      line_count++;
      advance(&pos, &current_char, text);
      
    } else if (current_char == '+') {
      struct Token add_token;
      enum TokenType token_type = Plus;
      
      add_token.type = token_type;
      add_token.value = current_char;
      add_token.line = line_count;
      
      tokens_append(tokens, &token_count, add_token);
      advance(&pos, &current_char, text);
    } else if (current_char == '-') {
      struct Token min_token;
      enum TokenType token_type = Minus;
      
      min_token.type = token_type;
      min_token.value = current_char;
      min_token.line = line_count;
      
      tokens_append(tokens, &token_count, min_token);
      advance(&pos, &current_char, text);
    } else {
      advance(&pos, &current_char, text);
    }
  }

  tokens[0].line = token_count;

  return tokens;
}

int main() {
  char* input = "1 + 1\n1 - 1";
  struct Token* tokens = lex(input);
  for (int i = 0; i < tokens[0].line; i++) {
    printf("Token %d: type = %d, value = %c, line = %d\n", 
      i+1, tokens[i].type, tokens[i].value, tokens[i].line);
  }
}