#ifndef COMMANDS_FUNCTIONS_H
#define COMMANDS_FUNCTIONS_H

#include"ast_symbols.h"
#include"semantico.tab.h"

typedef enum error_list {
    NO_ERROR,
	UNDECLARED_SYMBOL,
	REDEFINED_SYMBOL,
	REDECLARED_SYMBOL,
	VARIABLE_DECLARED_VOID,
    INITIALIZER_NOT_CONST,
    STRING_DEFINE,
    DIVISION_BY_ZERO,
    STRING_ASSIGNMENT,
    CONST_IDENTIFIER_ASSIGNMENT,
    RVALUE_ASSIGNMENT
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