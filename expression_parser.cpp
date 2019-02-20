#include "syntax_parser.h"
using namespace std;


ASTree *SyntaxParser::_parse_expression(vector<pair<int, ASTree *>> *token_vec) {
    int lowest_prior = 0, cur_prior;
    int root_index = 0;
    int i, start, end;
    int brack_counter = 0;

    int type;
    ASTree *root;
    vector<pair<int, ASTree *>> *left_vec, *right_vec;

    start = 0;
    end = token_vec->size();
    
    while (1) {
        for (i = start; i < end; ++i) {
        type = (*token_vec)[i].first;

            if (type == LB) {
                ++brack_counter;
            } else if (type == RB) {
                --brack_counter;
            } else {
                if (brack_counter > 0) {
                    continue;
                } else {
                    cur_prior = priority_table[type];
                    if (cur_prior == 15) { // ASSIGN is right combination op
                        lowest_prior = cur_prior > lowest_prior ? (root_index = i, cur_prior) : lowest_prior;
                    } else {
                        lowest_prior = cur_prior >= lowest_prior ? (root_index = i, cur_prior) : lowest_prior;
                    }
                }
            }
        }

        if (lowest_prior > 0) {
            break;
        } else {
            ++start;
            --end;
        }
    } 
     
    if (lowest_prior == 1) {
        root = (*token_vec)[root_index].second;
        delete token_vec;
        return root;
    } else {  // lowest_prior > 1
        root = (*token_vec)[root_index].second;

        left_vec = new vector<pair<int, ASTree *>> (token_vec->begin() + start, token_vec->begin() + root_index);
        // cout << "left: " << left_vec->size() << endl;
        right_vec = new vector<pair<int, ASTree *>> (token_vec->begin() + root_index + 1, token_vec->begin() + end);
        // cout << "right: " << left_vec->size() << endl;
        delete token_vec;

        root->child = _parse_expression(left_vec);
        root->child->brother = _parse_expression(right_vec);
        return root;
    } 
}