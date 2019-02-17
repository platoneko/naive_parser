#include "syntax_parser.h"
using namespace std;


ASTree *SyntaxParser::_parse_func_dec(TokenParser &token_parser, const string &name, int type, int maybe_func_def) {
    // current token pair is LB
    TokenPair token_pair;
    ASTree *root = new ASTree();
    vector<int> func_args;  // store function args list no matter define a function or just declare a func
    vector<string> args_names; // store function args names 
    unordered_map<string, int> loc_var_table;  // store local variables, we deliver it to create_func_codeblock() when define a function
    
    int maybe_void_args = 1;

    if (defined_func_set.count(name)) maybe_func_def = 0;

    root->token_pair.first = FUNC_ARGS;
    root->token_pair.second = "FUNCTION ARGS";

    func_args.push_back(type);
    
    while (1) {
        // current token pair is LB(first time) or COMMA
        token_pair = token_parser.get_token();

        if (token_pair.first >= INT && token_pair.first <= CHAR) {  // (int ...)
            maybe_void_args = 0;

            int arg_type = token_pair.first;
            token_pair = token_parser.get_token();

            if (token_pair.first == IDENT) {  // (int a, ...) | (int a[], ...)
                string arg_name = token_pair.second;

                if (loc_var_table.count(arg_name)) {
                    cerr << "Redefinition of '" << arg_name << "' in line " << token_parser.get_line();
                    cerr << " in " << token_parser.get_file_name() << "." << endl;
                    cerr << "Parse interrupted." << endl;
                    exit(-1);
                }

                token_pair = token_parser.get_token();
                
                if (token_pair.first == COMMA) {  // (int a, ...)
                    func_args.push_back(arg_type-INT+INT_VAR);
                    args_names.push_back(token_pair.second);
                    
                    loc_var_table[arg_name] = (arg_type-INT+INT_VAR);
                } else if (token_pair.first == LSB) {  // (int a[], ...)
                    _check_init_subscript(token_parser);  
                    // current token pair is RSB
                    func_args.push_back(arg_type-INT+INT_ARRAY);
                    args_names.push_back(token_pair.second);
                    
                    loc_var_table[arg_name] = (arg_type-INT+INT_ARRAY);

                    token_pair = token_parser.get_token();

                    if (token_pair.first == COMMA) {  // (int a[], ...)
                        continue;
                    } else if (token_pair.first == RB) { // (..., int a[])
                        break;
                    } else {
                        cerr << "Invalid syntax in line " << token_parser.get_line();
                        cerr << " in " << token_parser.get_file_name() << "." << endl;
                        cerr << "Parse interrupted." << endl;
                        exit(-1);
                    }
                } else if (token_pair.first == RB) { // (..., int a)
                    func_args.push_back(arg_type-INT+INT_VAR);
                    args_names.push_back(token_pair.second);
                    break;
                } else {
                    cerr << "Invalid syntax in line " << token_parser.get_line();
                    cerr << " in " << token_parser.get_file_name() << "." << endl;
                    cerr << "Parse interrupted." << endl;
                    exit(-1);
                }
            } else if (token_pair.first == COMMA) {  // (int, ...)
                func_args.push_back(arg_type-INT+INT_VAR);
                maybe_func_def = 0;
            } else if (token_pair.first == LSB) {  // (int [], ...)
                _check_init_subscript(token_parser);
                // current token pair is RSB
                func_args.push_back(arg_type-INT+INT_ARRAY);
                maybe_func_def = 0;

                token_pair = token_parser.get_token();

                if (token_pair.first == COMMA) {  // (int [], ...)
                    continue;
                } else if (token_pair.first == RB) { // (..., int [])
                    break;
                } else {
                    cerr << "Invalid syntax in line " << token_parser.get_line();
                    cerr << " in " << token_parser.get_file_name() << "." << endl;
                    cerr << "Parse interrupted." << endl;
                    exit(-1);
                }                
            } else if (token_pair.first == RB) {  // (..., int)
                func_args.push_back(arg_type-INT+INT_VAR);
                maybe_func_def = 0;
                break;
            } else {
                cerr << "Invalid syntax in line " << token_parser.get_line();
                cerr << " in " << token_parser.get_file_name() << "." << endl;
                cerr << "Parse interrupted." << endl;
                exit(-1);
            }
        } else if (token_pair.first == RB && maybe_void_args) {  // ()
            break;
        } else {
            cerr << "Invalid syntax in line " << token_parser.get_line();
            cerr << " in " << token_parser.get_file_name() << "." << endl;
            cerr << "Parse interrupted." << endl;
            exit(-1);
        }
    }
    // current token pair is RB
    if (func_args_table.count(name)) {
        const vector<int> &declared_func_args = func_args_table[name];
        if (declared_func_args != func_args) {
            cerr << "Conflicting types for '" << name << "' in line " << token_parser.get_line();
            cerr << " in " << token_parser.get_file_name() << "." << endl;
            cerr << "Parse interrupted." << endl;
            exit(-1);
        }
    } else {
        func_args_table[name] = func_args;
    }
    
    
    token_pair = token_parser.get_token();

    if (token_pair.first == SEMI || token_pair.first == COMMA) {  // function declaration

        int size = func_args.size();
        ASTree *child;
        child = root->child = new ASTree();
        if (size == 1) {
            child->token_pair.first = VOID;
            child->token_pair.second = "void";
        } else {
            child->token_pair.first = func_args[1];
            child->token_pair.second = VAR_TYPE[func_args[1]-OFFSET];
            for (int i = 2; i < size; ++i) {
                child->brother = new ASTree();
                child = child->brother;
                child->token_pair.first = func_args[i];
                child->token_pair.second = VAR_TYPE[func_args[i]-OFFSET];
            }
        }
        return root;
    } else if (token_pair.first == LCB) {
        if (maybe_func_def) {
            int size = args_names.size();
            ASTree *child;
            child = root->child = new ASTree();

            if (size == 0) {
                child->token_pair.first = VOID;
                child->token_pair.second = "void";
            } else {
                child->token_pair.first = func_args[1];
                child->token_pair.second = args_names[0];
                for (int i = 1; i < size; ++i) {
                    child->brother = new ASTree();
                    child = child->brother;
                    child->token_pair.first = func_args[i+1];
                    child->token_pair.second = args_names[i];
                }
            }
            defined_func_set.emplace(name);
            root->brother = _create_func_codeblock(token_parser, global_var_table, loc_var_table, type == VOID_FUNC);
            // current token pair is RCB
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
}


ASTree *SyntaxParser::_parse_func_ref(TokenParser &token_parser, VarTable &valid_var_table, const string &name, int type) {
    // current token pair is IDENT
    if (token_parser.get_token().first != LB) {
        cerr << "Invalid syntax in line " << token_parser.get_line();
        cerr << " in " << token_parser.get_file_name() << "." << endl;
        cerr << "Parse interrupted." << endl;
        exit(-1);
    }
    ASTree *root, *node;

    root = new ASTree();
    root->token_pair.first = FUNC_REF;
    root->token_pair.second = "FUNCTION REF";
    
    root->child = new ASTree();
    root->child->token_pair.first = type;
    root->child->token_pair.second = name;
    
    root->child->brother = new ASTree();
    root->child->brother->token_pair.first = FUNC_ARGS;
    root->child->brother->token_pair.second = "FUNCTION ARGS";

    root->child->brother->child = _check_and_parse_func_args(token_parser, valid_var_table, name);
    // current token pair is RB
    return root;
}


ASTree *SyntaxParser::_check_and_parse_func_args(TokenParser &token_parser, VarTable &valid_var_table, const string &name) {
    // current token pair is LB
    TokenPair token_pair;
    ASTree *root, *node;
    int i, args_count = func_args_table[name].size() - 1;
    cout << args_count << endl;
    if (args_count == 0) {
        if (token_parser.get_token().first != RB) {
            cerr << "Wrong arguments for function '" << name << "' in line " << token_parser.get_line();
            cerr << " in " << token_parser.get_file_name() << "." << endl;
            cerr << "Parse interrupted." << endl;
            cerr << "function_parser _check_and_parse_func_args 1" << endl;
            exit(-1);
        }
        return NULL;
    }

    root = node = _check_and_parse_local_expression(token_parser, valid_var_table, 1);
    cout << "arg expression check pass" << endl;
    // current token pair is RB or COMMA or SEMI or RCB

    for (i = 1; i < args_count; ++i) {
        token_parser.unget_token();
        if (token_parser.get_token().first != COMMA) {
            cerr << "Wrong arguments for function '" << name << "' in line " << token_parser.get_line();
            cerr << " in " << token_parser.get_file_name() << "." << endl;
            cerr << "Parse interrupted." << endl;
            cerr << "function_parser _check_and_parse_func_args 2" << endl;
            exit(-1);
        }
        node->brother = _check_and_parse_local_expression(token_parser, valid_var_table, 1);
        // cout << "Debug: arg expression check pass" << endl;
        // current token pair is RB or COMMA or SEMI or RCB
        node = node->brother;
    }
    // current token pair is RB or COMMA or SEMI or RCB
    token_parser.unget_token();
    if (token_parser.get_token().first != RB) {
        cerr << "Wrong arguments for function '" << name << "' in line " << token_parser.get_line();
        cerr << " in " << token_parser.get_file_name() << "." << endl;
        cerr << "Parse interrupted." << endl;
        cerr << "function_parser _check_and_parse_func_args 3" << endl;
        exit(-1);
    }

    return root;
}
