/////////////////////////////////
// Program Created By ZuggRugg //
// Date: 6/4/2025              //
/////////////////////////////////

//TODO: start creating functions like pow(), sin(), cos(), log()
//TODO: create some seperate function to handle matrices?
//TODO: maybe add some extra layer like analysing the properties of the numbers? (Prime, factors, etc)
//TODO: generate some new expresssions every 2 seconds then quit after 10 seconds???

#include "rand_expr.h"
#include "compiler.h"

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <iomanip>
#include <fstream>

// for generating random expr and writing to the file
		
// main function 
void compile() {
  
  rand_func::Main(); // generate new prompts (20000 lines)

  std::vector<token> t_answer; //vector containing tokens

  size_t pos = 0;
  std::vector<std::string> prompts;

  read_file(prompts);
  std::cout << "\n";

  for(size_t i = 0; i < prompts.size(); i++) {
    pos = 0;
    token current_token = get_next_token(prompts[i], t_answer, pos);
    float result = expr(t_answer, pos, prompts[i], current_token);
    std::cout << i << ") " << prompts[i] << " = " << result << "\n";
    t_answer.clear();
  }

  // old cli version of main
  // while(1) {
  //   // std::string answer;
  //   // std::cout << "\nGnosis Idle> ";
  //   // getline(std::cin,answer);
  //   // if(answer == "quit") { exit(1); }
  //   token current_token = get_next_token(answer, t_answer, pos);
  //   float result = expr(t_answer, pos, answer, current_token);
  //   std::cout << "final answer = " << result << "\n\n";
  //   read_all_tokens(t_answer);
}



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

//iterates through string and classifies each char as a simple token
token get_next_token(std::string answer, std::vector<token>& t_answer, size_t& pos) {

  char current = '0';

  while(1) {
    current = answer[pos];

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

//read tokens
void read_all_tokens(std::vector<token>& t_answer) {
  for(size_t i = 0; i < t_answer.size(); i++) {
    std::cout << std::left << std::setw(10) << getTokenName(t_answer[i].type) <<  
    std::right << std::setw(10) << t_answer[i].value << "\n"; 
    }
}

// pre-defined expr function to eval expressions like '3+5' or '3 - 6'
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


//advance to the next char
void advance(size_t& pos, std::string answer, char& current) {
  ++pos;
  current = (pos < answer.size()) ? answer[pos] : '\0';
}


// skip all white spaces in input
void skip_space(char& current, size_t& pos, std::string answer) {
  while(current != '\0' && isspace(current)) {
    advance(pos, answer, current);
  }
}


// eat the current token if it matches the expected type
token eat(std::vector<token>& t_answer, size_t& pos, Token_Type expected, std::string answer, token current_token) {
    if (current_token.type == expected) {
      current_token = get_next_token(answer, t_answer, pos);
      return current_token;
    }
    else {
    std::cout << "\nError: Expected " << getTokenName(expected) << " at position " << pos << "\n";
    std::cout << "Instead we got " << getTokenName(current_token.type) << "\n";
    exit(1);
    }
}


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
    read_all_tokens(t_answer);
    exit(1);}
}

// Handles Multiplying, Division and Modulo Operators
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
