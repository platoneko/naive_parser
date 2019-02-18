#ifndef __TOKEN_PARSER_H__
#define __TOKEN_PARSER_H__
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#define MAX_TOKEN 512

typedef std::pair<int, std::string> TokenPair;

class TokenParser {
private:
    std::string file_name;
    FILE *fp;
    int cur_line;
    char token_text_buffer[MAX_TOKEN];
    char *token_buffer_ptr;
    int position;
    std::vector<int> line_counter;
    std::vector<TokenPair> token_sequence;
    std::unordered_map<std::string, int> token_table;

    void _init_token_table();

    void _create_token_sequence();

    TokenPair _parse_alpha_token(char c);

    TokenPair _parse_digit_token(char c);

    TokenPair _parse_float_token(char c, int has_dot);

    TokenPair _parse_str_token(char c);

    TokenPair _parse_pre_token(char c);

    // Normally exit with current char is '/n' or '/'.
    void _parse_comment(char c);

    TokenPair _parse_less_or_includefile_token(char c);

    TokenPair _get_token();

public:
    TokenParser(FILE *fp, std::string file_name);

    TokenPair get_token();

    void unget_token();

    int get_line();

    std::string get_file_name();
};
#endif