#ifndef COMMANDS_FUNCTIONS_H
#define COMMANDS_FUNCTIONS_H

#include"ast_symbols.h"
#include"semantico.tab.h"

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
        //incompatible types in initialization when assigning to type ’<nome-do-tipo>’ from type ’<nome-do-tipo>’

    /* Erros em chamadas de função */
        //called object ’<nome-do-identificador>’ is not a function or function pointer
	UNDECLARED_SYMBOL,
        //too few arguments to function ’<nome-da-funcao>’
        //too many arguments to function ’<nome-da-funcao>’
        //incompatible type for argument ’<numero-do-argumento>’ of ’<nome-da-funcao>’ expected ’<nome-do-tipo>’ but argument is of type ’<nome-do-tipo>’

    /* Erros em retorno de funcao */
        //no return statement in function returning non-void
        //return with a value, in function returning void
        //return with no value, in function returning non-void
        //incompatible types when returning type ’<nome-do-tipo>’ but ’<nome-do-tipo>’ was expected

    /* Erros na verificação de tipos em ocmandos/expressões */
    //UNDECLARED_SYMBOL
        //lvalue required as increment operand
    RVALUE_ASSIGNMENT,
    INITIALIZER_NOT_CONST,
        //right shift count is negative
        //left shift count is negative
    STRING_DEFINE,
    DIVISION_BY_ZERO,
        //void value not ignored as it ought to be
        //subscripted value is neither array nor pointer
        //lvalue required as unary ’<operador-unario>’ operand
        //invalid type argument of unary ’<operador-unario>’ (have ’<nome-do-tipo>’)
        //array subscript is not an integer
        //comparison between ’<nome-do-tipo>’ and ’<nome-do-tipo>’ operator ’<operador-binario>’
        //cannot convert from ’<nome-do-tipo>’ to int
    STRING_ASSIGNMENT,
    //STRING_ASSIGNMENT,
        //incompatible types when assigning to type ’<nome-do-tipo>’ from type ’<nome-do-tipo>’
        //invalid operands to binary ’<operador-binario>’ (have ’<nome-do-tipo>’ and ’<nome-do-tipo>’)
        //wrong type argument to unary plus
        //wrong type argument to unary minus

    //Warnings
        //left shift count >= width of type
        //right shift count >= width of type
        //array index out of bounds
        //comparison between ’<nome-do-tipo>’ and ’<nome-do-tipo>’ operator ’<operador-binario>’
        //cast from ’<nome-do-tipo>’ to ’<nome-do-tipo>’ of different size
        //’<nome-do-tipo>’/’<nome-do-tipo>’ type mismatch in conditional expression

    //Outros erros
    CONST_IDENTIFIER_ASSIGNMENT,
}Error_list;

typedef struct const_expr_state{
    int value;
    Error_list error;
    Expression *exp;
}Const_expr_state;

Expression* expressionNew(int node_t, union expression_union value, Expression* left, Expression* right, int line, int columns);

void RpnWalk(Expression*);
Const_expr_state evaluateConstExpr(Expression *root);

void deleteTree(Expression*);

#endif