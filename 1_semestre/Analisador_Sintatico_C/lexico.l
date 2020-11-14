/* Nao usar a biblioteca do flex*/
%option noyywrap

%{
	
int colunas = 0;
int linhas = 1;

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
"void"		{ return VOID_T; }
"int"		{ return INT_T; }
"char"		{ return CHAR_T; }
"return"	{ return RETURN_T; }
	// "break"		{ return ; }
	// "switch"	{ return ; }
	// "case"		{ return ; }
	// "default"	{ return ; }
"do"		{ return DO_T; }
"while"		{ return WHILE_T; }
"for"		{ return FOR_T; }
"if"		{ return IF_T; }
"else"		{ return ELSE_T; }
	// "typedef"	{ return ; }
	// "struct"	{ return ; }

	/* operators */
	// matematicos
"+"		{ return ADD; }
"-"		{ return SUB; }
"*"		{ return ASTERISK; }
"/"		{ return DIV; }
"%"		{ return MOD; }
"++"	{ return INC; }
"--"	{ return DEC; }
	// bitwise
"&"		{ return AMPERSAND; }
"|"		{ return BIT_OR; }
"~"		{ return BIT_NOT; }
"^"		{ return BIT_XOR; }
	// logicos
"&&"	{ return LOG_AND; }
"||"	{ return LOG_OR; }
"!"		{ return LOG_NOT; }
	// comparacao
"=="	{ return EQUALS; }
"!="	{ return NOT_EQUALS; }
"<"		{ return LESS; }
">"		{ return GREAT; }
"<="	{ return LEQ; }
">="	{ return GEQ; }
	// shift
">>"	{ return RSHIFT; }
"<<"	{ return LSHIFT; }
	// atribuicao
"="		{ return ASSIGN; }
"+="	{ return ADD_ASSIGN; }
"-="	{ return SUB_ASSIGN; }
	//misc
";"		{ return SEMICOLON; }
","		{ return COMMA; }
":"		{ return COLON; }
"("		{ return LPAREN; }
")"		{ return RPAREN; }
"{"		{ return LCBRACK; }
"}"		{ return RCBRACK; }
"["		{ return LBRACK; }
"]"		{ return RBRACK; }
"?"		{ return QUEST_MARK; }
	// "->"	{ return ; }

	/* preprocessador */
"#"			{ return NUMBER_SIGN; }
"define"	{ return DEFINE; }

	/* funções */
"printf"	{ return PRINTF_T; }
"scanf"		{ return SCANF_T; }
"exit"		{ return EXIT_T; }

	/* variables */
"0"("x"|"X")([0-9]|[A-F]|[a-f])+	{ return NUM_HEXA; }
"0"[0-9]+							{ return NUM_OCTA; }
[0-9]+								{ return NUM_INT; }
"\'""\\"?."\'"						{ return CHARACTER; }
\"(\\.|[^"\\])*\"					{ return STRING; }
	/*[_a-zA-z][_a-zA-Z0-9]*	{printf("IDENTIFIER(%s)\n", yytext);	line_chars+=strlen(yytext);}*/
([a-z]|"_"|[A-Z])([a-z]|"_"|[A-Z]|[0-9])*	{ return IDENTIFIER; }

	/* comments */
"//".*[\n]		{ return LINE_COMMENT; }
("/*"([^*]|[\n]|("*"+([^*/]|[\n])))*"*"+"/")	{ return BLOCK_COMMENT; }
("/*"([^*]|[\n]|("*"+([^*/]|[\n])))*)			{ return UNTERMINATED_COMMENT; }

	/* misc */
[ \r\t\f]	{ colunas++; }
[\n]		{ linhas++; colunas = 0; }
.			{ return ; }

%%
