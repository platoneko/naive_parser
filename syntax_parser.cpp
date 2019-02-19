#include "syntax_parser.h"
using namespace std;


SyntaxParser::SyntaxParser(FILE *fp, string file_name) {
    this->fp = fp;
    this->file_name = file_name;
    _init_priority_table();
}


void SyntaxParser::_init_priority_table() {
    priority_table[LB] = 0;
    priority_table[RB] = 0;
    priority_table[IDENT] = 1; 
    priority_table[INT_CONST] = 1;
    priority_table[LONG_CONST] = 1; 
    priority_table[FLOAT_CONST] = 1;
    priority_table[DOUBLE_CONST] = 1;
    priority_table[CHAR_CONST] = 1;    
    priority_table[MUL] = 4;
    priority_table[DIV] = 4;
    priority_table[MOD] = 4;
    priority_table[PLUS] = 5;
    priority_table[MINUS] = 5;
    priority_table[LT] = 7;
    priority_table[LE] = 7;
    priority_table[GT] = 7;
    priority_table[GE] = 7;
    priority_table[EQ] = 8;
    priority_table[NEQ] = 8;
    priority_table[AND] = 12;
    priority_table[OR] = 13;
    priority_table[ASSIGN] = 15;
}


ASTree *SyntaxParser::parse_syntax() {
    TokenParser token_parser = TokenParser(fp, file_name);

    ASTree *root = new ASTree();
    root->token_pair.first = PROGRAM;
    root->token_pair.second = "PROGRAM";

    root->child = _parse_program(token_parser);
    
    _indent_format(token_parser);
    return root;
}



