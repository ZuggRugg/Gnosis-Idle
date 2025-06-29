#ifndef EX_PARSE_TREE_H
#define EX_PARSE_TREE_H

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class parsetree_main {
 private:
  string root_key;
  parsetree_main *node_left;
  parsetree_main *node_right;

 public:
  parsetree_main(string obj_root) {
    this->root_key = obj_root;
    this->node_left = NULL;
    this->node_right = NULL;
  }

  void insertNode_left(string insert_newnode) {
    if (this->node_left == NULL) {
      this->node_left = new parsetree_main(insert_newnode);
    } else {
      parsetree_main *t = new parsetree_main(insert_newnode);
      t->node_left = this->node_left;
      this->node_left = t;
    }
  }

  void insertNode_right(string insert_newnode) {
    if (this->node_right == NULL) {
      this->node_right = new parsetree_main(insert_newnode);
    } else {
      parsetree_main *active_parsetree = new parsetree_main(insert_newnode);
      active_parsetree->node_right = this->node_right;
      this->node_right = active_parsetree;
    }
  }

  parsetree_main *getchild_rightside() { return this->node_right; }

  parsetree_main *getchield_leftside() { return this->node_left; }

  void set_rootvalue(string obj_rootvalue) { this->root_key = obj_rootvalue; }

  string get_rootvalue() { return this->root_key; }
};

parsetree_main *build_newparsetree(string obj_parse) {
  string var_buffer;
  stringstream ss(obj_parse);
  vector<string> vector_list;
  while (ss >> var_buffer) {
    vector_list.push_back(var_buffer);
  }
  stack<parsetree_main *> parsetree_stack;
  parsetree_main *pri_parsetree = new parsetree_main("");
  parsetree_stack.push(pri_parsetree);
  parsetree_main *active_parsetree = pri_parsetree;

  string parsetreearray_1[] = {"+", "-", "*", "/"};
  vector<string> parse_vector_1(
      parsetreearray_1, parsetreearray_1 + (sizeof(parsetreearray_1) /
                                            sizeof(parsetreearray_1[0])));

  string parsetreearray_2[] = {"+", "-", "*", "/", ")"};
  vector<string> parse_vector_2(
      parsetreearray_2, parsetreearray_2 + (sizeof(parsetreearray_2) /
                                            sizeof(parsetreearray_2[0])));

  for (unsigned int i = 0; i < vector_list.size(); i++) {
    if (vector_list[i] == "(") {
      active_parsetree->insertNode_left("");
      parsetree_stack.push(active_parsetree);
      active_parsetree = active_parsetree->getchield_leftside();
    }

    else if (find(parse_vector_1.begin(), parse_vector_1.end(),
                  vector_list[i]) != parse_vector_1.end()) {
      active_parsetree->set_rootvalue(vector_list[i]);
      active_parsetree->insertNode_right("");
      parsetree_stack.push(active_parsetree);
      active_parsetree = active_parsetree->getchild_rightside();
    }

    else if (vector_list[i] == ")") {
      active_parsetree = parsetree_stack.top();
      parsetree_stack.pop();
    }

    else if (find(parse_vector_2.begin(), parse_vector_2.end(),
                  vector_list[i]) == parse_vector_2.end()) {
      try {
        active_parsetree->set_rootvalue(vector_list[i]);
        parsetree_main *node_parent = parsetree_stack.top();
        parsetree_stack.pop();
        active_parsetree = node_parent;
      }

      catch (string error_value) {
        cerr << "Token:  " << vector_list[i]
             << " Error: It's not a valid integer!" << endl;
      }
    }
  }
  return pri_parsetree;
}

void postorder(parsetree_main *createInst_parseTree) {
  if (createInst_parseTree != NULL) {
    postorder(createInst_parseTree->getchield_leftside());
    postorder(createInst_parseTree->getchild_rightside());
    cout << createInst_parseTree->get_rootvalue() << endl;
  }
}

int example() {
  parsetree_main *main_parsetree = build_newparsetree("( ( 10 + 5 ) * 3 )");
  postorder(main_parsetree);

  return 0;
}


#endif
