/* Nao usar a biblioteca do flex*/
%option noyywrap

%{
int chars = 0;
int words = 0;
int lines = 1;
%}

%%

"aba"+		{printf("(action 1)\n"); chars+=strlen(yytext); words++;}
"a""b"*"a"	{printf("(action 2)\n"); chars+=strlen(yytext); words++;}
"a"|"b"		{printf("(action 3)\n"); chars++; words++;}

%%

int main(int argc, char **argv)
{
	yylex();
	return 0;
}
