#ifndef AST_H
#define AST_H

#include <iostream>


struct Node {
  char op;
  Node* left;
  Node* right;
};


class AST  {
private:
  Node root;

public:
  AST();
};


#endif 
