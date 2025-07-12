#ifndef RANDOM_EXPR_H
#define RANDOM_EXPR_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>

#define MAX_LINES 20000

void Main(); 
void generate_expr(std::vector<std::string> e);
void write_file(std::vector<std::string>& e);
char gen_op();
std::string gen_expr(int depth);


// function p_back() looks backwards at previous token
// function paren_check() would check the amount of parentheses and implement correctly
// IF NUM | RPAREN, OP
// IF OP | NUM
// IF LPAREN | paren_check() then NUM
// IF RPAREN | OP
// I could fix the length of the expression based on the amount of parentheses maybe
// (definitly not length of string)


namespace rand_func {

  // random operator
  char gen_op() {
    const char ops[] = {'+', '-', '*', '/', '%'};
    return ops[rand() % 5];
  }

  // generate simple expr '# op #'
  void generate_expr(std::vector<std::string>& e) { 
    int left, right;
    std::string s;
    char op;
    
    for(size_t i = 0; i < MAX_LINES; i++) {
      left = rand() % 10000; right = rand() % 10000;

    
      if ((op == '/' || op == '%') && right == 0) {
	right = 1;  // or continue to skip this expression
      }

      op = gen_op();
      s = std::to_string(left) + " " + op + " " + std::to_string(right);
      e.emplace_back(s + " " + gen_op() + " " + std::to_string(right));
    }
  }

  //write vector to file
  void write_file(const std::vector<std::string>& e) { 
    std::ofstream out("prompts.txt");
    for(size_t i = 0; i < MAX_LINES; i++) {
      out << e[i] << "\n";
    }
    out.close();
  }

  // run everything 
  void Main() {
    std::vector<std::string> e;
    e.reserve(MAX_LINES);

    srand(time(0));
    generate_expr(e);
    write_file(e);
  }
}

#endif
