#ifndef PARSER_H
#define PARSER_H

#include<stdbool.h>
#include<stdio.h>
#include"lex_analyser.h"

bool S();
bool E();
bool E1();
bool T();
bool T1();
bool F();

bool error();
bool advance(FILE* file_in);
bool eat(token_type t);

#endif