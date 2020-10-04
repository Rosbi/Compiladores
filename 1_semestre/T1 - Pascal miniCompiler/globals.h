#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#include<stdio.h>
#include"stack.h"

//Esses valores DEVEM ser inicializados na main
extern FILE* file_in;
extern Stack stck;

extern int linha;
extern int coluna;

enum tokens{
    //Tokens de controle
	TOKEN_EOF,
	TOKEN_ERROR,
	WHITESPACE,
	NEWLINE,

    //Terminais e seus limitadores
	terminal_start,
	PROGRAM,
	ID,
	SEMICOLON,
	VAR,
	PROCEDURE,
	FUNCTION,
	COLON,
	BEGIN,
	END,
	PERIOD,
	COMMA,
	NUMBER,
	LPAREN,
	RPAREN,
	LBRACKET,
	RBRACKET,
	ATTRIBUTION,
	IF_t,
	THEN,
	ELSE_t,
	WHILE_t,
	DO_t,
	DIFF,
	LESS,
	GREAT,
	LEQ,
	GEQ,
	EQUALS,
	PLUS,
	MINUS,
	MULTIPLY,
	DIVIDE,
	LOG_OR,
	LOG_AND,
	LOG_NOT,
	COMMENT,
	terminal_end,

    //Não terminais e seus limitadores
	nonterminal_start,
	PROGRAMA_nt,
	BLOCO_nt,
	BLOCO1_nt,
	BLOCO_C1_nt,
	BLOCO_C11_nt,
	BLOCO_C2_nt,
	TIPO_nt,
	PARAMETROS_nt,
	PARAMETROS1_nt,
	PARAMETROS11_nt,
	PARAMETROS_C1_nt,
	VARIAVEL1_nt,
	VARIAVEL_C1_nt,
	COMANDO_nt,
	COMANDO0_nt,
	COMANDO1_nt,
	COMANDO2_nt,
	COMANDO_C1_nt,
	COMANDO_C2_nt,
	EXPRESSAO_nt,
	EXPRESSAO1_nt,
	SINAL_nt,
	EXP_SIMPLES_nt,
	EXP_SIMPLES1_nt,
	TERMO_nt,
	TERMO1_nt,
	FATOR_nt,
	FATOR0_nt,
	FATOR_E_nt,
	FATOR_E1_nt,
	nonterminal_end
};

#endif