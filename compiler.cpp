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

// main function
int main(void) {
  std::string answer;
  std::vector<token> t_answer; //vector containing tokens

  std::cout << "please input an expression to be evaluated: ";
  getline(std::cin,answer);
  get_tokens(answer, t_answer);

}

//note to ignore this function for now
//simple tokenizer that breaks up sstream into individual tokens
std::string tokenize(std::string rec) {
  Token_Type type;
  std::string s;

  switch(type) {
  case NUMBER:    s += "NUMBER";    break;
  case PLUS:      s += "PLUS";      break;
  case EOF_:      s += "EOF";       break;
  }

  return s;
}


//iterates through string and classifies each char as a simple token
void get_tokens(std::string rec, std::vector<token>& t_answer) {
  for (int i = 0; i < rec.length(); i++) {
    
    if (rec[i] == '+') { //check if its + operator
      t_answer.push_back({PLUS, 000});
    }

    if(isdigit(rec[i])) { 
      int number = rec[i] - '0';  // Convert char digit to int
      t_answer.push_back({NUMBER, number});
    }

    if(i == rec.length()-1) { t_answer.push_back({EOF_, 000}); } // add end of file token
  }
  
  //read tokens
  for(int i = 0; i < t_answer.size(); i++) {
    std::cout << t_answer[i].type << " - " << t_answer[i].value << "\n";
  }
}


