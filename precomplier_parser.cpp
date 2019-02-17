#include "syntax_parser.h"
using namespace std;


ASTree *SyntaxParser::_parse_include(TokenParser &token_parser) {
    TokenPair token_pair;
    FILE *in_fp;
    char file_name[128];

    token_pair = token_parser.get_token();

    if (token_pair.first == INCLUDE_FILE || token_pair.first == STR_CONST) {
        token_pair.second.copy(file_name, token_pair.second.size() - 2, 1);
        file_name[token_pair.second.size() - 2] = '\0';  // replace " or > with \0

        if ((in_fp = fopen(file_name, "r")) == NULL) {
            cerr << "Cannot find file '" << file_name << "' in line " << token_parser.get_line();
            cerr << " in " << token_parser.get_file_name() << "." << endl;
            cerr << "Parse interrupted." << endl;
            exit(-1);
        }
        
        TokenParser in_token_parser = TokenParser(in_fp, string(file_name));
        return _parse_program(in_token_parser);
    } else {
        cerr << "Invalid syntax in line " << token_parser.get_line();
        cerr << " in " << token_parser.get_file_name() << "." << endl;
        cerr << "Parse interrupted." << endl;
        exit(-1);
    }
}
