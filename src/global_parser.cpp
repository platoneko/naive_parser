#include "syntax_parser.h"
using namespace std;


ASTree *SyntaxParser::_parse_global_var_dec(TokenParser &token_parser, int type, int maybe_func_def) {
    // current token pair is INT... or COMMA
    ASTree *root;
    TokenPair token_pair, tmp;

    token_pair = token_parser.get_token();

    root = new ASTree();

    if (token_pair.first == IDENT) {

        tmp = token_pair;
        token_pair = token_parser.get_token();
        
        if (token_pair.first == SEMI) {  // int a;

            if (global_var_table.count(tmp.second) && global_var_table[tmp.second] != type - INT + INT_VAR) {
                cerr << "Redefinition of '" << tmp.second << "' in line " << token_parser.get_line();
                cerr << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }

            if (type == VOID) {
                cerr << "Invalid syntax in line " << token_parser.get_line();
                cerr << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }

            global_var_table[tmp.second] = type - INT + INT_VAR;
            root->token_pair.first = type - INT + INT_VAR;
            root->token_pair.second = tmp.second;

            return root;
        } else if (token_pair.first == COMMA) {  // int a, ...

            if (global_var_table.count(tmp.second) && global_var_table[tmp.second] != type - INT + INT_VAR) {
                cerr << "Redefinition of '" << tmp.second << "' in line " << token_parser.get_line();
                cerr << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }

            if (type == VOID) {
                cerr << "Invalid syntax in line " << token_parser.get_line();
                cerr << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }

            global_var_table[tmp.second] = type - INT + INT_VAR;
            root->token_pair.first = type - INT + INT_VAR;
            root->token_pair.second = tmp.second;

            root->brother = _parse_global_var_dec(token_parser, type);
            return root;
        } else if (token_pair.first == LB) {  // int func(...)

            if (global_var_table.count(tmp.second) && global_var_table[tmp.second] < INT_FUNC) {
                cerr << "Redefinition of '" << tmp.second << "' in line " << token_parser.get_line();
                cerr << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }

            global_var_table[tmp.second] = type - INT + INT_FUNC;
            root->token_pair.first = type - INT + INT_FUNC;
            root->token_pair.second = tmp.second;

            root->child = _parse_func_dec(token_parser, tmp.second, type-INT+INT_FUNC, maybe_func_def);
            // current token pair is COMMA or SEMI or RCB
            token_parser.unget_token();
            token_pair = token_parser.get_token();

            if (token_pair.first == SEMI || token_pair.first == RCB) return root;
            if (token_pair.first == COMMA) {
                root->brother = _parse_global_var_dec(token_parser, type);
                return root;
            }
            cerr << "Invalid syntax in line " << token_parser.get_line();
            cerr << " in " << token_parser.get_file_name() << "." << endl;
            cerr << "Parse interrupted." << endl;
            exit(-1);            
        } else if (token_pair.first == LSB) {  // int a[]

            if (global_var_table.count(tmp.second) && global_var_table[tmp.second] != type - INT + INT_ARRAY) {
                cerr << "Redefinition of '" << tmp.second << "' in line " << token_parser.get_line();
                cerr << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }

            if (type == VOID) {
                cerr << "Invalid syntax in line " << token_parser.get_line();
                cerr << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }

            global_var_table[tmp.second] = type - INT + INT_ARRAY;
            root->token_pair.first = type - INT + INT_ARRAY;
            root->token_pair.second = tmp.second;

            root->child = _parse_global_array_dec(token_parser, type);
            // current token pair is COMMA or SEMI
            
            token_parser.unget_token();
            token_pair = token_parser.get_token();
            if (token_pair.first == SEMI) return root;
            if (token_pair.first == COMMA) {
                root->brother = _parse_global_var_dec(token_parser, type);
                return root;
            }
            cerr << "Invalid syntax in line " << token_parser.get_line();
            cerr << " in " << token_parser.get_file_name() << "." << endl;
            cerr << "Parse interrupted." << endl;
            exit(-1);
        } else if (token_pair.first == ASSIGN) {  // int a = ...

            if (initialized_global_var_set.count(tmp.second) ||
                (global_var_table.count(tmp.second) && global_var_table[tmp.second] != type - INT + INT_VAR)) {
                cerr << "Redefinition of '" << tmp.second << "' in line " << token_parser.get_line();
                cerr << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }
            initialized_global_var_set.emplace(tmp.second);

            if (type == VOID) {
                cerr << "Invalid syntax in line " << token_parser.get_line();
                cerr << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }

            global_var_table[tmp.second] = type - INT + INT_VAR;
            root->token_pair.first = type - INT + INT_VAR;
            root->token_pair.second = tmp.second;
            
            root->child = _parse_global_init(token_parser);
            // current token pair is SEMI or COMMA  
            
            token_parser.unget_token();
            token_pair =  token_parser.get_token();
            if (token_pair.first == SEMI) return root;
            if (token_pair.first == COMMA) {
                root->brother = _parse_global_var_dec(token_parser, type);
                return root;
            }
            cerr << "Invalid syntax in line " << token_parser.get_line();
            cerr << " in " << token_parser.get_file_name() << "." << endl;
            cerr << "Parse interrupted." << endl;
            exit(-1); 
        } else {
            cerr << "Invalid syntax in line " << token_parser.get_line();
            cerr << " in " << token_parser.get_file_name() << "." << endl;
            cerr << "Parse interrupted." << endl;
            exit(-1);
        }
    }

    cerr << "Invalid syntax in line " << token_parser.get_line();
    cerr << " in " << token_parser.get_file_name() << "." << endl;
    cerr << "Parse interrupted." << endl;
    exit(-1);
}


