#ifndef CONST_H
#define CONST_H

#include<stdio.h>
#include<stdint.h>

typedef int token_type;
enum tokens{
	TOKEN_ERROR,
	PLUS_SIGN,
	MULT_SIGN,
	LPAREN,
	RPAREN,
	ID,
	DOLLAR,
	WHITESPACE,
	NEWLINE
};

char* tokenStringify(token_type);

token_type getToken(FILE*);

#endif