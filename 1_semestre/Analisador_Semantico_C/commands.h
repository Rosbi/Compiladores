#ifndef COMMANDS_FUNCTIONS_H
#define COMMANDS_FUNCTIONS_H

#include"ast_symbols.h"

Expression* expressionNew(int node_t, int node_v, Expression* left, Expression* right);

void RpnWalk(Expression*);
int constExprSolve(Expression *root);

void deleteTree(Expression*);

#endif