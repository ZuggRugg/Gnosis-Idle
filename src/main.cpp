#include <iostream>
#include <string>
#include <vector>

#include "token.h"
#include "Parser.h"
#include "Lexer.h"

int main(void) {
  
  std::cout << "test";
  int timer = 0;    // how many times you want to repeat cycle
  size_t pos = 0;

  std::vector<token> t_answer; //vector containing tokens
  std::vector<std::string> prompts; // vector containing strings from file

  Token::read_file(prompts);
  std::cout << "\n";

  for(size_t i = 0; i < prompts.size(); i++) {
    pos = 0;
    token current_token = Lexer::get_next_token(prompts[i], t_answer, pos);
    float result = Parser::expr(t_answer, pos, prompts[i], current_token);
    std::cout << result << "\n";
  }

  // clear up vectors after use for next batch of processing
  prompts.clear();
  t_answer.clear();

}



