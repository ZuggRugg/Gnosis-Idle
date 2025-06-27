#ifndef COMPILER_H
#define COMPILER_H

#include <vector>
#include <string>

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
  MODULO,
  EOF_
};

//token struct
struct token {
  Token_Type type;
  float value;
};

void compile();
token get_next_token(std::string answer, std::vector<token>& t_answer, size_t& pos);
float expr(std::vector<token>& t_answer, size_t& pos, const std::string answer, token& current_token);
token eat(std::vector<token>& t_answer, size_t& pos, Token_Type t, const std::string answer, token current_token);
const std::string getTokenName(const Token_Type t);
void advance(size_t& pos, std::string answer, char& current);
void skip_space(char& current, size_t& pos, const std::string answer);
void read_all_tokens(std::vector<token>& t_answer);
bool isOperator(const Token_Type t);
float factor(std::vector<token>& t_answer, size_t& pos, const std::string answer, token& current_token);
float term(std::vector<token>& t_answer, size_t& pos, const std::string answer, token& current_token);
void read_file(std::vector<std::string>& prompts);

#endif
