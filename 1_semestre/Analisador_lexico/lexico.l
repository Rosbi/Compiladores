/* Nao usar a biblioteca do flex*/
%option noyywrap

%{
int total_lines = 1;
int line_chars = 0;
int charFrequency(const char* str, char ch){
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
"void"		{printf("VOID\n");line_chars+=4;}
"int"		{printf("INT\n");line_chars+=3;}
"char"		{printf("CHAR\n");line_chars+=4;}
"return"	{printf("RETURN\n");line_chars+=6;}
"break"		{printf("BREAK\n");line_chars+=5;}
"switch"	{printf("SWITCH\n");line_chars+=6;}
"case"		{printf("CASE\n");line_chars+=4;}
"default"	{printf("DEFAULT\n");line_chars+=7;}
"do"		{printf("DO\n");line_chars+=2;}
"while"		{printf("WHILE\n");line_chars+=5;}
"for"		{printf("FOR\n");line_chars+=3;}
"if"		{printf("IF\n");line_chars+=2;}
"else"		{printf("ELSE\n");line_chars+=4;}
"typedef"	{printf("TYPEDEF\n");line_chars+=7;}
"struct"	{printf("STRUCT\n");line_chars+=6;}

	/* operators */
"+"		{printf("PLUS\n");			line_chars+=1;}
"-"		{printf("MINUS\n");			line_chars+=1;}
"*"		{printf("MULTIPLY\n");		line_chars+=1;}
"/"		{printf("DIV\n");			line_chars+=1;}
"%"		{printf("REMAINDER\n");		line_chars+=1;}
"++"	{printf("INC\n");			line_chars+=2;}
"--"	{printf("DEC\n");			line_chars+=2;}
"&"		{printf("BITWISE_AND\n");	line_chars+=1;}
"|"		{printf("BITWISE_OR\n");	line_chars+=1;}
"~"		{printf("BITWISE_NOT\n");	line_chars+=1;}
"^"		{printf("BITWISE_XOR\n");	line_chars+=1;}
"!"		{printf("NOT\n");			line_chars+=1;}
"&&"	{printf("LOGICAL_AND\n");	line_chars+=2;}
"||"	{printf("LOGICAL_OR\n");	line_chars+=2;}
"=="	{printf("EQUAL\n");			line_chars+=2;}
"!="	{printf("NOT_EQUAL\n");		line_chars+=2;}
"<"		{printf("LESS_THAN\n");		line_chars+=1;}
">"		{printf("GREATER_THAN\n");	line_chars+=1;}
"<="	{printf("LESS_EQUAL\n");	line_chars+=2;}
">="	{printf("GREATER_EQUAL\n");	line_chars+=2;}
">>"	{printf("R_SHIFT\n");		line_chars+=2;}
"<<"	{printf("L_SHIFT\n");		line_chars+=2;}
"="		{printf("ASSIGN\n");		line_chars+=1;}
"+="	{printf("ADD_ASSIGN\n");	line_chars+=2;}
"-="	{printf("MINUS_ASSIGN\n");	line_chars+=2;}
";"		{printf("SEMICOLON\n");		line_chars+=1;}
","		{printf("COMMA\n");			line_chars+=1;}
":"		{printf("COLON\n");			line_chars+=1;}
"("		{printf("L_PAREN\n");		line_chars+=1;}
")"		{printf("R_PAREN\n");		line_chars+=1;}
"{"		{printf("L_CURLY_BRACKET\n");	line_chars+=1;}
"}"		{printf("R_CURLY_BRACKET\n");	line_chars+=1;}
"["		{printf("L_SQUARE_BRACKET\n");	line_chars+=1;}
"]"		{printf("R_SQUARE_BRACKET\n");	line_chars+=1;}
"?"		{printf("TERNARY_CONDITION\n");	line_chars+=1;}
"#"		{printf("NUMBER_SIGN\n");	line_chars+=1;}
"->"	{printf("POINTER\n");		line_chars+=2;}

	/* funções */
"printf"	{printf("PRINTF\n");	line_chars+=6;}
"scanf"		{printf("SCANF\n");		line_chars+=5;}
"define"	{printf("DEFINE\n");	line_chars+=6;}
"exit"		{printf("EXIT\n");		line_chars+=4;}

	/* variables */
"0x"[0-9]+				{printf("NUM_HEXA(%s)\n", yytext);		line_chars+=strlen(yytext);}
"0"[0-9]+				{printf("NUM_OCTAL(%s)\n", yytext);		line_chars+=strlen(yytext);}
[0-9]+					{printf("NUM_INTEGER(%s)\n", yytext);	line_chars+=strlen(yytext);}
"\'""\\"?."\'"			{printf("CHARACTER(");strlen(yytext)==3 ? printf("%c)\n",yytext[1]) : printf("%c%c)\n",yytext[1],yytext[2]);line_chars+=strlen(yytext);}
"\"".*"\""				{printf("STRING(%s)\n", yytext);		line_chars+=strlen(yytext);}
[_a-zA-z][_a-zA-Z0-9]*	{printf("IDENTIFIER(%s)\n", yytext);	line_chars+=strlen(yytext);}

	/* comments */
"//".*[\n]					{total_lines++;line_chars=0;}
("/*"([^*]|[\n]|("*"+([^*/]|[\n])))*"*"+"/")	{total_lines+=charFrequency(yytext,'\n');}

	/* misc */
[ \r\t\f]	{line_chars++;}
[\n]		{total_lines++;line_chars=0;}
.			{line_chars++;printf("error:lexical:%d:%d: %s\n", total_lines, line_chars, yytext);}

%%

int main(int argc, char **argv)
{
	yylex();
}
