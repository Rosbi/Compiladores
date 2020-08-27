#ifndef CONST_H
#define CONST_H

#include<stdio.h>
#include<stdint.h>

#define symbol_quantity 27
#define state_quantity 27

typedef int token_type;
enum tokens{
	TOKEN_ERROR,
	IF,
	THEN,
	ELSE,
	BEGIN,
	END,
	PRINT,
	SEMICOLON,
	NUMBER,
	EQUALS,
	WHITESPACE,
	NEWLINE
};

char* tokenStringify(token_type);

token_type getToken(FILE*);

#endif