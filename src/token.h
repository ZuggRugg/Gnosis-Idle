#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

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

namespace Token {
  const std::string getTokenName(Token_Type t);
  void read_file(std::vector<std::string>& prompts);
  bool isOperator(Token_Type t);
}


#endif
