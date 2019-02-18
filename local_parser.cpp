#include "syntax_parser.h"
using namespace std;


ASTree *SyntaxParser::_parse_local_var_dec(TokenParser &token_parser, VarTable &valid_var_table, VarTable &loc_var_table, int type) {
    // current token pair is INT... or COMMA
    ASTree *root;
    TokenPair token_pair, tmp;

    token_pair = token_parser.get_token();

    root = new ASTree();
    if (token_pair.first == IDENT) {

        tmp = token_pair;
        token_pair = token_parser.get_token();
        
        if (token_pair.first == SEMI) {  // int a;

            if (loc_var_table.count(tmp.second)) {
                cerr << "Redefinition of '" << tmp.second << "' in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }

            if (type == VOID) {
                cerr << "Invalid syntax in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }

            loc_var_table[tmp.second] = type - INT + INT_VAR;
            valid_var_table[tmp.second] = type - INT + INT_VAR;
            root->token_pair.first = type - INT + INT_VAR;
            root->token_pair.second = tmp.second;

            return root;
        } else if (token_pair.first == COMMA) {  // int a, ...

            if (loc_var_table.count(tmp.second)) {
                cerr << "Redefinition of '" << tmp.second << "' in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }

            if (type == VOID) {
                cerr << "Invalid syntax in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }

            loc_var_table[tmp.second] = type - INT + INT_VAR;
            valid_var_table[tmp.second] = type - INT + INT_VAR;
            root->token_pair.first = type - INT + INT_VAR;
            root->token_pair.second = tmp.second;

            root->brother = _parse_local_var_dec(token_parser, valid_var_table, loc_var_table, type);
            return root;
        } else if (token_pair.first == LB) {  // int func(...)

            if (loc_var_table.count(tmp.second) && loc_var_table[tmp.second] < INT_FUNC) {  // local var exists and is function
                cerr << "Redefinition of '" << tmp.second << "' in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }

            loc_var_table[tmp.second] = type - INT + INT_FUNC;
            valid_var_table[tmp.second] = type - INT + INT_FUNC;
            root->token_pair.first = type - INT + INT_FUNC;
            root->token_pair.second = tmp.second;

            root->child = _parse_func_dec(token_parser, tmp.second, type-INT+INT_FUNC);
            // current token pair is COMMA or SEMI or RCB
            token_parser.unget_token();
            token_pair = token_parser.get_token();

            if (token_pair.first == SEMI) return root;
            if (token_pair.first == COMMA) {
                root->brother = _parse_local_var_dec(token_parser, valid_var_table, loc_var_table, type);                
                return root;
            }
            cerr << "Invalid syntax in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
            cerr << "Parse interrupted." << endl;
            exit(-1);            
        } else if (token_pair.first == LSB) {  // int a[]

            if (loc_var_table.count(tmp.second)) {
                cerr << "Redefinition of '" << tmp.second << "' in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }

            if (type == VOID) {
                cerr << "Invalid syntax in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }

            loc_var_table[tmp.second] = type - INT + INT_ARRAY;
            valid_var_table[tmp.second] = type - INT + INT_ARRAY;
            root->token_pair.first = type - INT + INT_ARRAY;
            root->token_pair.second = tmp.second;

            root->child = _parse_local_array_dec(token_parser, valid_var_table, type);
            // current token pair is COMMA or SEMI
            
            token_parser.unget_token();
            token_pair = token_parser.get_token();
            if (token_pair.first == SEMI) return root;
            if (token_pair.first == COMMA) {
                root->brother = _parse_local_var_dec(token_parser, valid_var_table, loc_var_table, type);
                return root;
            }
            cerr << "Invalid syntax in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
                    cerr << "Parse interrupted." << endl;
                    exit(-1);
        } else if (token_pair.first == ASSIGN) {  // int a = ...

            if (loc_var_table.count(tmp.second)) {
                cerr << "Redefinition of '" << tmp.second << "' in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }

             if (type == VOID) {
                cerr << "Invalid syntax in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }

            loc_var_table[tmp.second] = type - INT + INT_VAR;
            valid_var_table[tmp.second] = type - INT + INT_VAR;
            root->token_pair.first = type - INT + INT_VAR;
            root->token_pair.second = tmp.second;

            root->child = _parse_local_init(token_parser, valid_var_table);
            // current token pair is SEMI or COMMA  
            
            token_parser.unget_token();
            token_pair =  token_parser.get_token();
            if (token_pair.first == SEMI) return root;
            if (token_pair.first == COMMA) {
                root->brother = _parse_local_var_dec(token_parser, valid_var_table, loc_var_table, type);
                return root;
            }
            cerr << "Invalid syntax in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
            cerr << "Parse interrupted." << endl;
            exit(-1); 
        } else {
            cerr << "Invalid syntax in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
            cerr << "Parse interrupted." << endl;
            exit(-1);
        }
    }

    cerr << "Invalid syntax in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
    cerr << "Parse interrupted." << endl;
    exit(-1);
}


ASTree *SyntaxParser::_parse_local_array_dec(TokenParser &token_parser, VarTable &valid_var_table, int type) {
    // current token pair is LSB
    TokenPair token_pair;
    ASTree *root, *child;

    _check_init_subscript(token_parser);
    // current token pair is RSB
    
    token_pair = token_parser.get_token();
    if (token_pair.first == SEMI || token_pair.first == COMMA) {
        return NULL;
    } else if (token_pair.first == ASSIGN) {
        root = new ASTree();
        root->token_pair.first = INITIAL;
        root->token_pair.second = "INITIAL";
        
        token_pair = token_parser.get_token();
        if (token_pair.first == LCB) {
            child = root->child = _check_and_parse_local_expression(token_parser, valid_var_table);
            // current token pair is COMMA or SEMI or RCB
            token_parser.unget_token();
            token_pair = token_parser.get_token();
            while (token_pair.first == COMMA) {
                child->brother = _check_and_parse_local_expression(token_parser, valid_var_table);
                // current token pair is COMMA or SEMI or RCB
                token_parser.unget_token();
                token_pair = token_parser.get_token();
                child = child->brother;
            }
            if (token_pair.first == RCB) {
                token_pair = token_parser.get_token();  // To ensure current token pair can be SEMI or COMMA normally 
                if (token_pair.first == COMMA || token_pair.first == SEMI) {
                    return root;   
                } else {
                    cerr << "Invalid syntax in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
                    cerr << "Parse interrupted." << endl;
                    exit(-1);
                }
            } else {
                cerr << "Invalid syntax in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }
        } else if (token_pair.first == STR_CONST) {
            if (type == CHAR) {
                child = root->child = new ASTree();
                child->token_pair.first = STR_CONST;
                child->token_pair.second = token_pair.second;
                token_pair = token_parser.get_token();  // To ensure current token_pair can be SEMI or COMMA normally
                if (token_pair.first == COMMA || token_pair.first == SEMI) {
                    return root;   
                } else {
                    cerr << "Invalid syntax in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
                    cerr << "Parse interrupted." << endl;
                    exit(-1);
                } 
                return root;
            } else {
                cerr << "Invalid syntax in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }
        } else {
            cerr << "Invalid syntax in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
            cerr << "Parse interrupted." << endl;
            exit(-1);
        }
    } else {
        cerr << "Invalid syntax in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
        cerr << "Parse interrupted." << endl;
        exit(-1);
    }
}


ASTree *SyntaxParser::_parse_local_init(TokenParser &token_parser, VarTable &valid_var_table) {
    ASTree *root = new ASTree();
    root->token_pair.first = INITIAL;
    root->token_pair.second = "INITIAL";
    root->child = _check_and_parse_local_expression(token_parser, valid_var_table);
    // current token pair is SEMI or COMMA or RCB
    TokenPair token_pair;
    token_parser.unget_token();
    token_pair = token_parser.get_token();
    if (token_pair.first == SEMI || token_pair.first == COMMA) {
        return root;
    } else {
        cerr << "Invalid syntax in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
        cerr << "Parse interrupted." << endl;
        exit(-1);
    }
}


ASTree *SyntaxParser::_check_and_parse_local_expression(TokenParser &token_parser, VarTable &valid_var_table, int end_with_rb, int maybe_ref_void_func) {
    int maybe_const = 1, maybe_ident = 1, maybe_op = 0, maybe_lb = 1, maybe_rb = 0, maybe_end = 0, maybe_assign = 0;
    int brack_counter = end_with_rb;
    TokenPair token_pair;
    ASTree *root, *node;
    vector<pair<int, ASTree *>> *token_vec = new vector<pair<int, ASTree *>>();
    
    root = new ASTree();
    root->token_pair.first = EXPRESSION;
    root->token_pair.second = "EXPRESSION";

    while(1) {
        token_pair = token_parser.get_token();

        if (token_pair.first >= INT_CONST && token_pair.first <= CHAR_CONST) {
            if (maybe_const) {
                maybe_const = 0;
                maybe_ident = 0;
                maybe_op = 1;
                maybe_lb = 0;
                maybe_rb = 1;
                maybe_end = 1;
                maybe_assign = 0;
                node = new ASTree();
                node->token_pair = token_pair;
                token_vec->push_back(pair<int, ASTree *>(token_pair.first, node));
            } else {
                cerr << "Invalid syntax in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                cerr << "local_parser _check_and_parse_local_expression 1";
                exit(-1);
            }
        } else if (token_pair.first == IDENT) {
            if (maybe_ident) {
                if (!valid_var_table.count(token_pair.second)) {
                    cerr << "Undeclared identifier '" << token_pair.second << "' in line ";
                    cerr << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
                    cerr << "Parse interrupted." << endl;
                    exit(-1);
                }
                int ident_type = valid_var_table[token_pair.second];
                if (ident_type >= INT_FUNC) {  // function identifier
                    if (ident_type == VOID_FUNC) {
                        if (!maybe_ref_void_func) {
                            cerr << "Invalid operation on void type in line " << token_parser.get_line();
                            cerr << " in " << token_parser.get_file_name() << "." << endl;
                            cerr << "Parse interrupted." << endl;
                            cerr << "local_parser _check_and_parse_local_expression 2";
                            exit(-1);
                        }
                        root->child = _parse_func_ref(token_parser, valid_var_table, token_pair.second, ident_type);
                        // current token pair is RB
                        token_pair = token_parser.get_token();
                        if (token_pair.first != SEMI) {
                            cerr << "Invalid operation on void type in line " << token_parser.get_line();
                            cerr << " in " << token_parser.get_file_name() << "." << endl;
                            cerr << "Parse interrupted." << endl;
                            cerr << "local_parser _check_and_parse_local_expression 3";
                            exit(-1);
                        }
                        delete token_vec;
                        return root;
                    }
                    node = _parse_func_ref(token_parser, valid_var_table, token_pair.second, ident_type);
                    // current token pair is RB
                    token_vec->push_back(pair<int, ASTree *>(token_pair.first, node));
                } else if (ident_type >= INT_ARRAY && ident_type <= CHAR_ARRAY) {
                    node = _parse_array_elem(token_parser, valid_var_table, token_pair.second, ident_type);
                    // current token pair is RSB
                    token_vec->push_back(pair<int, ASTree *>(token_pair.first, node));
                } else { // var identifier
                    node = new ASTree();
                    node->token_pair.first = ident_type;
                    node->token_pair.second = token_pair.second;
                    token_vec->push_back(pair<int, ASTree *>(token_pair.first, node));                    
                }

                maybe_const = 0;
                maybe_ident = 0;
                maybe_op = 1;
                maybe_lb = 0;
                maybe_rb = 1;
                maybe_end = 1;
                maybe_assign = 1;
            } else {
                cerr << "Invalid syntax in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                cerr << "local_parser _check_and_parse_local_expression 4";
                exit(-1);
            }
        } else if (token_pair.first >= AND && token_pair.first <= ASSIGN) {
            if (maybe_op) {
                if (token_pair.first == ASSIGN && !maybe_assign) {
                     cerr << "Expression is not assignable in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
                     cerr << "Parse interrupted." << endl;
                }
                maybe_const = 1;
                maybe_ident = 1;
                maybe_op = 0;
                maybe_lb = 1;
                maybe_rb = 0;
                maybe_end = 0;
                maybe_assign = 0;
                node = new ASTree();
                node->token_pair = token_pair;
                token_vec->push_back(pair<int, ASTree *>(token_pair.first, node));
            } else {
                cerr << "Invalid syntax in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                cerr << "local_parser _check_and_parse_local_expression 5";
                exit(-1);
            }
        } else if (token_pair.first == LB) {
            if (maybe_lb) {
                maybe_const = 1;
                maybe_ident = 1;
                maybe_op = 0;
                maybe_lb = 1;
                maybe_rb = 0;
                maybe_end = 0;
                maybe_assign = 0;
                ++brack_counter;
                token_vec->push_back(pair<int, ASTree *>(token_pair.first, NULL));
            } else {
                cerr << "Invalid syntax in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                cerr << "local_parser _check_and_parse_local_expression 6";
                exit(-1);
            }
        } else if (token_pair.first == RB) {
            if (maybe_rb && brack_counter - 1 >= 0) {
                --brack_counter;
                if (end_with_rb && brack_counter == 0) break;
                maybe_const = 0;
                maybe_ident = 0;
                maybe_op = 1;
                maybe_lb = 0;
                maybe_rb = 1;
                maybe_end = 1;
                maybe_assign = 0;
                token_vec->push_back(pair<int, ASTree *>(token_pair.first, NULL));
            } else {
                cerr << "Invalid syntax in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                cerr << "local_parser _check_and_parse_local_expression 7";                
                exit(-1);
            }
        } else if (token_pair.first == SEMI || token_pair.first == COMMA || token_pair.first == RCB) {
            if (maybe_end && brack_counter-end_with_rb == 0) {
                break;
            } else {
                cerr << "Invalid syntax in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                cerr << "local_parser _check_and_parse_local_expression 8";
                exit(-1);
            }
        } else {
            cerr << "Invalid syntax in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
            cerr << "Parse interrupted." << endl;
            cerr << "local_parser _check_and_parse_local_expression 9";
            exit(-1);
        }
        maybe_ref_void_func = 0;
    }

    root->child = _parse_expression(token_vec);
    return root;
}