ASTree *SyntaxParser::_parse_global_array_dec(TokenParser &token_parser, int type) {
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
            child = root->child = _check_and_parse_global_expression(token_parser);
            // current token pair is COMMA or SEMI or RCB
            token_parser.unget_token();
            token_pair = token_parser.get_token();
            while (token_pair.first == COMMA) {
                child->brother = _check_and_parse_global_expression(token_parser);
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
        } else if (token_pair.first == STR_CONST) {
            if (type == CHAR) {
                child = root->child = new ASTree();
                child->token_pair.first = STR_CONST;
                child->token_pair.second = token_pair.second;
                token_pair = token_parser.get_token();  // To ensure current token_pair can be SEMI or COMMA normally
                if (token_pair.first == COMMA || token_pair.first == SEMI) {
                    return root;   
                } else {
                    cerr << "Invalid syntax in line " << token_parser.get_line();
                    cerr << " in " << token_parser.get_file_name() << "." << endl;
                    cerr << "Parse interrupted." << endl;
                    exit(-1);
                } 
                return root;
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
    } else {
        cerr << "Invalid syntax in line " << token_parser.get_line();
        cerr << " in " << token_parser.get_file_name() << "." << endl;
        cerr << "Parse interrupted." << endl;
        exit(-1);
    }
}


ASTree *SyntaxParser::_parse_global_init(TokenParser &token_parser) {
    ASTree *root = new ASTree();
    root->token_pair.first = INITIAL;
    root->token_pair.second = "INITIAL";
    root->child = _check_and_parse_global_expression(token_parser);
    // current token pair is SEMI or COMMA or RCB
    TokenPair token_pair;
    token_parser.unget_token();
    token_pair = token_parser.get_token();
    if (token_pair.first == SEMI || token_pair.first == COMMA) {
        return root;
    } else {
        cerr << "Invalid syntax in line " << token_parser.get_line();
        cerr << " in " << token_parser.get_file_name() << "." << endl;
        cerr << "Parse interrupted." << endl;
        exit(-1);
    }
}


ASTree *SyntaxParser::_check_and_parse_global_expression(TokenParser &token_parser) {
    TokenPair token_pair;
    int maybe_lb = 1, maybe_rb = 0, maybe_op = 0, maybe_const = 1, maybe_end = 0;
    int brack_counter = 0;
    ASTree *root, *node;
    vector<pair<int, ASTree *>> *token_vec = new vector<pair<int, ASTree *>>();

    root = new ASTree();
    root->token_pair.first = EXPRESSION;
    root->token_pair.second = "EXPRESSION";

    while (1) {
        token_pair = token_parser.get_token();

        if (token_pair.first == LB) {
            if (maybe_lb) {
                maybe_lb = 1;
                maybe_rb = 0;
                maybe_op = 0;
                maybe_const = 1;
                maybe_end = 0;
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
                maybe_lb = 0;
                maybe_rb = 1;
                maybe_op = 1;
                maybe_const = 0;
                maybe_end = 1;
                --brack_counter;
                token_vec->push_back(pair<int, ASTree *>(token_pair.first, NULL));
            } else {
                cerr << "Invalid syntax in line " << token_parser.get_line();
                cerr << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }
        } else if (token_pair.first >= AND && token_pair.first <= MOD) {
            if (maybe_op) {
                maybe_lb = 1;
                maybe_rb = 0;
                maybe_op = 0;
                maybe_const = 1;
                maybe_end = 0;
                node = new ASTree();
                node->token_pair = token_pair;
                token_vec->push_back(pair<int, ASTree *>(token_pair.first, node));
            } else {
                cerr << "Invalid syntax in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }
        } else if (token_pair.first >= INT_CONST && token_pair.first <= CHAR_CONST) {
            if (maybe_const) {
                maybe_lb = 0;
                maybe_rb = 1;
                maybe_op = 1;
                maybe_const = 0;
                maybe_end = 1;
                node = new ASTree();
                node->token_pair = token_pair;
                token_vec->push_back(pair<int, ASTree *>(token_pair.first, node));
            } else {
                cerr << "Invalid syntax in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }
        } else if (token_pair.first == SEMI || token_pair.first == COMMA || token_pair.first == RCB) {
            if (maybe_end && brack_counter == 0) {
                break;
            } else {
                cerr << "Invalid syntax in line " << token_parser.get_line() << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }
        }

    }

    root->child = _parse_expression(token_vec);
    return root;
}
