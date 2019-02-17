#ifndef __SYNTAX_PARSER_H__
#define __SYNTAX_PARSER_H__
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "token_type.h"
#include "token_parser.h"
#include "var_type.h"

typedef std::unordered_map<std::string, int> VarTable;

typedef struct astree {
    TokenPair token_pair;
    struct astree *child = NULL;
    struct astree *brother = NULL;
} ASTree;


class SyntaxParser {
private:
    FILE *fp;
    std::string file_name;
    std::map<int, int> priority_table;
    std::unordered_set<std::string> defined_func_set;
    std::unordered_set<std::string> initialized_global_var_set;
    std::unordered_map<std::string, std::vector<int>> func_args_table;
    VarTable global_var_table;

    void _init_priority_table();
    
    // Normally exit with current token pair is EOF.
    // Based on recursive algorithm.
    // Return child of PROGRAM ASTree node.
    ASTree *_parse_program(TokenParser &token_parser);
    
    // Normally exit with current token pair is INCLUDE_FILE or STR_CONST.
    // Based on recursive algorithm.
    // Return child of PROGRAM ASTree node.    
    ASTree *_parse_include(TokenParser &token_parser);
    
    // Normally exit with current token pair is SEMI.
    // Based on recursive algorithm.
    // Return child of GLOBAL_VAR_DEC ASTree node.
    // Default: maybe_func_def = 0.
    ASTree *_parse_global_var_dec(TokenParser &token_parser, int type, int maybe_func_def=0);
    
    // Normally exit with current token pair is SEMI or COMMA.
    // Return child of XXX_ARRAY ASTree node.
    // We need arg 'type' to judge whether it is valid when a STR_CONST after ASSIGN.    
    ASTree *_parse_global_array_dec(TokenParser &token_parser, int type);
    
    // Normally exit with current token pair is SEMI or COMMA.
    // Return child of XXX_VAR ASTree node.
    ASTree *_parse_global_init(TokenParser &token_parser);
    
    // Normally exit with current token pair is SEMI or COMMA or RCB  
    // e.g. expression, | expression; | ..., expression}.
    // Return EXPRESSION ASTree node.
    ASTree *_check_and_parse_global_expression(TokenParser &token_parser);
    
    // Normally exit with current token pair is SEMI.
    // Based on recursive algorithm.
    // Return child of LOCAL_VAR_DEC ASTree node. 
    ASTree *_parse_local_var_dec(TokenParser &token_parser, VarTable &valid_var_table, VarTable &loc_var_table, int type);

    // Normally exit with current token pair is SEMI or COMMA.
    // Return child of XXX_ARRAY ASTree node.
    // We need arg 'type' to judge whether it is valid when a STR_CONST after ASSIGN.    
    ASTree *_parse_local_array_dec(TokenParser &token_parser, VarTable &valid_var_table, int type);

    // Normally exit with current token pair is SEMI or COMMA.
    // Return child of XXX_VAR ASTree node.
    ASTree *_parse_local_init(TokenParser &token_parser, VarTable &valid_var_table);

    // If end_with_rb = 0, normally exit with current token pair is SEMI e.g. expression;
    // or COMMA e.g. expression, ...} | int a = expression, ...
    // or RCB e.g. ... expression}.
    // If set end_with_rb = 1, then it is valid to exit with current token pair is RB e.g. if|while (expression) | for(...;...;expression).
    // Default: end_with_rb = 0, maybe_ref_void_func = 0.
    ASTree *_check_and_parse_local_expression(TokenParser &token_parser, VarTable &valid_var_table, int end_with_rb=0, int maybe_ref_void_func=0);
    
    // Normally exit with current token pair is RB.
    // Return FUNC_REF ASTree node.
    ASTree *_parse_func_ref(TokenParser &token_parser, VarTable &valid_var_table, const std::string &name, int type);
    
    // Normally exit with current token pair is RSB.
    // Return ARRAY_ELEM ASTree node.
    ASTree *_parse_array_elem(TokenParser &token_parser, VarTable &valid_var_table, const std::string &name, int type);
    
    // Normally exit with current token pair is RCB.
    // Return CODE_BLOCK ASTree node.
    // Complain: Can we use const VatTable& for ext_var_table? iter = VarTableObj.begin() not viable when it is const.
    ASTree *_create_func_codeblock(TokenParser &token_parser, VarTable &ext_var_table, VarTable &loc_var_table, int void_return);
    
    // Normally exit with current token pair is RCB.
    // Return CODE_BLOCK ASTree node.
    ASTree *_create_codeblock(TokenParser &token_parser, VarTable &ext_var_table, int maybe_conti_break, int void_return);

    // Normally exit with current token pair is RCB.
    // Based on recursive algorithm.
    // Return child of CODE_BLOCK ASTree node.
    ASTree *_parse_codeblock(TokenParser &token_parser, VarTable &valid_var_table, VarTable &loc_var_table, int maybe_conti_break, int void_return);
    
    // Normally exit with current token pair is SEMI or RCB.
    // Based on recursive algorithm.
    // Return child of BRANCH ASTree node.
    ASTree *_parse_branch(TokenParser &token_parser, VarTable &valid_var_table, VarTable &loc_var_table, int maybe_conti_break, int void_return);

    // Normally exit with current token pair is SEMI or RCB.
    // Return FOR ASTree node.
    ASTree *_parse_for(TokenParser &token_parser, VarTable &valid_var_table, VarTable &loc_var_table, int void_return);

    // Normally exit with current token pair is SEMI or RCB.
    // Return WHILE ASTree node.    
    ASTree *_parse_while(TokenParser &token_parser, VarTable &valid_var_table, VarTable &loc_var_table, int void_return);

    // Normally exit with token pair is SEMI or RCB.
    // Return child of CONTIDITION or ELSE ASTree node.
    ASTree *_parse_code_after_condition(TokenParser &token_parser, VarTable &valid_var_table, VarTable &loc_var_table, int maybe_conti_break, int void_return);

    // Normally exit with current token pair is COMMA or SEMI or RCB.
    // Return child of XXX_FUNC ASTree node.
    // Default: maybe_func_def = 0.
    ASTree *_parse_func_dec(TokenParser &token_parser, const std::string &name, int type, int maybe_func_def=0);

    // Normally exit with current token pair is RSB. 
    void _check_init_subscript(TokenParser &token_parser);
    
    // Normally exit with current token pair is RSB.
    // Return borther of XXX_ARRAY ASTree node.
    ASTree *_check_and_parse_elem_subscript(TokenParser &token_parser, VarTable &valid_var_table);

    // Normally exit with current token pair is RB.
    // Return child of FUNC_ARGS ASTree node.
    ASTree *_check_and_parse_func_args(TokenParser &token_parser, VarTable &valid_var_table, const std::string &name);
    
    // After check, call this method to build a expression tree.
    // Return child of EXPRESSION ASTree node.
    ASTree *_parse_expression(std::vector<std::pair<int, ASTree *>> *token_vec);
public:
    SyntaxParser(FILE *fp, std::string file_name);
    
    // Normally exit with current token pair is EOF.
    // Return PROGRAM ASTree (root)node.
    ASTree *parse_syntax();
};

#endif