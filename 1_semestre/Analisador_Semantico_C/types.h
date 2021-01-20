#ifndef TYPES_H
#define TYPES_H

#include"ast_symbols.h"
#include"errors.h"

enum compatibility_enum {
    PLUS_COMP,
    MINUS_COMP,
    MUL_COMP,
    DIV_COMP,
    REMAINDER_COMP,
    BIT_AND_COMP,
    BIT_OR_COMP,
    BIT_XOR_COMP,
    LOG_AND_COMP,
    LOG_OR_COMP,
    EUQAL_COMP,
    DIFF_COMP,
    LESS_COMP,
    GREAT_COMP,
    LEQ_COMP,
    GEQ_COMP,
    RSHIFT_COMP,
    LSHIFT_COMP,
    ASSIGN_COMP,
    ADD_ASSIGN_COMP,
    SUB_ASSIGN_COMP,
    UN_PLUS_COMP,
    UN_MINUS_COMP,
    UN_DEFERENCE_COMP,
    UN_INC_COMP,
    UN_DEC_COMP,
    UN_BIT_NOT_COMP,
    UN_LOG_NOT_COMP,
    UN_ADDRESS_COMP,
    INT_INT=0,
    CHAR_CHAR,
    INT_CHAR,
    POINTER_INT,
    POINTER_CHAR,
    POINTER_POINTER,
    INT_COMP=0,
    CHAR_COMP,
    POINTER_COMP,
};

Error_list matchTypes(int operation, struct var_type *var1, struct var_type *var2);

#endif