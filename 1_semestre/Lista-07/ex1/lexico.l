/* Nao usar a biblioteca do flex*/
%option noyywrap

%{
int chars = 0;
int words = 0;
int lines = 1;
%}

%%

"+"   					{printf("%s\n", yytext); chars++;}
"-"						{printf("%s\n", yytext); chars++;}
[a-z][a-z0-9]*			{printf("%s\n", yytext); words++; chars+=strlen(yytext);}
[0-9]+					{printf("%s\n", yytext); words++; chars+=strlen(yytext);}
[0-9]+"e"[+-]?[0-9]+	{printf("%s\n", yytext); words++; chars+=strlen(yytext);}
[\n]					{lines++;}
.						{printf("ERRO\n"); chars++;}

%%

main(int argc, char **argv)
{
	yylex();
	return 0;
}
