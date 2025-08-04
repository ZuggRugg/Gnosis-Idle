#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cctype>
#include <iomanip>

#include "token.h"
#include "Lexer.h"

namespace Lexer {

  // read the entire token array
void read_all_tokens(std::vector<token>& t_answer) {
  for(size_t i = 0; i < t_answer.size(); i++) {
    std::cout << std::left << std::setw(10) << Token::getTokenName(t_answer[i].type) <<  
    std::right << std::setw(10) << t_answer[i].value << "\n"; 
    }
}


  // if current char is space then skip the char
void skip_space(char& current, size_t& pos, std::string answer) {
  while(current != '\0' && isspace(current)) {
    advance(pos, answer, current);
  }
}

  // advances the position by one and returns null if at end of string
void advance(size_t& pos, std::string answer, char& current) {
  ++pos;
  current = (pos < answer.size()) ? answer[pos] : '\0';
}



// decides which char is which token
token get_next_token(std::string answer, std::vector<token>& t_answer, size_t& pos) {

  while(1) {
    char current = answer[pos];

    if (current == '+') { 
      t_answer.push_back({PLUS, 999});
      advance(pos, answer, current);
      return t_answer.back();
    }

    else if (current == '-') { 
      t_answer.push_back({MINUS, 999});
      advance(pos, answer, current);
      return t_answer.back();
    }

    else if (current == '*') { 
      t_answer.push_back({MULTIPLY, 999});
      advance(pos, answer, current);
      return t_answer.back();
    }

    else if (current == '/') { 
      t_answer.push_back({DIVIDE, 999});
      advance(pos, answer, current);
      return t_answer.back();
    }

    else if (current == '%') { 
      t_answer.push_back({MODULO, 999});
      advance(pos, answer, current);
      return t_answer.back();
    }

    else if (current == '(') { 
      t_answer.push_back({LPAREN, 999});
      advance(pos, answer, current);
      return t_answer.back();
    }

    else if (current == ')') { 
      t_answer.push_back({RPAREN, 999});
      advance(pos, answer, current);
      return t_answer.back();
  }


    else if(isdigit(current)) { 
      float number = 0;  // Convert char digit to int
      std::string num_expr; //array of chars that gets converted to float?

      while(isdigit(current) || current == '.') {

	if(isdigit(current)) {
	num_expr += current;
	advance(pos, answer, current);
	}
	
	else if(current == '.') {
	num_expr += current;
	advance(pos, answer, current);
	}
      }

      number = std::stof(num_expr);
      t_answer.push_back({NUMBER, number});
      return t_answer.back();
    }

    //check for whitespace
    else if(isspace(current)) {
      skip_space(current, pos, answer);
      continue;
    }

    else if(current == '\0') {
      t_answer.push_back({EOF_, 999}); 
      return t_answer.back();
    }

    // for unknown token
    else { 
      std::cerr << "\nUnknown token discovered cannot parse\n";
      exit(1);
      }    
    }
  }
}








