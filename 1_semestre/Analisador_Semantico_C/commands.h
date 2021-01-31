#ifndef COMMANDS_FUNCTIONS_H
#define COMMANDS_FUNCTIONS_H

#include"ast_symbols.h"
// #include"types.h"
#include"semantico.tab.h"
#include"errors.h"
#include<stdio.h>

Expression* expressionNew(int node_t, union expression_union value, Expression* left, Expression* right, int line, int columns);

void RpnWalk(Expression*);
Const_expr_state evaluateConstExpr(Expression *root);
Exp_type_state evaluateExpressionType(Exp_type_state root);
Exp_type_state evalExpTypeAndHandleWarnings(Expression *root, FILE* read_warning_line);

Func_type_state matchFunctionCall(Expression *func, Expression *call, FILE* read_warning_line);

void printWarnings(struct warnings* warnings_list, FILE* lines_file);
void freeWarningList(struct warnings *warnings_list);

const char* getOperator(int operator);
char* getType(struct var_type type);

void deleteTree(Expression*);

#endif