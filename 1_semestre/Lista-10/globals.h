#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#include<stdio.h>
#include"stack.h"

//Esses valores DEVEM ser inicializados na main
extern FILE* file_in;
extern Stack stck;

// extern token_type s_token;

enum tokens{
    //Tokens de controle
	TOKEN_EOF,
	TOKEN_ERROR,
	WHITESPACE,
	NEWLINE,

    //Terminais e seus limitadores
	terminal_start,
	PLUS_SIGN,
	MULT_SIGN,
	LPAREN,
	RPAREN,
	ID,
	DOLLAR,
	terminal_end,

    //Não terminais e seus limitadores
	nonterminal_start,
	S_nt,
    E_nt,
    E1_nt,
    T_nt,
    T1_nt,
    F_nt,
	nonterminal_end
};

#endif