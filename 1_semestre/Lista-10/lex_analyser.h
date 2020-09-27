#ifndef CONST_H
#define CONST_H

#include<stdio.h>
#include<stdint.h>
#include"globals.h"

typedef int token_type;
extern char lex_error;

char* tokenStringify(token_type);

token_type getToken(FILE*);

#endif