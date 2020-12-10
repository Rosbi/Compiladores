%{

#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include"custom_print.h"
#include"hashTable.h"
extern int yylex();
extern char* yytext;
void yyerror(char *s);
void insere_tabela(HashTable tabela_simbolos, char *id);

bool semantic_error;
int linha = 1;
int tipo = 0;
HashTable tabela_simbolos = NULL;

%}

%union{
	char* string;
}

/* declare tokens */
%token INT_T
%token FLOAT_T
%token CHAR_T
%token IDENTIFIER

%token COMMA
%token DOLLAR

%token MISTERY
%token EOL
%token END_OF_FILE

/* declare types */
%type <string> IDENTIFIER

%start s

%%

s: d d1 DOLLAR EOL			{ return  0; }
 | d d1 DOLLAR END_OF_FILE	{ return -1; }
;

d1: d d1		{}
  | /* empty */	{}
;

d: t i	{}
;

t: INT_T	{ tipo = INT_T; }
 | FLOAT_T	{ tipo = FLOAT_T; }
 | CHAR_T	{ tipo = CHAR_T; }
;

i: IDENTIFIER			{ insere_tabela(tabela_simbolos, $1); }
 | i COMMA IDENTIFIER	{ insere_tabela(tabela_simbolos, $3); }
;

%%

void yyerror(char *s)
{
	if(yychar == MISTERY){
		myprintf("Erro lexico encontrado: '%s'", yytext);
	}else{
		myprintf("Erro sintatico encontrado: '%s'", yytext);
	}
}

int main(int argc, char **argv)
{
	int fim = 0;

	while(fim == 0){
		tabela_simbolos = criaTabela(211);
		semantic_error = false;
		fim = yyparse();
		if(!semantic_error)
			{ myprintf("%d: All Identifiers on Hash.", linha); }
		linha++;
		hashtableFinalizar(tabela_simbolos);
	}

    return 0;
}

void insere_tabela(HashTable tabela_simbolos, char *id){
	if(!existeChave(tabela_simbolos, id)){
		int *tipop = malloc(sizeof(int));
		*tipop = tipo;
		insereRegistro(tabela_simbolos, id, tipop);
	}else{
		semantic_error = true;
		int *tipop = getPrimeiroRegistro(tabela_simbolos, id);
		if(*tipop != tipo){
			myprintf("%d: redefinition of identifier '%s'", linha, id);
		}else{
			myprintf("%d: identifier '%s' already declared", linha, id);
		}
	}
}
