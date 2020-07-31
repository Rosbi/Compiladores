/* Nao usar a biblioteca do flex*/
%option noyywrap

%{
int chars = 0;
int words = 0;
int lines = 1;
%}

%%

"if"   					{printf("%s IF\n", yytext);    chars+=2;}
[a-z][a-z0-9]*			{printf("%s ID\n", yytext);    words++; chars+=strlen(yytext);}
"."[0-9]+				{printf("%s REAL\n", yytext);  words++; chars+=strlen(yytext);}
[0-9]+					{printf("%s NUM\n", yytext);   words++; chars+=strlen(yytext);}
[0-9]+"."[0-9]*			{printf("%s REAL\n", yytext);  words++; chars+=strlen(yytext);}
"--"[a-z]*[\n]			{fwrite(yytext, sizeof(char), strlen(yytext)-1, stdout);printf(" comment\n"); words++; chars+=strlen(yytext); lines++;}
" "|[\t]				{printf("whitespace\n");       chars++;}
[\n]					{lines++;}
.						{printf("%s error\n", yytext); chars++;}

%%

int main(int argc, char **argv)
{
	yylex();
	return 0;
}
