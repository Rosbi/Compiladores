#ifndef TYPES_H
#define TYPES_H

typedef enum error_list Error_list;

extern const int TIPOS_POINTER_SIZE;
extern const int TIPOS_INT_SIZE;
extern const int TIPOS_CHAR_SIZE;
extern const int TIPOS_VOID_SIZE;

typedef enum types_compatibility {
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
    EQUAL_COMP,
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
}Types_compatibility;

typedef enum type_matching{
    MATCH,
    TYPE_MISSMATCH,
    BASE_PTR_MISSMATCH,
    PTR_MISSMATCH,
    PTR_AND_NON_PTR,
}Type_matching;

Type_matching verifyTypes(Var_type left_var, Var_type right_var);
Error_list matchTypes(int operation, Var_type left_var, Var_type right_var);

#endif