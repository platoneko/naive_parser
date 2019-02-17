#include "syntax_parser.h"
using namespace std;


ASTree *SyntaxParser::_parse_branch(TokenParser &token_parser, VarTable &valid_var_table, VarTable &loc_var_table, int maybe_conti_break, int void_return) {
    // current token pair is IF
    TokenPair token_pair;
    ASTree *root, *node;
    token_pair = token_parser.get_token();
    if (token_pair.first == LB) {
        root = new ASTree();
        root->token_pair.first = CONDITION;
        root->token_pair.second = "CONDITION";
        root->child = _check_and_parse_local_expression(token_parser, valid_var_table, 1);
        // current token pair is RB or SEMI or COMMA or RCB
        token_parser.unget_token();
        if (token_parser.get_token().first != RB) {
            cerr << "Invalid syntax in line " << token_parser.get_line();
            cerr << " in " << token_parser.get_file_name() << "." << endl;
            cerr << "Parse interrupted." << endl;
            cerr << "branch_recurrent_parser _parse_branch 1" << endl;
            exit(-1);
        }
    } else {
        cerr << "Invalid syntax in line " << token_parser.get_line();
        cerr << " in " << token_parser.get_file_name() << "." << endl;
        cerr << "Parse interrupted." << endl;
        cerr << "branch_recurrent_parser _parse_branch 2" << endl;
        exit(-1);
    }
    root->child->brother = _parse_code_after_condition(token_parser, valid_var_table, loc_var_table, maybe_conti_break, void_return);
    // current token pair is SEMI or RCB
    token_pair = token_parser.get_token();
    if (token_pair.first == ELSE) {
        token_pair = token_parser.get_token();
        if (token_pair.first == IF) {
            root->brother = _parse_branch(token_parser, valid_var_table, loc_var_table, maybe_conti_break, void_return);
            return root;
        } else {
            token_parser.unget_token();
            // current token pair is ELSE
            root->brother = new ASTree();
            root->brother->token_pair.first = ELSE;
            root->brother->token_pair.second = "ELSE";
            root->brother->child = _parse_code_after_condition(token_parser, valid_var_table, loc_var_table, maybe_conti_break, void_return);
            // current token pair is SEMI or RB
            return root;
        }
    } else {
        token_parser.unget_token();
        // current token pair is SEMI or RCB
        return root;
    }
}


ASTree *SyntaxParser::_parse_for(TokenParser &token_parser, VarTable &valid_var_table, VarTable &loc_var_table, int void_return) {
    // current token pair is FOR
    TokenPair token_pair;
    ASTree *root;

    token_pair = token_parser.get_token();
    if (token_pair.first == LB) {
        root = new ASTree();
        root->token_pair.first = FOR;
        root->token_pair.second = "FOR";

        root->child = new ASTree();
        root->child->token_pair.first = FOR_1;
        root->child->token_pair.second = "FOR EXPRESSION 1";
        token_pair = token_parser.get_token();
        if (token_pair.first != SEMI) {
            token_parser.unget_token();
            root->child->child = _check_and_parse_local_expression(token_parser, valid_var_table);
        }
        // current token pair is SEMI or COMMA or RCB
        token_parser.unget_token();
        token_pair = token_parser.get_token();
        if (token_pair.first != SEMI) {
            cerr << "Invalid syntax in line " << token_parser.get_line();
            cerr << " in " << token_parser.get_file_name() << "." << endl;
            cerr << "Parse interrupted." << endl;
            cerr << "branch_recurrent_parser _parse_for 1" << endl;
            exit(-1);
        }
        // current token pair is SEMI 
        root->child->brother = new ASTree();
        root->child->brother->token_pair.first = FOR_2;
        root->child->brother->token_pair.second = "FOR EXPRESSION 2";
        token_pair = token_parser.get_token();
        if (token_pair.first != SEMI) {
            token_parser.unget_token();
            root->child->brother->child = _check_and_parse_local_expression(token_parser, valid_var_table);
        }
        // current token pair is SEMI or COMMA or RCB
        token_parser.unget_token();
        token_pair = token_parser.get_token();
        if (token_pair.first != SEMI) {
            cerr << "Invalid syntax in line " << token_parser.get_line();
            cerr << " in " << token_parser.get_file_name() << "." << endl;
            cerr << "Parse interrupted." << endl;
            cerr << "branch_recurrent_parser _parse_for 2" << endl;
            exit(-1);
        }
        // current token pair is SEMI
        root->child->brother->brother = new ASTree();
        root->child->brother->brother->token_pair.first = FOR_3;
        root->child->brother->brother->token_pair.second = "FOR EXPRESSION 3";
        token_pair = token_parser.get_token();
        if (token_pair.first != RB) {
            token_parser.unget_token();
            root->child->brother->brother->child = _check_and_parse_local_expression(token_parser, valid_var_table, 1);
            // current token pair is RB or SEMI or COMMA or RCB
            token_parser.unget_token();
            if (token_parser.get_token().first != RB) {
                cerr << "Invalid syntax in line " << token_parser.get_line();
                cerr << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                cerr << "branch_recurrent_parser _parse_for 3" << endl;
                exit(-1);
            }
        }
        // current token pair is RB
    }
    root->child->brother->brother->brother = _parse_code_after_condition(token_parser, valid_var_table, loc_var_table, 1, void_return);
    // current token pair is SEMI or RCB
    return root;
}


