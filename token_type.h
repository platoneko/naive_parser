#ifndef __TOKEN_TYPE_H__
#define __TOKEN_TYPE_H__
enum token_type {ERROR_TOKEN, IDENT, 
                 INT_CONST, LONG_CONST, FLOAT_CONST, DOUBLE_CONST, CHAR_CONST, STR_CONST,
                 INT, LONG, FLOAT, DOUBLE, CHAR, VOID,
                 IF, ELSE, FOR, WHILE, BREAK, CONTINUE, RETURN,
                 LB, RB, LSB, RSB, LCB, RCB, SEMI, COMMA, // Left/Right Bracket, Left/Right Squard Bracket, Left/Right Curly Bracket
                 AND, OR, GT, LT, EQ, NEQ, GE, LE, // Greater Than, Less Than, Equal, Greater or Equal, Less or Equal
                 PLUS, MINUS, MUL, DIV, MOD, ASSIGN,
                 INCLUDE, DEFINE, INCLUDE_FILE, 
                 PROGRAM, EXPRESSION, BRANCH, CONDITION, // Extension
                 FOR_1, FOR_2, FOR_3, 
                 GLOBAL_VAR_DEC, LOCAL_VAR_DEC, FUNC_REF, FUNC_ARGS, ARRAY_ELEM, INITIAL,
                 CODE_BLOCK, 
                 };

extern const char *TOKEN_TYPE[];
#endif