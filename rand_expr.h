#ifndef RANDOM_EXPR_H
#define RANDOM_EXPR_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>

#define MAX_LINES 10000

void Main(); 
void generate_expr(std::vector<std::string> e);
void write_file(std::vector<std::string>& e);
char gen_op();

//TODO: use this file to generate random math expressions and then write the strings to prompts.


namespace rand_func {


  // random operator
  char gen_op() {
    int f = rand() % 5;
    char op;

    if(f == 0) { op = '+';}
    else if(f == 1) { op = '-';}
    else if(f == 2) { op = '*';}
    else if(f == 3) { op = '/';}
    else if(f == 4) { op = '%';}

    return op;
  }


  //generate simple expr '# op #'
  void generate_expr(std::vector<std::string>& e) { 
    int left, right;
    std::string s;
    char op;
    
    for(size_t i = 0; i < MAX_LINES; i++) {
      left = rand(); right = rand();

    
      if ((op == '/' || op == '%') && right == 0) {
	right = 1;  // or continue to skip this expression
      }

      op = gen_op();
      e.emplace_back(std::to_string(left) + op + std::to_string(right));
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
