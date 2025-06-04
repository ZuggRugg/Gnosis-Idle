/////////////////////////////////
// Program Created By ZuggRugg //
// Date: 6/4/2025              //
/////////////////////////////////

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#define digits "0123456789"

//data types for tokens
enum Token_Type {
  NUMBER,
  PLUS,
  EOF_
};

//token struct
struct token {
  Token_Type type;
  int value;
};

//function definitions
std::string tokenize();
void get_tokens(std::string rec, std::vector<token>& t_answer);
int expr(std::vector<token>& t_answer, int& pos);
bool eat(std::vector<token>& tokens, int& pos, Token_Type t);

// main function
int main(void) {
  while(1) {
  int pos = 0;

  std::string answer;
  std::vector<token> t_answer; //vector containing tokens

  std::cout << "Idle_Gnosis> ";
  getline(std::cin,answer);
  get_tokens(answer, t_answer);
  

  std::cout << "final answer = " << expr(t_answer, pos) << "\n";
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

    if(i == rec.length()-1) { t_answer.push_back({EOF_, 999}); } // add end of file token
  }

  //read tokens
  for(int i = 0; i < t_answer.size(); i++) {
    std::cout << t_answer[i].type << " - " << t_answer[i].value << "\n";
  }
}


// pre-defined expr function to eval expressions like '3+5'
int expr(std::vector<token>& t_answer, int& pos) {
    token left = t_answer[0];
    if(!eat(t_answer, pos, NUMBER)) { exit(1); }

    token Op = t_answer[1];
    if(!eat(t_answer, pos, PLUS)) { exit(1); }

    token right = t_answer[2];
    if(!eat(t_answer, pos, NUMBER)) { exit(1); } 

    int result = left.value + right.value;
    return result;
}


bool eat(std::vector<token>& tokens, int& pos, Token_Type expected) {
    if (pos < tokens.size() && tokens[pos].type == expected) {
        pos++;
        return true;
    }
    std::cout << "\nError: Expected token type " << expected << " at position " << pos << "\n";
    return false;
}