ASTree *SyntaxParser::_parse_while(TokenParser &token_parser, VarTable &valid_var_table, VarTable &loc_var_table, int void_return) {
    // current token pair is WHILE
    TokenPair token_pair;
    ASTree *root; 

    token_pair = token_parser.get_token();
    if (token_pair.first == LB) {
        root = new ASTree();
        root->token_pair.first = WHILE;
        root->token_pair.second = "WHILE";
        root->child = new ASTree();
        root->child->token_pair.first = CONDITION;
        root->child->token_pair.second = "CONDITION";
        root->child->child = _check_and_parse_local_expression(token_parser, valid_var_table, 1);
        // current token pair is RB or SEMI or COMMA or RCB
        token_parser.unget_token();
        if (token_parser.get_token().first != RB) {
            cerr << "Invalid syntax in line " << token_parser.get_line();
            cerr << " in " << token_parser.get_file_name() << "." << endl;
            cerr << "Parse interrupted." << endl;
            cerr << "branch_recurrent_parser _parse_while 1" << endl;
            exit(-1);
        }
        // current token pair is RB
        root->child->brother = _parse_code_after_condition(token_parser, valid_var_table, loc_var_table, 1, void_return);
        // current token pair is SEMI or RCB
        return root;
    } else {
        cerr << "Invalid syntax in line " << token_parser.get_line();
        cerr << " in " << token_parser.get_file_name() << "." << endl;
        cerr << "Parse interrupted." << endl;
        cerr << "branch_recurrent_parser _parse_while 2" << endl;
        exit(-1);
    }
}


ASTree *SyntaxParser::_parse_code_after_condition(TokenParser &token_parser, VarTable &valid_var_table, VarTable &loc_var_table, int maybe_conti_break, int void_return) {
    // current token pair is RB
    TokenPair token_pair;
    ASTree *root;

    token_pair = token_parser.get_token();
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
                cerr << "branch_recurrent_parser _parse_code_after_condition 1" << endl;
                exit(-1);
            }
            return root;
        } else {
            cerr << "Invalid syntax in line " << token_parser.get_line();
            cerr << " in " << token_parser.get_file_name() << "." << endl;
            cerr << "Parse interrupted." << endl;
            cerr << "branch_recurrent_parser _parse_code_after_condition 2" << endl;
            exit(-1);
        }
    } else if (token_pair.first == RETURN) {
        root = new ASTree();
        root->token_pair.first = RETURN;
        root->token_pair.second = "RETURN";
        token_pair = token_parser.get_token();
        if (token_pair.first == SEMI) {
            if (void_return) {
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
                return root;
            }
        }
    } else if (token_pair.first == IF) {
        root = new ASTree();
        root->token_pair.first = BRANCH;
        root->token_pair.second = "BRANCH";
        root->child = _parse_branch(token_parser, valid_var_table, loc_var_table, maybe_conti_break, void_return);
        // current token pair is SEMI or RCB
        return root;
    } else if (token_pair.first == FOR) {
        root = _parse_for(token_parser, valid_var_table, loc_var_table, void_return);
        // current token pair is SEMI or RCB
        return root;        
    } else if (token_pair.first == WHILE) {
        root = _parse_while(token_parser, valid_var_table, loc_var_table, void_return);
        // current token pair is SEMI or RCB
        return root;
    } else if (token_pair.first >= INT && token_pair.first <= VOID) {
        root = new ASTree();
        root->token_pair.first = LOCAL_VAR_DEC;
        root->token_pair.second = "LOCAL VAR DECLARE";
        root->child = _parse_local_var_dec(token_parser, valid_var_table, loc_var_table, token_pair.first);
        // current token pair is SEMI
        return root;
    } else if (token_pair.first == LCB) {
        root = _create_codeblock(token_parser, valid_var_table, maybe_conti_break, void_return);
        // current token pair is RCB
        return root;        
    } else if (token_pair.first == SEMI) {
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
            cerr << "branch_recurrent_parser _parse_code_after_condition 3" << endl;
            exit(-1);
        }
        return root;
    }
}
