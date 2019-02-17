#include "syntax_parser.h"
using namespace std;


ASTree *SyntaxParser::_parse_program(TokenParser &token_parser) {
    ASTree *root, *tmp;
    TokenPair token_pair;

    while ((token_pair = token_parser.get_token()).first == SEMI);  // ignore ';'s
    
    if (token_pair.first != EOF) {

        if (token_pair.first >= INT && token_pair.first <= VOID) {
            root = new ASTree();
            root->token_pair.first = GLOBAL_VAR_DEC;
            root->token_pair.second = "GLOBAL VAR DECLARE";
            root->child = _parse_global_var_dec(token_parser, token_pair.first, 1);
            // current token pair is SEMI
            root->brother = _parse_program(token_parser);
            return root;
        } else if (token_pair.first == INCLUDE) {
            root =  _parse_include(token_parser);
            // current token pair is INCLUDE_FILE or STR_CONST
            tmp = root;
            while(tmp->brother != NULL) tmp = tmp->brother;
            tmp->brother = _parse_program(token_parser);
            return root;
        } else if (token_pair.first == DEFINE) {
            // TODO
        } else {
            cerr << "Invalid syntax ' " <<  token_pair.second << " ' in line " << token_parser.get_line();
            cerr << " in " << token_parser.get_file_name() << "." << endl;
            cerr << "Parse interrupted." << endl;
            exit(-1);
        }
    }

    return NULL;
}