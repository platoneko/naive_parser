#include <iostream>
#include <string>

#include "token_kind.h"
#include "index2type.h"
#include "token_parser.h"

using namespace std;

int main(int argc, char* argv[]) {
    FILE *fp;
    TokenPair token_pair;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <cfile>\n", argv[0]);
        exit(0);
    }

    if ((fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "File '%s' not exist.\n", argv[1]);
        exit(-1);
    }

    init_token_table();

    do {
        token_pair = get_token(fp);
        if (token_pair.first != EOF && token_pair.first != ERROR_TOKEN)
            cout << INDEX2TYPE[token_pair.first] << "\t" << token_pair.second << endl;
    } while (token_pair.first != EOF && token_pair.first != ERROR_TOKEN);

    if (token_pair.first == ERROR_TOKEN) {
        cerr << "Invalid token  " << token_pair.second <<  "  in line " << line_counter << ".";
        cerr << "  Parse interrupted." << endl;
        exit(-1);
    }

    exit(0);
}