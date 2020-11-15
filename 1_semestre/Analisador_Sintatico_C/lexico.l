/* Nao usar a biblioteca do flex*/
%option noyywrap

%{

#include<sintatico.tab.h>
#include<string.h>
int colunas = 1;
int linhas = 1;

int charFrequency(const char *str, char ch, int* col){
	int count=0;
	for(int i=0;i<strlen(str);i++){
		*col += 1;
		if(str[i]==ch){
			count++;
			*col = 1;
		}
	}
	return count;
}

%}

%%

	/* keywords */
"void"		{ colunas+=4; return VOID_T; }
"int"		{ colunas+=3; return INT_T; }
"char"		{ colunas+=4; return CHAR_T; }
"return"	{ colunas+=6; return RETURN_T; }
	/* // "break"		{ return ; }
	// "switch"	{ return ; }
	// "case"		{ return ; }
	// "default"	{ return ; } */
"do"		{ colunas+=2; return DO_T; }
"while"		{ colunas+=5; return WHILE_T; }
"for"		{ colunas+=3; return FOR_T; }
"if"		{ colunas+=2; return IF_T; }
"else"		{ colunas+=4; return ELSE_T; }
	/* // "typedef"	{ return ; }
	// "struct"	{ return ; }*/

	/* operators */
		/*matematicos*/
"+"		{ colunas+=1; return ADD; }
"-"		{ colunas+=1; return SUB; }
"*"		{ colunas+=1; return ASTERISK; }
"/"		{ colunas+=1; return DIV; }
"%"		{ colunas+=1; return MOD; }
"++"	{ colunas+=2; return INC; }
"--"	{ colunas+=2; return DEC; }
		/*bitwise*/
"&"		{ colunas+=1; return AMPERSAND; }
"|"		{ colunas+=1; return BIT_OR; }
"~"		{ colunas+=1; return BIT_NOT; }
"^"		{ colunas+=1; return BIT_XOR; }
		/*logicos*/
"&&"	{ colunas+=2; return LOG_AND; }
"||"	{ colunas+=2; return LOG_OR; }
"!"		{ colunas+=1; return LOG_NOT; }
		/*comparacao*/
"=="	{ colunas+=2; return EQUALS; }
"!="	{ colunas+=2; return NOT_EQUALS; }
"<"		{ colunas+=1; return LESS; }
">"		{ colunas+=1; return GREAT; }
"<="	{ colunas+=2; return LEQ; }
">="	{ colunas+=2; return GEQ; }
		/*shift*/
">>"	{ colunas+=2; return RSHIFT; }
"<<"	{ colunas+=2; return LSHIFT; }
		/*atribuicao*/
"="		{ colunas+=1; return ASSIGN; }
"+="	{ colunas+=2; return ADD_ASSIGN; }
"-="	{ colunas+=2; return SUB_ASSIGN; }
		/*misc*/
";"		{ colunas+=1; return SEMICOLON; }
","		{ colunas+=1; return COMMA; }
":"		{ colunas+=1; return COLON; }
"("		{ colunas+=1; return LPAREN; }
")"		{ colunas+=1; return RPAREN; }
"{"		{ colunas+=1; return LCBRACK; }
"}"		{ colunas+=1; return RCBRACK; }
"["		{ colunas+=1; return LBRACK; }
"]"		{ colunas+=1; return RBRACK; }
"?"		{ colunas+=1; return QUEST_MARK; }
	/* // "->"	{ return ; } */

	/* preprocessador */
"#"			{ colunas+=1; return NUMBER_SIGN; }
"define"	{ colunas+=6; return DEFINE; }

	/* funções */
"printf"	{ colunas+=6; return PRINTF_T; }
"scanf"		{ colunas+=5; return SCANF_T; }
"exit"		{ colunas+=4; return EXIT_T; }

	/* variables */
"0"("x"|"X")([0-9]|[A-F]|[a-f])+	{ colunas+=strlen(yytext); return NUM_HEXA; }
"0"[0-9]+							{ colunas+=strlen(yytext); return NUM_OCTA; }
[0-9]+								{ colunas+=strlen(yytext); return NUM_INT; }
"\'""\\"?."\'"						{ colunas+=strlen(yytext); return CHARACTER; }
\"(\\.|[^"\\])*\"					{ colunas+=strlen(yytext); return STRING; }
	/*[_a-zA-z][_a-zA-Z0-9]*	{printf("IDENTIFIER(%s)\n", yytext);	line_chars+=strlen(yytext);}*/
([a-z]|"_"|[A-Z])([a-z]|"_"|[A-Z]|[0-9])*	{ colunas+=strlen(yytext); return IDENTIFIER; }

	/* comments */
"//".*[\n]		{ linhas++; colunas=1; }
"//".*			{ return END_OF_FILE; }
("/*"([^*]|[\n]|("*"+([^*/]|[\n])))*"*"+"/")	{ linhas+=charFrequency(yytext, '\n', &colunas); }
("/*"([^*]|[\n]|("*"+([^*/]|[\n])))*)			{ return UNTERMINATED_COMMENT; }

	/* misc */
[ \r\t\f]	{ colunas++; }
[\n]		{ linhas++; colunas = 1; }
<<EOF>>		{ return END_OF_FILE; }
.			{ colunas++; return UNKNOWN_CHAR; }

%%
