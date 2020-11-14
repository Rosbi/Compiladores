%{

#include <stdio.h>
#include<string.h>
#include"custom_print.h"
extern int yylex();
extern char* yytext;
void yyerror(char *s);

extern int colunas;
extern int linhas;

%}

/* declare tokens */
%token VOID_T
%token INT_T
%token CHAR_T
%token RETURN_T
%token DO_T
%token WHILE_T
%token FOR_T
%token IF_T
%token ELSE_T
%token ADD
%token SUB
%token ASTERISK
%token DIV
%token MOD
%token INC
%token DEC
%token AMPERSAND
%token BIT_OR
%token BIT_NOT
%token BIT_XOR
%token LOG_AND
%token LOG_OR
%token LOG_NOT
%token EQUALS
%token NOT_EQUALS
%token LESS
%token GREAT
%token LEQ
%token GEQ
%token RSHIFT
%token LSHIFT
%token ASSIGN
%token ADD_ASSIGN
%token SUB_ASSIGN
%token SEMICOLON
%token COMMA
%token COLON
%token LPAREN
%token RPAREN
%token LCBRACK
%token RCBRACK
%token LBRACK
%token RBRACK
%token QUEST_MARK
%token NUMBER_SIGN
%token DEFINE
%token PRINTF_T
%token SCANF_T
%token EXIT_T
%token NUM_HEXA
%token NUM_OCTA
%token NUM_INT
%token CHARACTER
%token STRING
%token IDENTIFIER
%token LINE_COMMENT
%token BLOCK_COMMENT
%token UNTERMINATED_COMMENT

%start programa

%%

programa: programa1 programa EOL	{}
		| programa1					{}
;
programa1: declaracoes	{}
		 | funcao		{}
;

declaracoes: NUMBER_SIGN DEFINE IDENTIFIER expressao	{}
		   | declaracao_var		{}
		   | declaracao_prot	{}
;

declaracao_var: tipo declaracao_var1	{}
;
declaracao_var1: pointer IDENTIFIER array ASSIGN exp_atr declaracao_var_fim	{}
;
declaracao_var_fim: COMMA declaracao_var1	{}
				  | /* epsilon */			{}
;

declaracao_prot: tipo pointer IDENTIFIER parametros SEMICOLON	{}
;

funcao: tipo pointer IDENTIFIER parametros LCBRACK func_dec_var comandos RCBRACK	{}
;
func_dec_var: declaracao_var func_dec_var	{}
			| /* epsilon */					{}
;

pointer: ASTERISK pointer	{}
	   | /* epsilon */		{}
;
array: LBRACK expressao RBRACK array	{}
	 | /* epsilon */					{}
;

%%

void yyerror(char *s)
{
	colunas = colunas - strlen(yytext) + 1;
	myprintf("A expressao terminou de forma inesperada.");
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
