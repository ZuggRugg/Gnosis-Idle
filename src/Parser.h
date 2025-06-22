#ifndef PARSER_H
#define PARSER_H

#include <iostream>

float expr(std::vector<token>& t_answer, size_t& pos, std::string answer, token& current_token);
token eat(std::vector<token>& t_answer, size_t& pos, Token_Type t, std::string answer, token current_token);
float factor(std::vector<token>& t_answer, size_t& pos, std::string answer, token& current_token);
float term(std::vector<token>& t_answer, size_t& pos, std::string answer, token& current_token);





#endif

