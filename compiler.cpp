/////////////////////////////////
// Program Created By ZuggRugg //
// Date: 6/4/2025              //
/////////////////////////////////

// Goals for Today:
// start creating functions like pow()?

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include <iomanip>

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
  MODULO,
  EOF_
};

//token struct
struct token {
  Token_Type type;
  float value;
};

//function definitions
token get_next_token(std::string answer, std::vector<token>& t_answer, size_t& pos);
float expr(std::vector<token>& t_answer, size_t& pos, std::string answer, token& current_token);
token eat(std::vector<token>& t_answer, size_t& pos, Token_Type t, std::string answer, token current_token);
const std::string getTokenName(Token_Type t);
void advance(size_t& pos, std::string answer, char& current);
void skip_space(char& current, size_t& pos, std::string answer);
void read_all_tokens(std::vector<token>& t_answer);
bool isOperator(Token_Type t);
float factor(std::vector<token>& t_answer, size_t& pos, std::string answer, token& current_token);
float term(std::vector<token>& t_answer, size_t& pos, std::string answer, token& current_token);
				
// main function
int main(void) {
  while(1) {
  size_t pos = 0;

  std::string answer;
  std::vector<token> t_answer; //vector containing tokens

  std::cout << "\nIdle_Gnosis> ";
  getline(std::cin,answer);
  if(answer == "quit") { exit(1); }

  token current_token = get_next_token(answer, t_answer, pos);
  float result = expr(t_answer, pos, answer, current_token);
  std::cout << "final answer = " << result << "\n\n";

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
    case LPAREN:    return "LPAREN";
    case RPAREN:    return "RPAREN";
    case DOT:       return "DOT";
    case UNARY_POS: return "UNARY_POS";
    case UNARY_NEG: return "UNARY_NEG";
    case MODULO:    return "MODULO";
    default:        return "???";
    }
}

//iterates through string and classifies each char as a simple token
token get_next_token(std::string answer, std::vector<token>& t_answer, size_t& pos) {

  char current = '1';

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

    if (current == '%') { 
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


void read_all_tokens(std::vector<token>& t_answer) {
  //read tokens
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

  else { std::cerr << "Error!";  exit(1);}
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
