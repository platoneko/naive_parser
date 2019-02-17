#include "syntax_parser.h"
using namespace std;


void SyntaxParser::_check_init_subscript(TokenParser &token_parser) {
    // current token pair is LSB
    TokenPair token_pair;
    int maybe_rsb = 1, maybe_lb = 1, maybe_rb = 0, maybe_op = 0, maybe_const = 1;
    int brack_counter = 0;
    while (1) {
        token_pair = token_parser.get_token();
        if (token_pair.first == INT_CONST || token_pair.first == LONG_CONST || token_pair.first == CHAR_CONST) {
            if (maybe_const) {
                maybe_rsb = 1;
                maybe_lb = 0;
                maybe_rb = 1;
                maybe_op = 1;
                maybe_const = 0;
            } else {
                cerr << "Invalid syntax in line " << token_parser.get_line();
                cerr << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }
        } else if (token_pair.first == RSB) {
            if (maybe_rsb && brack_counter == 0) {
                return;
            } else {
                cerr << "Invalid syntax in line " << token_parser.get_line();
                cerr << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }
        } else if (token_pair.first == LB) {
            if (maybe_lb) {
                maybe_rsb = 0;
                maybe_lb = 1;
                maybe_rb = 0;
                maybe_op = 0;
                maybe_const = 1;
                ++brack_counter;
            } else {
                cerr << "Invalid syntax in line " << token_parser.get_line();
                cerr << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }
        } else if (token_pair.first == RB) {
            if (maybe_rb && brack_counter - 1 >= 0) {
                maybe_rsb = 1;
                maybe_lb = 0;
                maybe_rb = 1;
                maybe_op = 1;
                maybe_const = 0;
                --brack_counter;
            } else {
                cerr << "Invalid syntax in line " << token_parser.get_line();
                cerr << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }
        } else if (token_pair.first >= AND && token_pair.first <= MOD) {
            if (maybe_op) {
                maybe_rsb = 0;
                maybe_lb = 1;
                maybe_rb = 0;
                maybe_op = 0;
                maybe_const = 1;
            } else {
                cerr << "Invalid syntax in line " << token_parser.get_line();
                cerr << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }
        } else {
            cerr << "Invalid syntax in line " << token_parser.get_line();
            cerr << " in " << token_parser.get_file_name() << "." << endl;
            cerr << "Parse interrupted." << endl;
            exit(-1);
        }
    }
}


