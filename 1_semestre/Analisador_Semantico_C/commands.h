#ifndef COMMANDS_FUNCTIONS_H
#define COMMANDS_FUNCTIONS_H

#include"ast_symbols.h"
#include"semantico.tab.h"

Expression* expressionNew(int node_t, union expression_union value, Expression* left, Expression* right, int line, int columns);

void RpnWalk(Expression*);
int constExprSolve(Expression *root);

void deleteTree(Expression*);

#endif