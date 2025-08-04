#include <iostream>
#include <string>

#include "token.h"
#include "Parser.h"
#include "Lexer.h"

namespace Parser {

  float factor(std::vector<token>& t_answer, size_t& pos, std::string answer, token& current_token) {
    //handle positive sign
    if (current_token.type == PLUS) {
      current_token = eat(t_answer, pos, PLUS, answer, current_token);
      return +factor(t_answer, pos, answer, current_token);
    }

    //handle negative sign
    if (current_token.type == MINUS) {
      current_token = eat(t_answer, pos, MINUS, answer, current_token);
      return -factor(t_answer, pos, answer, current_token);
    }

    float v = current_token.value;

    if(current_token.type == NUMBER) {
      current_token = eat(t_answer, pos, NUMBER, answer, current_token);
      return v;
    }
  
    // handles parentheses
    else if(current_token.type == LPAREN) {
      current_token = eat(t_answer, pos, LPAREN, answer, current_token);
      v = expr(t_answer, pos, answer, current_token);
      current_token = eat(t_answer, pos, RPAREN, answer, current_token);
      return v;
    }

    // if no condition satisfied then error
    else { std::cerr << "Error!"; 
      Lexer::read_all_tokens(t_answer);
      exit(1);}
  }


  token eat(std::vector<token>& t_answer, size_t& pos, Token_Type expected, std::string answer, token current_token) {
    if (current_token.type == expected) {
      current_token = Lexer::get_next_token(answer, t_answer, pos);
      return current_token;
    }
    else {
      std::cout << "\nError: Expected " << Token::getTokenName(expected) << " at position " << pos << "\n";
      std::cout << "Instead we got " << Token::getTokenName(current_token.type) << "\n";
      exit(1);
    }
  }


  float term(std::vector<token>& t_answer, size_t& pos, std::string answer, token& current_token) {
    float result = factor(t_answer, pos, answer, current_token);
 
    while(current_token.type == MULTIPLY || current_token.type == DIVIDE || current_token.type == MODULO) {
      if(current_token.type == MULTIPLY) {
	current_token = eat(t_answer, pos, MULTIPLY, answer, current_token);
	result = result * factor(t_answer, pos, answer, current_token);
      } 

      else if(current_token.type == DIVIDE) { 
	current_token = eat(t_answer, pos, DIVIDE, answer, current_token);
	result = result / factor(t_answer, pos, answer, current_token);      
      }

      else if(current_token.type == MODULO) { 
	current_token = eat(t_answer, pos, MODULO, answer, current_token);
	result = static_cast<int>(result) % (int)factor(t_answer, pos, answer, current_token);      
      }
    }
    return result;
  }


  float expr(std::vector<token>& t_answer, size_t& pos, std::string answer, token& current_token) {
    float result = term(t_answer, pos, answer, current_token);

    while(current_token.type == PLUS || current_token.type == MINUS) {
      if(current_token.type == PLUS) {
	current_token = eat(t_answer, pos, PLUS, answer, current_token);
	result = result + term(t_answer, pos, answer, current_token);
      }
      else if(current_token.type == MINUS) {
	current_token = eat(t_answer, pos, MINUS, answer, current_token);
	result = result - term(t_answer, pos, answer, current_token);
      }
    }

    return result;
  }
}
