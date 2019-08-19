#include "syntax_parser.h"
using namespace std;


ASTree *SyntaxParser::_create_func_codeblock(TokenParser &token_parser, VarTable &ext_var_table, VarTable &loc_var_table, int void_return) {
    // current token pair is LCB
    ASTree *root = new ASTree();
    unordered_map<string, int> valid_var_table;
    unordered_map<string, int>::iterator iter;
    for (iter = ext_var_table.begin(); iter != ext_var_table.end(); ++iter) {
        valid_var_table[iter->first] = iter->second;
    }
    for (iter = loc_var_table.begin(); iter != loc_var_table.end(); ++iter) {
        valid_var_table[iter->first] = iter->second;
    }

    root->token_pair.first = CODE_BLOCK;
    root->token_pair.second = "CODE BLOCK";
    root->child = _parse_codeblock(token_parser, valid_var_table, loc_var_table, 0, void_return);
    return root;
}


ASTree *SyntaxParser::_create_codeblock(TokenParser &token_parser, VarTable &ext_var_table, int maybe_conti_break, int void_return) {
    // current token pair is LCB
    ASTree *root = new ASTree();
    VarTable loc_var_table;
    VarTable valid_var_table = ext_var_table;

    root->token_pair.first = CODE_BLOCK;
    root->token_pair.second = "CODE BLOCK";
    root->child = _parse_codeblock(token_parser, valid_var_table, loc_var_table, maybe_conti_break, void_return);
    return root;
}


ASTree *SyntaxParser::_parse_codeblock(TokenParser &token_parser, VarTable &valid_var_table, VarTable &loc_var_table, int maybe_conti_break, int void_return) {
    ASTree *root;
    TokenPair token_pair;
    
    while ((token_pair = token_parser.get_token()).first == SEMI);
    
    if (token_pair.first == CONTINUE || token_pair.first == BREAK) {
        if (maybe_conti_break) {
            root = new ASTree();
            root->token_pair.first = token_pair.first;
            root->token_pair.second = TOKEN_TYPE[token_pair.first];
            token_pair = token_parser.get_token();
            if (token_pair.first != SEMI) {
                cerr << "Invalid syntax in line " << token_parser.get_line();
                cerr << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }
            root->brother = _parse_codeblock(token_parser, valid_var_table, loc_var_table, maybe_conti_break, void_return);
            return root;
        } else {
            cerr << "Invalid syntax in line " << token_parser.get_line();
            cerr << " in " << token_parser.get_file_name() << "." << endl;
            cerr << "Parse interrupted." << endl;
            exit(-1);
        }
    } else if (token_pair.first == RETURN) {
        root = new ASTree();
        root->token_pair.first = RETURN;
        root->token_pair.second = "RETURN";
        token_pair = token_parser.get_token();
        if (token_pair.first == SEMI) {
            if (void_return) {
                root->brother = _parse_codeblock(token_parser, valid_var_table, loc_var_table, maybe_conti_break, void_return);
                return root;
            } else {
                cerr << "Non-void function should return a value in line " << token_parser.get_line();
                cerr << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }
        } else {
            if (void_return) {
                if (token_pair.first == IDENT && valid_var_table[token_pair.second] == VOID_FUNC) {
                    token_parser.unget_token();
                    root->child = _check_and_parse_local_expression(token_parser, valid_var_table, 0, 1);
                    // current token pair is SEMI or COMMA or RCB
                    token_parser.unget_token();
                    if (token_parser.get_token().first != SEMI) {
                        cerr << "Invalid syntax in line " << token_parser.get_line();
                        cerr << " in " << token_parser.get_file_name() << "." << endl;
                        cerr << "Parse interrupted." << endl;
                        exit(-1);
                    }
                    root->brother = _parse_codeblock(token_parser, valid_var_table, loc_var_table, maybe_conti_break, void_return);
                    return root;
                } else {
                    cerr << "Void function should not return a value in line " << token_parser.get_line();
                    cerr << " in " << token_parser.get_file_name() << "." << endl;
                    cerr << "Parse interrupted." << endl;
                    exit(-1);
                }
            } else {
                token_parser.unget_token();
                root->child = _check_and_parse_local_expression(token_parser, valid_var_table);
                // current token pair is SEMI or COMMA or RCB
                token_parser.unget_token();
                if (token_parser.get_token().first != SEMI) {
                    cerr << "Invalid syntax in line " << token_parser.get_line();
                    cerr << " in " << token_parser.get_file_name() << "." << endl;
                    cerr << "Parse interrupted." << endl;
                    exit(-1);
                }
                root->brother = _parse_codeblock(token_parser, valid_var_table, loc_var_table, maybe_conti_break, void_return);
                return root;
            }
        }
    } else if (token_pair.first == IF) {
        root = new ASTree();
        root->token_pair.first = BRANCH;
        root->token_pair.second = "BRANCH";
        root->child = _parse_branch(token_parser, valid_var_table, loc_var_table, maybe_conti_break, void_return);
        // current token pair is SEMI or RCB
        root->brother = _parse_codeblock(token_parser, valid_var_table, loc_var_table, maybe_conti_break, void_return);
        return root;
    } else if (token_pair.first == FOR) {
        root = _parse_for(token_parser, valid_var_table, loc_var_table, void_return);
        // current token pair is SEMI or RCB
        root->brother = _parse_codeblock(token_parser, valid_var_table, loc_var_table, maybe_conti_break, void_return);
        return root;        
    } else if (token_pair.first == WHILE) {
        root = _parse_while(token_parser, valid_var_table, loc_var_table, void_return);
        // current token pair is SEMI or RCB
        root->brother = _parse_codeblock(token_parser, valid_var_table, loc_var_table, maybe_conti_break, void_return);
        return root;
    } else if (token_pair.first == DO) {
        root = _parse_do_while(token_parser, valid_var_table, loc_var_table, void_return);
        // current token pair is SEMI or RCB
        root->brother = _parse_codeblock(token_parser, valid_var_table, loc_var_table, maybe_conti_break, void_return);
        return root;
    } else if (token_pair.first >= INT && token_pair.first <= VOID) {
        root = new ASTree();
        root->token_pair.first = LOCAL_VAR_DEC;
        root->token_pair.second = "LOCAL VAR DECLARE";
        root->child = _parse_local_var_dec(token_parser, valid_var_table, loc_var_table, token_pair.first);
        // current token pair is SEMI
        root->brother = _parse_codeblock(token_parser, valid_var_table, loc_var_table, maybe_conti_break, void_return);
        return root;
    } else if (token_pair.first == LCB) {
        root = _create_codeblock(token_parser, valid_var_table, maybe_conti_break, void_return);
        // current token pair is RCB
        root->brother = _parse_codeblock(token_parser, valid_var_table, loc_var_table, maybe_conti_break, void_return);
        return root;        
    } else if (token_pair.first == RCB) {
        return NULL;
    } else {
        token_parser.unget_token();
        root = _check_and_parse_local_expression(token_parser, valid_var_table, 0, 1);
        // current token pair is SEMI or COMMA or RCB
        token_parser.unget_token();
        token_pair = token_parser.get_token();
        if (token_pair.first != SEMI) {
            cerr << "Invalid syntax in line " << token_parser.get_line();
            cerr << " in " << token_parser.get_file_name() << "." << endl;
            cerr << "Parse interrupted." << endl;
            exit(-1);
        }
        root->brother = _parse_codeblock(token_parser, valid_var_table, loc_var_table, maybe_conti_break, void_return);
        return root;
    }
}