#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <vector>
#include <string>



namespace Lexer {

token get_next_token(std::string answer, std::vector<token>& t_answer, size_t& pos);
void read_all_tokens(std::vector<token>& t_answer);
void skip_space(char& current, size_t& pos, std::string answer);
void read_all_tokens(std::vector<token>& t_answer);
void advance(size_t& pos, std::string answer, char& current);

//data types for tokens
enum Token_Type {
  NUMBER,
  PLUS,
  MINUS,
  MULTIPLY,
  DIVIDE,
  DOT,
  LPAREN,
  RPAREN,
  UNARY_POS,
  UNARY_NEG,
  EOF_
};


//token struct
struct token {
  Token_Type type;
  float value;
};


}

#endif

