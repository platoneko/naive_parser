#ifndef __VAR_TYPE_H__
#define __VAR_TYPE_H__

#define OFFSET 100

enum var_type {INT_VAR=OFFSET, LONG_VAR, FLOAT_VAR, DOUBLE_VAR, CHAR_VAR, 
               INT_ARRAY, LONG_ARRAY, FLOAT_ARRAY, DOUBLE_ARRAY, CHAR_ARRAY,
               INT_FUNC, LONG_FUNC, FLOAT_FUNC, DOUBLE_FUNC, CHAR_FUNC, VOID_FUNC
               };
extern const char *VAR_TYPE[];
#endif