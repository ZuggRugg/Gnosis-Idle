/////////////////////////////////
// Program Created By ZuggRugg //
// Date: 6/4/2025              //
/////////////////////////////////

// Goals for Today:
// rewrite to handle whitespace and subtraction, do a rewrite and passover on how it eats tokens
// then maybe think about how to either split up into different files or whatever else

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>

#define digits "0123456789"

//data types for tokens
enum Token_Type {
  NUMBER,
  PLUS,
  MINUS,
  EOF_
};

//token struct
struct token {
  Token_Type type;
  int value;
};

//function definitions
token get_token(std::string answer, std::vector<token>& t_answer, size_t& pos);
int expr(std::vector<token>& t_answer, size_t& pos, std::string answer);
bool eat(std::vector<token>& t_answer, size_t& pos, Token_Type t, std::string answer, token& current_token);
const std::string getTokenName(Token_Type t);
void advance(size_t& pos, std::string answer, char& current);
void skip_space(char& current, size_t& pos, std::string answer);
void read_all_tokens(std::vector<token>& t_answer);

// main function
int main(void) {
  while(1) {
  size_t pos = 0;

  std::string answer;
  std::vector<token> t_answer; //vector containing tokens

  std::cout << "Idle_Gnosis> ";
  getline(std::cin,answer);
  
  std::cout << "final answer = " << expr(t_answer, pos, answer) << "\n\n";

  read_all_tokens(t_answer);
  }
}


const std::string getTokenName(Token_Type t)
{
  switch (t)
    {
    case PLUS:   return "PLUS";
    case NUMBER:  return "NUMBER";
    case EOF_:    return "EOF_";
    case MINUS: return "MINUS";
    default:    return "???";
    }
}

//iterates through string and classifies each char as a simple token
token get_token(std::string answer, std::vector<token>& t_answer, size_t& pos) {

  char current = 'l';
  while(current != '\0') {
  current = answer[pos];

    //check if its + operator
    if (current == '+') { 
      t_answer.push_back({PLUS, 999});
      advance(pos, answer, current);
      return t_answer.back();
    }

    //check if its - operator
    if (current == '-') { 
      t_answer.push_back({MINUS, 999});
      advance(pos, answer, current);
      return t_answer.back();
    }

    //Check if number
    else if(isdigit(current)) { 
      int number = current - '0';  // Convert char digit to int
      t_answer.push_back({NUMBER, number});
      advance(pos, answer, current);
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


void read_all_tokens(std::vector<token>& t_answer) {
  //read tokens
  for(int i = 0; i < t_answer.size(); i++) {
    std::cout << getTokenName(t_answer[i].type) << " - " << t_answer[i].value << "\n"; 
    }
}

// pre-defined expr function to eval expressions like '3+5' or '3 - 6'
int expr(std::vector<token>& t_answer, size_t& pos, std::string answer) {
    token current_token = get_token(answer, t_answer, pos);
    int result = 0;
   
    if(!eat(t_answer, pos, NUMBER, answer, current_token)) { exit(1); }
    if(!(eat(t_answer, pos, PLUS, answer, current_token) || eat(t_answer, pos, MINUS, answer, current_token))) { exit(1); }
    if(!eat(t_answer, pos, NUMBER, answer, current_token)) { exit(1); } 

    token left = t_answer[0];
    token Op = t_answer[1];
    token right = t_answer[2];

    if(Op.type == PLUS) {
    result = left.value + right.value;
    } else { result = left.value - right.value; }

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
bool eat(std::vector<token>& t_answer, size_t& pos, Token_Type expected, std::string answer, token& current_token) {
    if (pos < t_answer.size() || current_token.type == expected) {
      current_token = get_token(answer, t_answer, pos);
      return true;
    }
    std::cout << "\nError: Expected " << getTokenName(expected) << " at position " << pos << "\n";
    std::cout << "Instead we got " << getTokenName(current_token.type);
    return false;
}



