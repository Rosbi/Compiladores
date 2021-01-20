#ifndef COMMANDS_FUNCTIONS_H
#define COMMANDS_FUNCTIONS_H

#include"ast_symbols.h"
// #include"types.h"
#include"semantico.tab.h"
#include"errors.h"

Expression* expressionNew(int node_t, union expression_union value, Expression* left, Expression* right, int line, int columns);

void RpnWalk(Expression*);
Const_expr_state evaluateConstExpr(Expression *root);

void deleteTree(Expression*);

#endif