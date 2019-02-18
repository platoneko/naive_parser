#include <iostream>
#include "syntax_parser.h"
using namespace std;

void pre_ordered_traverse(ASTree *root, int indent=0);

int main(int argc, char* argv[]) {
    FILE *fp;
    ASTree *root;
    vector<TokenPair> *exp_vec;
    TokenPair token_pair;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <cfile>\n", argv[0]);
        exit(0);
    }

    if ((fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "File '%s' not exist.\n", argv[1]);
        exit(-1);
    }

    SyntaxParser syntax_parser = SyntaxParser(fp, argv[1]);
    root = syntax_parser.parse_syntax();
    pre_ordered_traverse(root);
    return 0;
}

void pre_ordered_traverse(ASTree *root, int indent) {
    if (root != NULL) {
        for (int i = 0; i < indent; ++i) cout << " ";
        if (root->token_pair.first >= INT_VAR) {
            cout << VAR_TYPE[root->token_pair.first - OFFSET] << " ";
        }
        cout << root->token_pair.second << endl;
        pre_ordered_traverse(root->child, indent+1);
        pre_ordered_traverse(root->brother, indent);        
    }
}