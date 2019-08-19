#include <iostream>
#include <cctype>
#include <cstring>

#include "token_parser.h"
#include "token_type.h"

using namespace std;

void TokenParser::_init_token_table() {
    token_table["int"] = INT;
    token_table["long"] = LONG;
    token_table["float"] = FLOAT;
    token_table["double"] = DOUBLE;
    token_table["char"] = CHAR;
    token_table["void"] = VOID;
    token_table["if"] = IF;
    token_table["else"] = ELSE;
    token_table["for"] = FOR;
    token_table["do"] = DO;
    token_table["while"] = WHILE;
    token_table["break"] = BREAK;
    token_table["continue"] = CONTINUE;
    token_table["return"] = RETURN;
}

TokenParser::TokenParser(FILE *fp, string file_name) {
    this->fp = fp;
    this->file_name = file_name;
    cur_line = 1;
    position = -1;
    _init_token_table();
    _create_token_sequence();
}


void TokenParser::_create_token_sequence() {
    TokenPair token_pair;

    while ((token_pair = _get_token()).first != EOF) {
        if (token_pair.first == ERROR_TOKEN) {
            cerr << "Invalid token '" << token_pair.second <<  "' in line " << cur_line;
            cerr << " in " << file_name << "." << endl;
            cerr << "Parse interrupted." << endl;
            exit(-1);
        }
        token_sequence.push_back(token_pair);
        line_counter.push_back(cur_line);
    }

    token_sequence.push_back(token_pair);
}


TokenPair TokenParser::_get_token() {
    char c;
    token_buffer_ptr = token_text_buffer;

    while ((c = fgetc(fp)) == ' ' || c == '\t' || c == '\n')
        if (c == '\n') ++cur_line;
    
    if (isalpha(c) || c == '_') {
        return _parse_alpha_token(c);
    }

    if (isdigit(c)) {
        return _parse_digit_token(c);
    }

    *(token_buffer_ptr++) = c;

    switch (c)
    {   
        case '(': return TokenPair (LB, "(");
        case ')': return TokenPair (RB, ")");
        case '[': return TokenPair (LSB, "[");
        case ']': return TokenPair (RSB, "]");
        case '{': return TokenPair (LCB, "{");
        case '}': return TokenPair (RCB, "}");
        case ',': return TokenPair (COMMA, ",");
        case ';': return TokenPair (SEMI, ";");
        case '|':
            if ((c = fgetc(fp)) == '|') return TokenPair (OR, "||");
            else {
                *(token_buffer_ptr++) = c;
                *token_buffer_ptr = '\0';
                return TokenPair (ERROR_TOKEN, string(token_text_buffer));
            }
        case '&':
            if ((c = fgetc(fp)) == '&') return TokenPair (AND, "&&");
            *(token_buffer_ptr++) = c;
            *token_buffer_ptr = '\0';
            return TokenPair (ERROR_TOKEN, string(token_text_buffer));
        case '>':
            if ((c = fgetc(fp)) == '=') return TokenPair (GE, ">=");
            ungetc(c, fp);
            return TokenPair (GT, ">");
        case '<': return _parse_less_or_includefile_token(c);
        case '=':
            if ((c = fgetc(fp)) == '=') return TokenPair (EQ, "==");
            ungetc(c, fp);
            return TokenPair (ASSIGN, "=");
        case '!':
            if ((c = fgetc(fp)) == '=') return TokenPair (NEQ, "!=");
            ungetc(c, fp);
            return TokenPair (ERROR_TOKEN, "!");
        case '+': return TokenPair (PLUS, "+");
        case '-': return TokenPair (MINUS, "-");
        case '*': return TokenPair (MUL, "*");
        case '/':
            if ((c = fgetc(fp)) == '/' || c == '*') {
                _parse_comment(c);
                return _get_token();
            } else {
                ungetc(c, fp);
                return TokenPair (DIV, "/");
            }
        case '%': return TokenPair (MOD, "\%");
        case '.': return _parse_float_token(c, 1);
        case '\'':
            if ((*(token_buffer_ptr++) = fgetc(fp)) == '\\')
                *(token_buffer_ptr++) = fgetc(fp);
            if ((*(token_buffer_ptr++) = fgetc(fp)) == '\'')
                return TokenPair (CHAR_CONST, string(token_text_buffer));
            return TokenPair (ERROR_TOKEN, string(token_text_buffer));
        case '"': return _parse_str_token(c);
        case '#': return _parse_pre_token(c);
        default:
            if (feof(fp)) return TokenPair (EOF, "EOF");
            while ((c = fgetc(fp)) != ' ' && c != '\t' && c != '\n')
                *(token_buffer_ptr++) = c;
            *token_buffer_ptr = '\0';
            ungetc(c, fp);
            return TokenPair (ERROR_TOKEN, string(token_text_buffer));            
    }
}


TokenPair TokenParser::_parse_alpha_token(char c) {
    string token_text;
    do {
        *(token_buffer_ptr++) = c;
    } while (isalpha(c = fgetc(fp)) || isdigit(c) || c == '_');
    ungetc(c, fp);
    *token_buffer_ptr = '\0';
    token_text = string(token_text_buffer);
    if (token_table[token_text])
        return TokenPair (token_table[token_text], token_text);
    else
        return TokenPair (IDENT, token_text);
}


