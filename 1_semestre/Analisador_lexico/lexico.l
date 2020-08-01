/* Nao usar a biblioteca do flex*/
%option noyywrap

%{
#include<stdarg.h>
int total_lines = 1;
int line_chars = 0;
char *aux;
void myprint_first(const char *format, ...);
void my_next_print(const char *format, ...);
void (*myprintf)(const char *format, ...) = myprint_first;
void myprint_first(const char *format, ...){
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
	myprintf = my_next_print;
}
void my_next_print(const char *format, ...){
	va_list args;
	va_start(args, format);
	printf("\n");
	vprintf(format, args);
	va_end(args);
}
int charFrequency(const char *str, char ch){
	int count=0;
	for(int i=0;i<strlen(str);i++){
		if(str[i]==ch)
			count++;
	}
	return count;
}
%}

%%

	/* keywords */
"void"		{myprintf("VOID");line_chars+=4;}
"int"		{myprintf("INT");line_chars+=3;}
"char"		{myprintf("CHAR");line_chars+=4;}
"return"	{myprintf("RETURN");line_chars+=6;}
"break"		{myprintf("BREAK");line_chars+=5;}
"switch"	{myprintf("SWITCH");line_chars+=6;}
"case"		{myprintf("CASE");line_chars+=4;}
"default"	{myprintf("DEFAULT");line_chars+=7;}
"do"		{myprintf("DO");line_chars+=2;}
"while"		{myprintf("WHILE");line_chars+=5;}
"for"		{myprintf("FOR");line_chars+=3;}
"if"		{myprintf("IF");line_chars+=2;}
"else"		{myprintf("ELSE");line_chars+=4;}
"typedef"	{myprintf("TYPEDEF");line_chars+=7;}
"struct"	{myprintf("STRUCT");line_chars+=6;}

	/* operators */
"+"		{myprintf("PLUS");			line_chars+=1;}
"-"		{myprintf("MINUS");			line_chars+=1;}
"*"		{myprintf("MULTIPLY");		line_chars+=1;}
"/"		{myprintf("DIV");			line_chars+=1;}
"%"		{myprintf("REMAINDER");		line_chars+=1;}
"++"	{myprintf("INC");			line_chars+=2;}
"--"	{myprintf("DEC");			line_chars+=2;}
"&"		{myprintf("BITWISE_AND");	line_chars+=1;}
"|"		{myprintf("BITWISE_OR");	line_chars+=1;}
"~"		{myprintf("BITWISE_NOT");	line_chars+=1;}
"^"		{myprintf("BITWISE_XOR");	line_chars+=1;}
"!"		{myprintf("NOT");			line_chars+=1;}
"&&"	{myprintf("LOGICAL_AND");	line_chars+=2;}
"||"	{myprintf("LOGICAL_OR");	line_chars+=2;}
"=="	{myprintf("EQUAL");			line_chars+=2;}
"!="	{myprintf("NOT_EQUAL");		line_chars+=2;}
"<"		{myprintf("LESS_THAN");		line_chars+=1;}
">"		{myprintf("GREATER_THAN");	line_chars+=1;}
"<="	{myprintf("LESS_EQUAL");	line_chars+=2;}
">="	{myprintf("GREATER_EQUAL");	line_chars+=2;}
">>"	{myprintf("R_SHIFT");		line_chars+=2;}
"<<"	{myprintf("L_SHIFT");		line_chars+=2;}
"="		{myprintf("ASSIGN");		line_chars+=1;}
"+="	{myprintf("ADD_ASSIGN");	line_chars+=2;}
"-="	{myprintf("MINUS_ASSIGN");	line_chars+=2;}
";"		{myprintf("SEMICOLON");		line_chars+=1;}
","		{myprintf("COMMA");			line_chars+=1;}
":"		{myprintf("COLON");			line_chars+=1;}
"("		{myprintf("L_PAREN");		line_chars+=1;}
")"		{myprintf("R_PAREN");		line_chars+=1;}
"{"		{myprintf("L_CURLY_BRACKET");	line_chars+=1;}
"}"		{myprintf("R_CURLY_BRACKET");	line_chars+=1;}
"["		{myprintf("L_SQUARE_BRACKET");	line_chars+=1;}
"]"		{myprintf("R_SQUARE_BRACKET");	line_chars+=1;}
"?"		{myprintf("TERNARY_CONDITION");	line_chars+=1;}
"#"		{myprintf("NUMBER_SIGN");	line_chars+=1;}
"->"	{myprintf("POINTER");		line_chars+=2;}

	/* funções */
"printf"	{myprintf("PRINTF");	line_chars+=6;}
"scanf"		{myprintf("SCANF");		line_chars+=5;}
"define"	{myprintf("DEFINE");	line_chars+=6;}
"exit"		{myprintf("EXIT");		line_chars+=4;}

	/* variables */
"0"("x"|"X")([0-9]|[A-F]|[a-f])+	{myprintf("NUM_HEXA(%s)", yytext);		line_chars+=strlen(yytext);}
"0"[0-9]+							{myprintf("NUM_OCTAL(%s)", yytext);		line_chars+=strlen(yytext);}
[0-9]+								{myprintf("NUM_INTEGER(%s)", yytext);	line_chars+=strlen(yytext);}
"\'""\\"?."\'"						{myprintf("CHARACTER(");strlen(yytext)==3 ? printf("%c)",yytext[1]) : printf("%c%c)",yytext[1],yytext[2]);line_chars+=strlen(yytext);}
"\"".*"\""							{line_chars+=strlen(yytext);yytext[strlen(yytext)-1]='\0';aux=&yytext[1];myprintf("STRING(%s)", aux);}
	/*[_a-zA-z][_a-zA-Z0-9]*	{printf("IDENTIFIER(%s)\n", yytext);	line_chars+=strlen(yytext);}*/
([a-z]|"_"|[A-Z])([a-z]|"_"|[A-Z]|[0-9])*	{myprintf("IDENTIFIER(%s)", yytext);	line_chars+=strlen(yytext);}

	/* comments */
"//".*[\n]		{total_lines++;line_chars=0;}
("/*"([^*]|[\n]|("*"+([^*/]|[\n])))*"*"+"/")	{total_lines+=charFrequency(yytext,'\n');}
("/*"([^*]|[\n]|("*"+([^*/]|[\n])))*)	{myprintf("error:lexical:%d:%d: unterminated comment", total_lines, line_chars);}	

	/* misc */
[ \r\t\f]	{line_chars++;}
[\n]		{total_lines++;line_chars=0;}
.			{line_chars++;myprintf("error:lexical:%d:%d: %s\n", total_lines, line_chars, yytext);}

%%

int main(int argc, char **argv)
{
	yylex();
}
