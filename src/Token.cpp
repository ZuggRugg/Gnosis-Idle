#include <iostream>
#include <string>
#include <vector>
#include "token.h"

namespace Token {

  const std::string getTokenName(Token_Type t)
  {
    switch (t)
      {
      case PLUS:      return "PLUS";
      case NUMBER:    return "NUMBER";
      case EOF_:      return "EOF_";
      case MINUS:     return "MINUS";
      case MULTIPLY:  return "MULTIPLY";
      case DIVIDE:    return "DIVIDE";
      case LPAREN:    return "LPAREN";
      case RPAREN:    return "RPAREN";
      case DOT:       return "DOT";
      case MODULO:    return "MODULO";
      default:        return "???";
      }
  }

  // read file and put everything into an array of strings
  void read_file(std::vector<std::string>& prompts) {
    std::string line;
    std::ifstream fin("prompts.txt");

    if(fin.is_open()) {
      while(getline(fin, line)) {
	prompts.push_back(line);
      }
      fin.close();
    }
  }


  bool isOperator(Token_Type t) {
    switch(t) {
    case PLUS:
    case MINUS:
    case MULTIPLY:
    case DIVIDE:
    case MODULO:
      return true;  break;
    default:  return false; break;
    }
  }
}