TokenPair TokenParser::_parse_digit_token(char c) {
    int is_int = 0, token_type = INT_CONST;
    do {
        *(token_buffer_ptr++) = c;
        if (isdigit(c)){
            continue;
        } else if (c == '.' || c == 'e' || c == 'E') {
            if (!is_int) return _parse_float_token(c, c == '.');
            token_type = ERROR_TOKEN;
            break;            
        } else if (c == 'x' || c == 'X') {
            if ((token_buffer_ptr - token_text_buffer) == 2 && token_text_buffer[0] == '0') {
                is_int = 1;
            } else {
                token_type = ERROR_TOKEN;
                break; 
            }
        } else if (c == 'L') {
            if (isdigit(c = fgetc(fp)) || isalpha(c) || c == '.') {
                token_type = ERROR_TOKEN;
            } else {
                token_type = LONG_CONST;
            }
            ungetc(c, fp);
            break;
        } else {
            token_type = ERROR_TOKEN;
            break;
        }
    } while (isdigit(c = fgetc(fp)) || isalpha(c) || c == '.');

    if (token_type == ERROR_TOKEN) {
        while (isdigit(c = fgetc(fp)) || isalpha(c) || c == '.' || c == '_')
            *(token_buffer_ptr++) = c;  
    } else {
        if (token_text_buffer[0] == '0' && token_text_buffer[1] == '0')
            token_type = ERROR_TOKEN;
    }

    *token_buffer_ptr = '\0';
    ungetc(c, fp);
    return TokenPair (token_type, string(token_text_buffer));
}


TokenPair TokenParser::_parse_float_token(char c, int has_dot) {
    int token_type = FLOAT_CONST;
    while (isdigit(c = fgetc(fp)) || isalpha(c) || c == '.') {
        *(token_buffer_ptr++) = c;

        if (isdigit(c)) {
            continue;
        } else if (c == 'e' || c == 'E') {
            if (!has_dot) {
                token_type = ERROR_TOKEN;
                break;
            }
        } else if (c == '.') {
            token_type = ERROR_TOKEN;
            break;
        } else if (c == 'L') {
            if (isdigit(c = fgetc(fp)) || isalpha(c) || c == '.') {
                token_type = ERROR_TOKEN;
            } else {
                token_type = DOUBLE_CONST;
            }
            ungetc(c, fp);
            break;
        } else {
            token_type = ERROR_TOKEN;
            break;
        }
    }

    if (token_type == ERROR_TOKEN) {
        while (isdigit(c = fgetc(fp)) || isalpha(c) || c == '.')
            *(token_buffer_ptr++) = c;  
    }

    *token_buffer_ptr = '\0';
    ungetc(c, fp);
    return TokenPair (token_type, string(token_text_buffer));
}


TokenPair TokenParser::_parse_str_token(char c) {
    int token_type = STR_CONST;
    while ((c = fgetc(fp)) != '"') {
        if (c == '\n' || feof(fp)) {
            token_type = ERROR_TOKEN;
            break;
        }
        *(token_buffer_ptr++) = c;
    }
    if (c == '"')
        *(token_buffer_ptr++) = c;
    else
        ungetc(c, fp);
    *token_buffer_ptr = '\0';       
        
    return TokenPair (token_type, string(token_text_buffer));
}


TokenPair TokenParser::_parse_pre_token(char c) {
    while (isalpha(c = fgetc(fp))) {
            *(token_buffer_ptr++) = c;  
    }
    ungetc(c, fp);
    *token_buffer_ptr = '\0';

    if (strcmp(token_text_buffer, "#include") == 0)
        return TokenPair (INCLUDE, string(token_text_buffer));
    else if (strcmp(token_text_buffer, "#define") == 0)
        return TokenPair (DEFINE, string(token_text_buffer));
    else
        return TokenPair (ERROR_TOKEN, string(token_text_buffer));
}


TokenPair TokenParser::_parse_less_or_includefile_token(char c) {
    int i;

    if ((c = fgetc(fp)) == '=') return TokenPair (LE, "<=");
    else if (isalpha(c) || c == '_') {
        do {
            *(token_buffer_ptr++) = c;  
        } while (isalpha(c = fgetc(fp)) || c == '_' || isdigit(c) || c == '.');
        *(token_buffer_ptr++) = c;  
        *token_buffer_ptr = '\0';
        if (c == '>') {  
            return TokenPair (INCLUDE_FILE, string(token_text_buffer));
        } else {
            for (i = token_buffer_ptr - token_text_buffer - 1; i > 0; --i)
                ungetc(token_text_buffer[i], fp);
            return TokenPair (LT, "<");            
        }
    }
    else return TokenPair (LT, "<");
}


void TokenParser::_parse_comment(char c) {
    // current char is '/' or '*'
    if (c == '/') {
        while ((c = fgetc(fp)) != '\n' && c != EOF);
        if (c == '\n') ++cur_line;
    } else {
        int comment_line = cur_line;
        while ((c = fgetc(fp)) != EOF) {
            if (c == '\n') {
                ++cur_line;
            } else if (c == '*') {
                if ((c = fgetc(fp)) == '/') {
                    return;
                } else if (c == '\n') {
                    ++cur_line;
                } else if (c == EOF) {
                    cerr << "Unterminated /* comment in line " << comment_line;
                    cerr << " in " << file_name << "." << endl;
                    cerr << "Parse interrupted." << endl;
                    exit(-1);
                }
            }
        }
        cerr << "Unterminated /* comment in line " << comment_line;
        cerr << " in " << file_name << "." << endl;
        cerr << "Parse interrupted." << endl;
        exit(-1);
    }
}