#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cctype>


token get_next_token(std::string answer, std::vector<token>& t_answer, size_t& pos);
void read_all_tokens(std::vector<token>& t_answer);
void skip_space(char& current, size_t& pos, std::string answer);
void advance(size_t& pos, std::string answer, char& current);


#endif
