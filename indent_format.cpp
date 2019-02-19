#include "syntax_parser.h"
#include <fstream>
using namespace std;


void SyntaxParser::_internal_indent_format(TokenParser &token_parser, ofstream &output, int indent, int is_block) {
    TokenPair token_pair;
    
    cout << "_internal_indent_format" << "\n";

    while (1) {
        token_pair = token_parser.get_token();
        if ((token_pair.first >= IDENT && token_pair.first <= STR_CONST) || token_pair.first == LB) {  // EXPRESSION;
            _print_indent(output, indent);
            output << token_pair.second;            
            int blank = 1;  // if current token pair is LB or LSB, set blank to 0
            if (token_pair.first == IDENT) {
                if ((token_pair = token_parser.get_token()).first == LB || token_pair.first == LSB) {  // FUNC_REF or ARRAY_ELEM
                    output << token_pair.second;
                    blank = 0;
                } else {
                    token_parser.unget_token();
                    blank = 1;
                }
            } else if (token_pair.first == LB) {
                blank = 0;
            } else {
                blank = 1;
            }
            _format_local_expression(token_parser, output, blank);
            if (!is_block) return;
        } else if ((token_pair.first >= INT && token_pair.first <= VOID) || token_pair.first == RETURN) {  // XXX EPRESSION; 
            _print_indent(output, indent);
            output << token_pair.second;
            _format_local_expression(token_parser, output);
            if (!is_block) return;
        } else if (token_pair.first == IF || token_pair.first == FOR || token_pair.first == WHILE) {  // XXX (EXPRESSION)
            _print_indent(output, indent);
            output << token_pair.second;
            _format_local_expression(token_parser, output, 1, 1);
            token_pair = token_parser.get_token();
            if (token_pair.first == LCB) {
                _print_indent(output, indent);
                output << "{" << "\n";
                _internal_indent_format(token_parser, output, indent+4, 1);
            } else {
                token_parser.unget_token();
                _internal_indent_format(token_parser, output, indent+4);
            } 
            if (!is_block) return;
        } else if (token_pair.first == CONTINUE || token_pair.first == BREAK) {
            _print_indent(output, indent);
            output << token_pair.second;
            output << token_parser.get_token().second << "\n";
            if (!is_block) return;
        } else if (token_pair.first == ELSE) {
            _print_indent(output, indent);
            output << token_pair.second;
            token_pair = token_parser.get_token();
            if (token_pair.first == IF) {  // else if (EXPRESSION)
                output << " " << token_pair.second;
                _format_local_expression(token_parser, output, 1, 1);
                token_pair = token_parser.get_token();
                if (token_pair.first == LCB) {
                    _print_indent(output, indent);
                    output << "{" << "\n";
                    _internal_indent_format(token_parser, output, indent+4, 1);
                } else {
                    token_parser.unget_token();
                    _internal_indent_format(token_parser, output, indent+4);
                } 
            } else if (token_pair.first == LCB) {  // else {} | else EXPRESSION
                output << "\n";
                _print_indent(output, indent);
                output << "{" << "\n";
                _internal_indent_format(token_parser, output, indent+4, 1);
            } else {
                output << "\n";
                token_parser.unget_token();
                _internal_indent_format(token_parser, output, indent+4);
            }
            // is_block == 1
        } else if (token_pair.first == LCB) {
            // is_block == 1            
            _print_indent(output, indent);
            output << "{" << "\n"; 
            _internal_indent_format(token_parser, output, indent+4, 1);
        } else if (token_pair.first == RCB) {
            // is_block == 1            
            _print_indent(output, indent-4);
            output << "}" << "\n";
            return;
        } else if (token_pair.first == SEMI) {
             _print_indent(output, indent);
            output << ";" << "\n";
            if (!is_block) return;
        }
    }
}


void SyntaxParser::_indent_format(TokenParser &token_parser) {
    token_parser.reset_position();
    ofstream output("format_" + file_name);
    TokenPair token_pair;
    int blank = 0;
    while ((token_pair = token_parser.get_token()).first != EOF) {
        if (token_pair.first == IDENT) {
            if (blank) output << " ";
            output << token_pair.second;
            if ((token_pair = token_parser.get_token()).first == LB || token_pair.first == LSB) {  // FUNC_REF or ARRAY_ELEM
                output << token_pair.second;
                blank = 0;
            } else {
                token_parser.unget_token();
                blank = 1;
            }
        } else if (token_pair.first >= INT_CONST && token_pair.first <= VOID) {
            if (blank) output << " ";
            output << token_pair.second;
            blank = 1;
        } else if (token_pair.first == LB) {
            if (blank) output << " ";
            output << token_pair.second;
            blank = 0;
        } else if (token_pair.first == RB || token_pair.first == RSB || token_pair.first == RCB || token_pair.first == COMMA) {
            output << token_pair.second;
            blank = 1;                     
        } else if (token_pair.first == SEMI) {
            output << token_pair.second << "\n";
            blank = 0;
        } else if (token_pair.first == LCB) {
            output << "\n{" << "\n";
            _internal_indent_format(token_parser, output, 4, 1);
            blank = 0;
        } else if (token_pair.first == INCLUDE) {
            output << token_pair.second << " " << token_parser.get_token().second << "\n";
        }
        else { // OP
            output << " " << token_pair.second;
            if (token_pair.first == ASSIGN) {
                token_pair = token_parser.get_token();
                if (token_pair.first == LCB) {
                    output << "{";
                    blank = 0;
                    continue;
                } else {
                    token_parser.unget_token();
                }
            }
            blank = 1;
        }
    }
    output.close();
}


void SyntaxParser::_format_local_expression(TokenParser &token_parser, ofstream &output, int blank, int end_with_rb) {
    TokenPair token_pair;
    int brack_counter = 0;
    cout << "_format_local_expression" << "\n";

    while (1) {
        token_pair = token_parser.get_token();
        if (token_pair.first == IDENT) {
            if (blank) output << " ";
            output << token_pair.second;
            if ((token_pair = token_parser.get_token()).first == LB || token_pair.first == LSB) {  // FUNC_REF or ARRAY_ELEM
                if (token_pair.first == LB) ++brack_counter;
                output << token_pair.second;
                blank = 0;
            } else {
                token_parser.unget_token();
                blank = 1;
            }
        } else if (token_pair.first >= INT_CONST && token_pair.first < VOID) {
            if (blank) output << " ";
            output << token_pair.second;
            blank = 1;
        } else if (token_pair.first == LB || token_pair.first == LCB) {
            if (token_pair.first == LB) ++brack_counter;
            if (blank) output << " ";
            output << token_pair.second;
            blank = 0;
        } else if (token_pair.first == RB || token_pair.first == RSB || token_pair.first == RCB || token_pair.first == COMMA) {
            output << token_pair.second;
            if (token_pair.first == RB) {
                --brack_counter;
                if (end_with_rb && brack_counter == 0) {
                    output << "\n";
                    break;
                }
            }
            blank = 1;                     
        } else if (token_pair.first == SEMI) {
            output << token_pair.second;
            if (!end_with_rb) {
                output << "\n";
                break;
            }
            else blank = 1;
        } else { // OP
            output << " " << token_pair.second;
            blank = 1;
        }
    }
}


inline void SyntaxParser::_print_indent(ofstream &output, int indent) {
    for (int i = 0; i < indent; ++i)
        output << " ";
}