ASTree *SyntaxParser::_check_and_parse_elem_subscript(TokenParser &token_parser, VarTable &valid_var_table) {
    // current token pair is LSB
    TokenPair token_pair;
    ASTree *root, *node;

    int maybe_const = 1, maybe_ident = 1, maybe_op = 0, maybe_lb = 1, maybe_rb = 0, maybe_rsb = 0;
    int brack_counter = 0;
    vector<pair<int, ASTree *>> *token_vec = new vector<pair<int, ASTree *>>();
    
    while(1) {
        token_pair = token_parser.get_token();

        if (token_pair.first == INT_CONST || token_pair.first == LONG_CONST || token_pair.first == CHAR_CONST) {
            if (maybe_const) {
                maybe_const = 0;
                maybe_ident = 0;
                maybe_op = 1;
                maybe_lb = 0;
                maybe_rb = 1;
                maybe_rsb = 1;
                node = new ASTree();
                node->token_pair = token_pair;
                token_vec->push_back(pair<int, ASTree *>(token_pair.first, node));
            } else {
                cerr << "Invalid syntax in line " << token_parser.get_line();
                cerr << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }
        } else if (token_pair.first == IDENT) {
            if (maybe_ident) {
                if (!valid_var_table.count(token_pair.second)) {
                    cerr << "Undeclared identifier '" << token_pair.second << "' in line " << token_parser.get_line();
                    cerr << " in " << token_parser.get_file_name() << "." << endl;
                    cerr << "Parse interrupted." << endl;
                    exit(-1);
                }
                int ident_type = valid_var_table[token_pair.second];
                if (ident_type == INT_FUNC || ident_type == LONG_FUNC || ident_type == CHAR_FUNC) {  // function identifier
                    
                    node = _parse_func_ref(token_parser, valid_var_table, token_pair.second, ident_type);
                    // current token pair is RB
                    token_vec->push_back(pair<int, ASTree *>(token_pair.first, node));
                } else if (ident_type == INT_ARRAY || ident_type == LONG_ARRAY || ident_type == CHAR_ARRAY) {
                    node = _parse_array_elem(token_parser, valid_var_table, token_pair.second, ident_type);
                    // current token pair is RSB
                    token_vec->push_back(pair<int, ASTree *>(token_pair.first, node));
                } else if (ident_type == INT_VAR || ident_type == LONG_VAR || ident_type == CHAR_VAR) {
                    node = new ASTree();
                    node->token_pair.first = ident_type;
                    node->token_pair.second = token_pair.second;
                    token_vec->push_back(pair<int, ASTree *>(token_pair.first, node));                    
                } else {
                    cerr << "Invalid syntax in line " << token_parser.get_line();
                    cerr << " in " << token_parser.get_file_name() << "." << endl;
                    cerr << "Parse interrupted." << endl;
                    exit(-1);
                }

                maybe_const = 0;
                maybe_ident = 0;
                maybe_op = 1;
                maybe_lb = 0;
                maybe_rb = 1;
                maybe_rsb = 1;
            } else {
                cerr << "Invalid syntax in line " << token_parser.get_line();
                cerr << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Array subscript is not an integer." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }
        } else if (token_pair.first >= AND && token_pair.first <= ASSIGN) {
            if (maybe_op) {
                maybe_const = 1;
                maybe_ident = 1;
                maybe_op = 0;
                maybe_lb = 1;
                maybe_rb = 0;
                maybe_rsb = 0;
                node = new ASTree();
                node->token_pair = token_pair;
                token_vec->push_back(pair<int, ASTree *>(token_pair.first, node));
            } else {
                cerr << "Invalid syntax in line " << token_parser.get_line();
                cerr << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }
        } else if (token_pair.first == LB) {
            if (maybe_lb) {
                maybe_const = 1;
                maybe_ident = 1;
                maybe_op = 0;
                maybe_lb = 1;
                maybe_rb = 0;
                maybe_rsb = 0;
                ++brack_counter;
                token_vec->push_back(pair<int, ASTree *>(token_pair.first, NULL));
            } else {
                cerr << "Invalid syntax in line " << token_parser.get_line();
                cerr << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }
        } else if (token_pair.first == RB) {
            if (maybe_rb && brack_counter - 1 >= 0) {
                maybe_const = 0;
                maybe_ident = 0;
                maybe_op = 1;
                maybe_lb = 0;
                maybe_rb = 1;
                maybe_rsb = 1;
                --brack_counter;
                token_vec->push_back(pair<int, ASTree *>(token_pair.first, NULL));
            } else {
                cerr << "Invalid syntax in line " << token_parser.get_line();
                cerr << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }
        } else if (token_pair.first == RSB) {
            if (maybe_rsb && brack_counter == 0) {
                break;
            } else {
                cerr << "Invalid syntax in line " << token_parser.get_line();
                cerr << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }
        } else {
            cerr << "Invalid syntax in line " << token_parser.get_line();
            cerr << " in " << token_parser.get_file_name() << "." << endl;
            cerr << "Parse interrupted." << endl;
            exit(-1);
        }
    }
    // current token pair is RSB
    root = new ASTree();
    root->token_pair.first = EXPRESSION;
    root->token_pair.second = "EPRESSION";
    root->child = _parse_expression(token_vec);
    return root;
}


ASTree *SyntaxParser::_parse_array_elem(TokenParser &token_parser, VarTable &valid_var_table, const string &name, int type) {
    // current token pair is IDENT
    ASTree *root;
    if (token_parser.get_token().first != LSB) {
        cerr << "Invalid syntax in line " << token_parser.get_line();
        cerr << " in " << token_parser.get_file_name() << "." << endl;
        cerr << "Parse interrupted." << endl;
        exit(-1);
    }

    root = new ASTree();
    root->token_pair.first = ARRAY_ELEM;
    root->token_pair.second = "ARRAY ELEM";

    root->child = new ASTree();
    root->child->token_pair.first = type;
    root->child->token_pair.second = name;

    root->brother = _check_and_parse_elem_subscript(token_parser, valid_var_table);
    // current token pair is RSB
    return root;
}
