/* Nao usar a biblioteca do flex*/
%option noyywrap

%{
int total_lines = 1;
int blank_lines = 0;
int comment_lines = 0;
int content_lines = 0;
int semi_colons = 0;
int preprocessor = 0;
int total_lines_f = 1;
int blank_lines_f = 0;
int comment_lines_f = 0;
int content_lines_f = 0;
int semi_colons_f = 0;
int preprocessor_f = 0;
int aux;
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

[ \t\r\f]*("#include"|"#define").*\n	{total_lines_f++;preprocessor_f++;content_lines_f++;semi_colons_f+=charFrequency(yytext, ';');}
[ \t\r\f]*[\n]							{total_lines_f++;blank_lines_f++;}
[ \t\r\f]*"//".*[\n]					{total_lines_f++;comment_lines_f++;semi_colons_f+=charFrequency(yytext, ';');}
[ \t\r\f]*("/*"([^*]|[\n]|("*"+([^*/]|[\n])))*"*"+"/").*[\n]	{aux=charFrequency(yytext, '\n');total_lines_f+=aux;comment_lines_f+=aux;semi_colons_f+=charFrequency(yytext, ';');}
.*[\n]									{total_lines_f++;content_lines_f++;semi_colons_f+=charFrequency(yytext, ';');}

%%

int main(int argc, char **argv)
{
	FILE* f;
	printf(" total    blank lines w/   nb, nc    semi- preproc. file\n");
	printf(" lines    lines comments    lines   colons  direct.\n");
	printf("------+--------+--------+--------+--------+--------+----\n");
	
	for(int i=1;i<argc;i++){
		f = fopen(argv[i], "r");
		yyset_in(f);
		yylex();

		printf("%6d %8d %8d %8d %8d %8d %s\n",total_lines_f,blank_lines_f,comment_lines_f,content_lines_f,semi_colons_f,preprocessor_f, argv[i]);
		fclose(f);

		total_lines += total_lines_f;
		blank_lines += blank_lines_f;
		comment_lines += comment_lines_f;
		content_lines += content_lines_f;
		semi_colons += semi_colons_f;
		preprocessor += preprocessor_f;
		total_lines_f = 1;
		blank_lines_f = 0;
		comment_lines_f = 0;
		content_lines_f = 0;
		semi_colons_f = 0;
		preprocessor_f = 0;
	}
}
