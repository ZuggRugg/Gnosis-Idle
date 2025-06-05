/////////////////////////////////
// Program Created By ZuggRugg //
// Date: 6/4/2025              //
/////////////////////////////////

// Goals for Today:
// Write a new method to handle multi-digit numbers and then work on multiplication and division

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>

//data types for tokens
enum Token_Type {
  NUMBER,
  PLUS,
  MINUS,
  MULTIPLY,
  DIVIDE,
  EOF_
};

//token struct
struct token {
  Token_Type type;
  int value;
};

//function definitions
token get_next_token(std::string answer, std::vector<token>& t_answer, size_t& pos);
int expr(std::vector<token>& t_answer, size_t& pos, std::string answer);
void eat(std::vector<token>& t_answer, size_t& pos, Token_Type t, std::string answer, token& current_token);
const std::string getTokenName(Token_Type t);
void advance(size_t& pos, std::string answer, char& current);
void skip_space(char& current, size_t& pos, std::string answer);
const void read_all_tokens(std::vector<token>& t_answer);


// main function
int main(void) {
  while(1) {
  size_t pos = 0;

  std::string answer;
  std::vector<token> t_answer; //vector containing tokens

  std::cout << "\nIdle_Gnosis> ";
  getline(std::cin,answer);
  if(answer == "quit") { exit(1); }
  
  std::cout << "final answer = " << expr(t_answer, pos, answer) << "\n\n";

  read_all_tokens(t_answer);
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
    default:        return "???";
    }
}

//iterates through string and classifies each char as a simple token
token get_next_token(std::string answer, std::vector<token>& t_answer, size_t& pos) {

  char current = 'l';
  while(current != '\0') {
  current = answer[pos];

  if (current == '+') { 
    t_answer.push_back({PLUS, 999});
    advance(pos, answer, current);
    return t_answer.back();
  }

  if (current == '-') { 
    t_answer.push_back({MINUS, 999});
    advance(pos, answer, current);
    return t_answer.back();
  }

  if (current == '*') { 
    t_answer.push_back({MULTIPLY, 999});
    advance(pos, answer, current);
    return t_answer.back();
  }

  if (current == '/') { 
    t_answer.push_back({DIVIDE, 999});
    advance(pos, answer, current);
    return t_answer.back();
  }

    //Check if number
    else if(isdigit(current)) { 
      int number = 0;  // Convert char digit to int
      while(isdigit(current)) {
	number = number * 10 + (current - '0'); // convert multiple digits
	advance(pos, answer, current);
      }
      t_answer.push_back({NUMBER, number});
      return t_answer.back();
    }

    //check for whitespace
    else if(isspace(current)) {
      skip_space(current, pos, answer);
      continue;
    }

    // for unknown token
    else { 
      advance(pos, answer, current);
    }    
  }

  //add eof token
  t_answer.push_back({EOF_, 999}); 
  return t_answer.back();
}


const void read_all_tokens(std::vector<token>& t_answer) {
  //read tokens
  for(int i = 0; i < t_answer.size(); i++) {
    std::cout << getTokenName(t_answer[i].type) << " - " << t_answer[i].value << "\n"; 
    }
}

// pre-defined expr function to eval expressions like '3+5' or '3 - 6'
int expr(std::vector<token>& t_answer, size_t& pos, std::string answer) {
token current_token = get_next_token(answer, t_answer, pos);
 int eval;

  // Parse first number
  int left = current_token.value;
  eat(t_answer, pos, NUMBER, answer, current_token);

  // Parse operator
  Token_Type op = current_token.type;
  if (op != PLUS && op != MINUS && op != MULTIPLY && op != DIVIDE) {
    std::cerr << "Error: Expected '+' or '-' after number\n";
    exit(1);
  }
  eat(t_answer, pos, op, answer, current_token);

  // Parse second number
  int right = current_token.value;
  eat(t_answer, pos, NUMBER, answer, current_token);

  // Evaluate expression

  switch(op) {
  case PLUS:      eval = left + right;   break;
  case MINUS:     eval = left - right;   break;
  case MULTIPLY:   eval = left * right;   break;
  case DIVIDE:    eval = left / right;   break;
}

  return eval;
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
void eat(std::vector<token>& t_answer, size_t& pos, Token_Type expected, std::string answer, token& current_token) {
    if (current_token.type == expected) {
      current_token = get_next_token(answer, t_answer, pos);
    }
    else {
    std::cout << "\nError: Expected " << getTokenName(expected) << " at position " << pos << "\n";
    std::cout << "Instead we got " << getTokenName(current_token.type) << "\n";
    exit(1);
    }
}
