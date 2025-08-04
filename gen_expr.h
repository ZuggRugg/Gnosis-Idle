#ifndef GEN_EXPR_H
#define GEN_EXPR_H


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <fstream>

#define MAX_LINES 600000

enum class Operator {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    MODULO
};


namespace generate {

// Function to get operator symbol
std::string getOperatorSymbol(Operator op) {
    switch (op) {
        case Operator::ADD:
            return "+";
        case Operator::SUBTRACT:
            return "-";
        case Operator::MULTIPLY:
            return "*";
        case Operator::DIVIDE:
            return "/";
        case Operator::MODULO:
	  return "%";
    }
    return "";
}

// Function to generate a random number
int generateRandomNumber(int min, int max) {
    return min + (rand() % (max - min + 1));
}

// Function to generate a math expression
std::string generateMathExpression(int maxDepth) {
    if (maxDepth == 0) {
        return std::to_string(generateRandomNumber(1, 100));
    } else {

        std::string left = generateMathExpression(maxDepth - 1);
        Operator op = static_cast<Operator>(rand() % 4);
        std::string right = generateMathExpression(maxDepth - 1);

        // Randomly decide whether to add parentheses
        if (rand() % 2 == 0) {
            return "(" + left + " " + getOperatorSymbol(op) + " " + right + ")";
        } else {
            return left + " " + getOperatorSymbol(op) + " " + right;
        }
    }
}

void write_file(const std::vector<std::string>& e) { 
    std::ofstream out("prompts.txt");
    for(size_t i = 0; i < MAX_LINES; i++) {
      out << e[i] << "\n";
    }
    out.close();
  }


void gen() {
    srand(time(0)); 
    std::vector<std::string> e;
    e.reserve(MAX_LINES);

    int numExpressions = MAX_LINES;

    for (int i = 0; i < numExpressions; i++) {
        std::string expression = generateMathExpression(4);
        e.emplace_back(expression);
    }

    write_file(e);    
}

} // end of namespace


#endif
