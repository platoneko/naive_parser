const char *TOKEN_TYPE[] = {"ERROR_TOKEN", "IDENT", 
                            "INT_CONST", "LONG_CONST", "FLOAT_CONST", "DOUBLE_CONST", "CHAR_CONST", "STR_CONST",
                            "INT", "LONG", "FLOAT", "DOUBLE", "CHAR", "VOID",
                            "IF", "ELSE", "FOR", "WHILE", "BREAK", "CONTINUE", "RETURN",
                            "LB", "RB", "LSB", "RSB", "LCB", "RCB", "SEMI", "COMMA", // Left/Right Bracket, Left/Right Squard Bracket, Left/Right Curly Bracket
                            "AND", "OR", "GT", "LT", "EQ", "NEQ", "GE", "LE", "ASSIGN", // Greater Than, Less Than, Equal, Greater or Equal, Less or Equal
                            "PLUS", "MINUS", "MUL", "DIV", "MOD", 
                            "INCLUDE", "DEFINE", "INCLUDE_FILE"};