#ifndef CONST_H
#define CONST_H

#include<stdio.h>
#include<stdint.h>
#include"globals.h"

typedef int token_type;
extern char lex_error;
extern char last_read_token[63];

char* tokenStringify(token_type);

token_type getToken(FILE*);

#endif