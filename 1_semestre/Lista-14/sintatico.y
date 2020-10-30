%{

#include <stdio.h>
#include<string.h>
#include"custom_print.h"
extern int yylex();
extern char* yytext;
void yyerror(char *s);

extern int colunas;

%}

/* declare tokens */
%token ADD
%token SUB

%token MUL
%token DIV

%token POW
%token MOD

%token SEN
%token COS
%token TAN
%token ABS

%token LPAREN
%token RPAREN

%token NUM
%token REAL
%token VAR

%token MISTERY
%token EOL
%token END_OF_FILE

%start calclist

%%

calclist: exp1 EOL 			{ myprintf("EXPRESSAO CORRETA"); return 0; }
		| exp1 END_OF_FILE  { myprintf("EXPRESSAO CORRETA"); return -1; }
;

exp1: exp2			{ }
	| exp1 ADD exp2 { }
	| exp1 SUB exp2 { }
;

exp2: exp3			{ }
	| exp2 MUL exp3 { }
	| exp2 DIV exp3 { }
	| exp2 MOD exp3 { }
;
exp3: exp4			{ }
	| exp3 POW exp4 { }
	| ADD exp4		{ }
	| SUB exp4		{ }
;
exp4: exp5			{ }
	| SEN LPAREN exp1 RPAREN { }
	| COS LPAREN exp1 RPAREN { }
	| TAN LPAREN exp1 RPAREN { }
	| ABS LPAREN exp1 RPAREN { }
;
exp5: term		{ }
	| LPAREN exp1 RPAREN { }
;

term: NUM	{ }
	| REAL	{ }
	| VAR	{ }
;

%%

void yyerror(char *s)
{
	colunas = colunas - strlen(yytext) + 1;
	if(*yytext == '\n' || *yytext == EOF){
		myprintf("A expressao terminou de forma inesperada.");
	}else if(yychar == MISTERY){
		myprintf("Caractere(s) invalido(s) -> [%s", yytext);
	}else{
		myprintf("Erro de sintaxe na coluna [%d]: %s", colunas, yytext);
	}
}

int main(int argc, char **argv)
{
	int fim = 0;
    while(fim != -1){

		int parse = yyparse();
		if(yychar == MISTERY){

			int token = 0;
			while(token!=EOL){
				if(token == MISTERY){
					printf(",%s", yytext);
				}else if(token == END_OF_FILE){
					fim = -1;
					break;
				}
				token = yylex();
			}
			printf("]");

		}else if(parse != 0 && *yytext != '\n'){

			int token = 0;
			while(token != EOL){
				if(token == END_OF_FILE){
					fim = -1;
					break;
				}
				token = yylex();
			}

		}
		colunas = 0;

	}
    return 0;
}
