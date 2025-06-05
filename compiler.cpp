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

#define digits "0123456789"

//data types for tokens
enum Token_Type {
  NUMBER,
  PLUS,
  WHITESPACE,
  EOF_
};

//token struct
struct token {
  Token_Type type;
  int value;
};

//function definitions
void get_tokens(std::string rec, std::vector<token>& t_answer);
int expr(std::vector<token>& t_answer, size_t& pos);
bool eat(std::vector<token>& tokens, size_t& pos, Token_Type t);
const std::string getTokenName(Token_Type t);

// main function
int main(void) {
  while(1) {
  size_t pos = 0;

  std::string answer;
  std::vector<token> t_answer; //vector containing tokens

  std::cout << "Idle_Gnosis> ";
  getline(std::cin,answer);
  get_tokens(answer, t_answer);
  

  std::cout << "final answer = " << expr(t_answer, pos) << "\n\n";
  }
}


const std::string getTokenName(Token_Type t)
{
  switch (t)
    {
    case WHITESPACE: return "WHITESPACE";
    case PLUS:   return "PLUS";
    case NUMBER:  return "NUMBER";
    case EOF_:    return "EOF_";
    default:    return "???";
    }
}

//iterates through string and classifies each char as a simple token
void get_tokens(std::string rec, std::vector<token>& t_answer) {
  for (int i = 0; i < rec.length(); i++) {
    
    if (rec[i] == '+') { //check if its + operator
      t_answer.push_back({PLUS, 999});
    }

    if(isdigit(rec[i])) { 
      int number = rec[i] - '0';  // Convert char digit to int
      t_answer.push_back({NUMBER, number});
    }

    if(rec[i] == ' ') {
      t_answer.push_back({WHITESPACE, 999});
    }

    if(i == rec.length()-1) { t_answer.push_back({EOF_, 999}); } // add end of file token
  }

  //read tokens
  for(int i = 0; i < t_answer.size(); i++) {
    std::cout << getTokenName(t_answer[i].type) << " - " << t_answer[i].value << "\n"; 
  }
}


// pre-defined expr function to eval expressions like '3+5'
int expr(std::vector<token>& t_answer, size_t& pos) {
    token left = t_answer[0];
    token Op = t_answer[1];
    token right = t_answer[2];

    if(!eat(t_answer, pos, NUMBER)) { exit(1); }
    if(!eat(t_answer, pos, PLUS))   { exit(1); }
    if(!eat(t_answer, pos, NUMBER)) { exit(1); } 

    int result = left.value + right.value;
    return result;
}


// add the out_token variable
bool eat(std::vector<token>& tokens, size_t& pos, Token_Type expected) {
    if (pos < tokens.size() && tokens[pos].type == expected) {
        pos++;
        return true;
    }
    std::cout << "\nError: Expected " << getTokenName(expected) << " at position " << pos << "\n";
    return false;
}



