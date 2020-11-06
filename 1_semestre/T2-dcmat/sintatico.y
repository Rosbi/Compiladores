%{

#include <stdio.h>
#include<string.h>
#include<stdbool.h>
#include"abstractSyntaxTree.h"
#include"algebra.h"
#include"calculus.h"
extern int yylex();
extern char* yytext;
void yyerror(char *s);
void about();

bool quit = false;
int function_to_be_called=-1;
int aux_int=0;
float aux_float[] = {0.0, 0.0};
void* aux_ptr=NULL;

enum functions
{ 
	fn_SHOW_SETTINGS,
	fn_RESET_SETTINGS,
	fn_SET_H_VIEW,
	fn_SET_V_VIEW,
	fn_SET_AXIS_ON,
	fn_SET_AXIS_OFF,
	fn_PLOT,
	fn_SET_INTEGRAL_STEPS,
	fn_INTEGRATE,
	fn_MATRIX,
	fn_SHOW_MATRIX,
	fn_SOLVE_DETERMINANT,
	fn_SOLVE_LINEAR_SYSTEM,
	fn_ABOUT 
};

%}

%union{
	int integer;
	float real;
	void* ast;
}

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

%token CM_SHOW_SETTINGS
%token CM_RESET_SETTINGS
%token CM_QUIT
%token CM_SET
%token CM_H_VIEW
%token CM_V_VIEW
%token CM_AXIS_ON
%token CM_AXIS_OFF
%token CM_PLOT
%token CM_INTEGRAL_STEPS
%token CM_INTEGRATE
%token CM_MATRIX
%token CM_SHOW_MATRIX
%token CM_SOLVE_DETERMINANT
%token CM_SOLVE_LINEAR_SYSTEM
%token CM_ABOUT
%token SEMICOLON
%token COLON

%token MISTERY
%token EOL
%token END_OF_FILE

/* declare types */
%type <real> REAL
%type <real> real_num
%type <integer> VAR
%type <integer> NUM
%type <ast> expression
%type <ast> exp2
%type <ast> exp3
%type <ast> exp4
%type <ast> exp5
%type <ast> term

%start start

%%

start: expression EOL		 { RpnWalk($1);printf("\n");deleteTree($1);return 0; }
	 | comando SEMICOLON EOL { return 0; }
	 | CM_QUIT EOL			 { quit=true; return 1; }
	 | END_OF_FILE			 { return 0; }
;

comando: CM_SHOW_SETTINGS 						  { function_to_be_called = fn_SHOW_SETTINGS; }
	   | CM_RESET_SETTINGS 						  { function_to_be_called = fn_RESET_SETTINGS; }
	   | CM_SET CM_H_VIEW real_num COLON real_num { aux_float[0]=$3;aux_float[1]=$5;function_to_be_called=fn_SET_H_VIEW; }
	   | CM_SET CM_V_VIEW real_num COLON real_num { aux_float[0]=$3;aux_float[1]=$5;function_to_be_called=fn_SET_V_VIEW; }
	   | CM_SET CM_AXIS_ON  					  { function_to_be_called = fn_SET_AXIS_ON; }
	   | CM_SET CM_AXIS_OFF  					  { function_to_be_called = fn_SET_AXIS_OFF; }
	   | CM_PLOT 								  { printf("funcao ainda nao implementada ;-;\n"); }
	   | CM_PLOT LPAREN expression RPAREN 		  { printf("funcao ainda nao implementada ;-;\n"); }
	   | CM_SET CM_INTEGRAL_STEPS 				  { printf("funcao ainda nao implementada ;-;\n"); }
	   | CM_INTEGRATE 							  { printf("funcao ainda nao implementada ;-;\n"); }
	   | CM_MATRIX 								  { printf("funcao ainda nao implementada ;-;\n"); }
	   | CM_SHOW_MATRIX 						  { printf("funcao ainda nao implementada ;-;\n"); }
	   | CM_SOLVE_DETERMINANT 					  { printf("funcao ainda nao implementada ;-;\n"); }
	   | CM_SOLVE_LINEAR_SYSTEM 				  { printf("funcao ainda nao implementada ;-;\n"); }
	   | CM_ABOUT 								  { function_to_be_called = fn_ABOUT; }
;

real_num: ADD REAL	{ $$ = $2; }
		| SUB REAL	{ $$ = $2*(-1); }
		| REAL		{ $$ = $1; }

expression: exp2	{ $$ = $1; }
		  | expression ADD exp2 { $$ = nodeNew(ADD, 0.0, $1, $3); }
		  | expression SUB exp2 { $$ = nodeNew(SUB, 0.0, $1, $3); }
;

exp2: exp3			{ $$ = $1; }
	| exp2 MUL exp3 { $$ = nodeNew(MUL, 0.0, $1, $3); }
	| exp2 DIV exp3 { $$ = nodeNew(DIV, 0.0, $1, $3); }
	| exp2 MOD exp3 { $$ = nodeNew(MOD, 0.0, $1, $3); }
;
exp3: exp4			{ $$ = $1; }
	| exp3 POW exp4 { $$ = nodeNew(POW, 0.0, $1, $3); }
	| ADD exp4		{ }
	| SUB exp4		{ }
;
exp4: exp5			{ $$ = $1; }
	| SEN LPAREN expression RPAREN { $$ = nodeNew(SEN, 0.0, $3, NULL); }
	| COS LPAREN expression RPAREN { $$ = nodeNew(COS, 0.0, $3, NULL); }
	| TAN LPAREN expression RPAREN { $$ = nodeNew(TAN, 0.0, $3, NULL); }
	| ABS LPAREN expression RPAREN { $$ = nodeNew(ABS, 0.0, $3, NULL); }
;
exp5: term		{ $$ = $1; }
	| LPAREN expression RPAREN { $$ = $2; }
;
term: NUM	{ $$ = nodeNew(NUM, $1, NULL, NULL); }
	| REAL	{ $$ = nodeNew(REAL, $1, NULL, NULL); }
	| VAR	{ $$ = nodeNew(VAR, 0.0, NULL, NULL); }
;

%%

void yyerror(char *s)
{
	function_to_be_called = -1;
	if(yytext)
		printf("Erro de sintaxe: [%s]\n", yytext);
}

int main(int argc, char **argv)
{
	while(!quit){
		printf("> ");	
		yyparse();
		switch(function_to_be_called){
			case fn_SHOW_SETTINGS:
				showSettings();
				break;
			case fn_RESET_SETTINGS:
				resetSettings();
				break;
			case fn_SET_H_VIEW:
				setHView(aux_float[0], aux_float[1]);
				break;
			case fn_SET_V_VIEW:
				setVView(aux_float[0], aux_float[1]);
				break;
			case fn_SET_AXIS_ON:
				setAxis(true);
				break;
			case fn_SET_AXIS_OFF:
				setAxis(false);
				break;
			case fn_PLOT:

				break;
			case fn_SET_INTEGRAL_STEPS:

				break;
			case fn_INTEGRATE:

				break;
			case fn_MATRIX:

				break;
			case fn_SHOW_MATRIX:

				break;
			case fn_SOLVE_DETERMINANT:

				break;
			case fn_SOLVE_LINEAR_SYSTEM:

				break;
			case fn_ABOUT:
				about();
				break;
		}
		function_to_be_called=-1;
	}

	return 0;
}

void about(){
	printf("+--------------------------------------------+\n");
	printf("|                                            |\n");
	printf("|   201800560051 - Eric Augusto Nascimento   |\n");
	printf("|                                            |\n");
	printf("+--------------------------------------------+\n");
}
