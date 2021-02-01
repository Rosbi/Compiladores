#ifndef ERRORS_H
#define ERRORS_H

typedef enum error_list {
    NO_ERROR,

    /* Erros em declaracoes de variaveis/funçoes/prototipos */
	REDEFINED_SYMBOL,
	VARIABLE_DECLARED_VOID,
	REDECLARED_SYMBOL,
    PARAMETER_DECLARED_VOID,
    ARGUMENT_DIFF_PROTOTYPE,
    PROTOTYPE_FEWER_ARGS,
    PROTOTYPE_MORE_ARGS,
    CONFLICTING_TYPES,
    ARR_NEGATIVE_INITIALIZER,
    ARR_ZERO_INITIALIZER,
    INCOMPATIBLE_INITIALIZER,

    /* Erros em chamadas de função */
    OBJECT_NOT_A_FUNCTION,
	UNDECLARED_SYMBOL,
    TOO_FEW_ARGUMENTS,
    TOO_MANY_ARGUMENTS,
    INCOMPATIBLE_ARGUMENT_TYPE,

    /* Erros em retorno de funcao */
        //no return statement in function returning non-void
        //return with a value, in function returning void
        //return with no value, in function returning non-void
        //incompatible types when returning type ’<nome-do-tipo>’ but ’<nome-do-tipo>’ was expected

    /* Erros na verificação de tipos em ocmandos/expressões */
    //UNDECLARED_SYMBOL
    RVALUE_INC_OPERAND,
    RVALUE_DEC_OPERAND,
    RVALUE_ASSIGNMENT,
    INITIALIZER_NOT_CONST,
    RSHIFT_NEGATIVE,
    LSHIFT_NEGATIVE,
    STRING_DEFINE,
    DIVISION_BY_ZERO,
        //void value not ignored as it ought to be
    INVALID_SUBSCRIPTOR,
    RVALUE_UNARY_OPERAND,
    INVALID_UNR_OPERAND,
    NOT_INT_SUBSCRIPTOR,
    WRONG_TYPE_COMPARISON,
    IMPOSSIBLE_INT_CONVERSION,
    STRING_ASSIGNMENT,
    INCOMPATIBLE_ASSIGNMENT,
    INVALID_BIN_OPERANDS,
    WRONG_ARG_UNR_PLUS,//wrong type argument to unary plus
    WRONG_ARG_UNR_MINUS,//wrong type argument to unary minus

    WARNINGS_START,
    //Warnings
    LSHIFT_EXCEEDS_SIZE_W,
    RSHIFT_EXCEEDS_SIZE_W,
    INDEX_OUT_OF_BOUNDS,
    WRONG_TYPE_COMPARISON_W,
    DIFFERENT_CAST_SIZE_W,
    CONDITIONAL_TYPE_MISSMATCH_W,

    //Outros erros
    CONST_IDENTIFIER_ASSIGNMENT,
    IDENTIFIER_NOT_A_FUNCTION,
}Error_list;

typedef struct const_expr_state{
    int value;
    Error_list error;
    Expression *exp;
}Const_expr_state;

typedef struct exp_type_state{
    struct warnings{
        Error_list warning;
        Expression *exp;
        struct warnings *next;
    } *warnings_list;
    Error_list error;
    Expression *exp;
}Exp_type_state;

typedef struct func_type_state{
    Error_list error;
    Expression *func;
    char *func_name;
    int wrong_arg;
    struct var_type expected_type;
    struct var_type received_type;
}Func_type_state;

#endif
