%{

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"ast_symbols.h"
#include"hashTable.h"
#include"commands.h"
extern int yylex();
extern char* yytext;
void yyerror(char *s);

enum error_list {
	UNDECLARED_SYMBOL,
	REDEFINED_SYMBOL,
	REDECLARED_SYMBOL
};

void printLine(FILE* in, int line_number);
void semanticError(enum error_list erro, void* element);
int identifierInsert(HashTable symbol_table, Symbol* s);
Symbol* identifierLookup(HashTable symbol_table, Symbol *s);

extern int colunas;
extern int linhas;
int g_tipo = 0;
FILE* in_file = NULL;

%}

/* declare types */
%union{
	char* string;
	int integer;
	char charac;
	struct symbol* symbol_union;
	struct array* array_union;
	struct expression* expression_union;
}

%type <string> STRING
%type <string> IDENTIFIER
%type <integer> pointer
%type <integer> tipo
%type <integer> number
%type <integer> NUM_INT
%type <integer> NUM_HEXA
%type <integer> NUM_OCTA
%type <charac> CHARACTER
%type <symbol_union> declaracao_var1
%type <array_union> array
%type <expression_union> expressao
%type <expression_union> exp_atr
%type <expression_union> exp_cond
%type <expression_union> exp_log_or
%type <expression_union> exp_log_and
%type <expression_union> exp_or
%type <expression_union> exp_xor
%type <expression_union> exp_and
%type <expression_union> exp_equal
%type <expression_union> exp_relat
%type <expression_union> exp_shift
%type <expression_union> exp_add
%type <expression_union> exp_mult
%type <expression_union> exp_cast
%type <expression_union> exp_unary
%type <expression_union> exp_postfix
%type <expression_union> exp_postfix1
%type <expression_union> exp_prim

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
%token UNKNOWN_CHAR
%token END_OF_FILE

	/* unused tokens */
%token BREAK_T
%token SWITCH_T
%token CASE_T
%token DEFAULT_T
%token TYPEDEF_T
%token STRUCT_T
%token POINTER_DEFERENCE

%start programa

%%

programa: programa1 programa END_OF_FILE	{ printf("SUCCESSFUL COMPILATION."); YYACCEPT; }
		| programa1 END_OF_FILE				{ printf("SUCCESSFUL COMPILATION."); YYACCEPT; }
;
programa1: declaracoes	{}
		 | funcao		{}
;

declaracoes: NUMBER_SIGN DEFINE IDENTIFIER expressao	{}
		   | declaracao_var		{}
		   | declaracao_prot	{}
;

declaracao_var: tipo declaracao_var1 SEMICOLON	{}
;
declaracao_var1:
	pointer IDENTIFIER array ASSIGN exp_atr declaracao_var_fim	{
		Symbol *aux = malloc(sizeof(Symbol));

		aux->symbol_type = DECLARACAO_VARIAVEL;
		aux->type.pointers = $1;
		aux->id = $2;
		aux->type.type = g_tipo;
		aux->var.v.array = $3;
		aux->var.v.constant = false;
		aux->line = @2.first_line;
		aux->column = @2.first_column;

		if(!identifierInsert(Program_Table.Global_Symbol_Table, aux)){ YYABORT; };
	}
	| pointer IDENTIFIER array declaracao_var_fim				{
		Symbol *aux = malloc(sizeof(Symbol));

		aux->symbol_type = DECLARACAO_VARIAVEL;
		aux->type.pointers = $1;
		aux->id = $2;
		aux->type.type = g_tipo;
		aux->var.v.array = $3;
		aux->var.v.constant = false;
		aux->line = @2.first_line;
		aux->column = @2.first_column;

		if(!identifierInsert(Program_Table.Global_Symbol_Table, aux)){ YYABORT; };
	}
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

parametros: LPAREN parametros1 RPAREN	{}
;
parametros1: tipo pointer IDENTIFIER array parametros_fim	{}
		   | /* epsilon */		{}
;
parametros_fim: COMMA parametros1	{}
			  | /* epsilon */		{}
;

bloco: LCBRACK comandos RCBRACK	{}
;

comandos: lista_comandos comandos	{}
		| lista_comandos			{}
;

lista_comandos: DO_T bloco WHILE_T LPAREN expressao RPAREN SEMICOLON	{}
			  | IF_T LPAREN expressao RPAREN bloco else_exp				{}
			  | WHILE_T LPAREN expressao RPAREN bloco					{}
			  | FOR_T LPAREN opt_exp SEMICOLON opt_exp SEMICOLON opt_exp RPAREN bloco	{}
			  | PRINTF_T LPAREN STRING printf_exp RPAREN SEMICOLON		{}
			  | SCANF_T LPAREN STRING COMMA AMPERSAND IDENTIFIER RPAREN SEMICOLON		{}
			  | EXIT_T LPAREN expressao RPAREN SEMICOLON				{}
			  | RETURN_T opt_exp SEMICOLON								{}
			  | expressao SEMICOLON										{}
			  | SEMICOLON												{}
			  | bloco													{}
;
printf_exp: COMMA expressao	{}
		  | /* epsilon */	{}
;
else_exp: ELSE_T bloco		{}
		| /* epsilon */		{}
;
opt_exp: expressao		{}
	   | /* epsilon */	{}
;

expressao: exp_atr					{ $$ = $1; }
		 | exp_atr COMMA expressao	{}
;

exp_atr: exp_cond						{ $$ = $1; }
	   | exp_unary ASSIGN exp_atr		{}
	   | exp_unary ADD_ASSIGN exp_atr	{}
	   | exp_unary SUB_ASSIGN exp_atr	{}
;

exp_cond: exp_log_or										{ $$ = $1; }
		| exp_log_or QUEST_MARK expressao COLON exp_cond	{}
;

exp_log_or: exp_log_and						{ $$ = $1; }
		  | exp_log_and LOG_OR exp_log_or	{}
;

exp_log_and: exp_or						{ $$ = $1; }
		   | exp_or LOG_AND exp_log_and	{}
;

exp_or: exp_xor					{ $$ = $1; }
	  | exp_xor BIT_OR exp_or	{}
;

exp_xor: exp_and					{ $$ = $1; }
	   | exp_and BIT_XOR exp_xor	{}
;

exp_and: exp_equal					{ $$ = $1; }
	   | exp_equal AMPERSAND exp_and	{}
;

exp_equal: exp_relat						{ $$ = $1; }
		 | exp_relat EQUALS exp_equal		{}
		 | exp_relat NOT_EQUALS exp_equal	{}
;

exp_relat: exp_shift					{ $$ = $1; }
		 | exp_shift LESS exp_relat		{}
		 | exp_shift LEQ exp_relat		{}
		 | exp_shift GEQ exp_relat		{}
		 | exp_shift GREAT exp_relat	{}
;

exp_shift: exp_add					{ $$ = $1; }
		 | exp_add LSHIFT exp_shift	{}
		 | exp_add RSHIFT exp_shift	{}
;

exp_add: exp_mult				{ $$ = $1; }
	   | exp_mult ADD exp_add	{}
	   | exp_mult SUB exp_add	{}
;

exp_mult: exp_cast						{ $$ = $1; }
		| exp_cast ASTERISK exp_mult	{}
		| exp_cast DIV exp_mult			{}
		| exp_cast MOD exp_mult			{}
;

exp_cast: exp_unary								{ $$ = $1; }
		| LPAREN tipo pointer RPAREN exp_cast	{}
;

exp_unary: exp_postfix			{ $$ = $1; }
		 | INC exp_unary		{}
		 | DEC exp_unary		{}
		 | AMPERSAND exp_cast	{}
		 | ASTERISK exp_cast	{}
		 | ADD exp_cast			{}
		 | SUB exp_cast			{}
		 | BIT_NOT exp_cast		{}
		 | LOG_NOT exp_cast		{}
;

exp_postfix: exp_prim				{ $$ = $1; }
		   | exp_postfix INC		{}
		   | exp_postfix DEC		{}
		   | exp_postfix LBRACK expressao RBRACK			{}
		   | exp_postfix LPAREN RPAREN						{}
		   | exp_postfix LPAREN exp_atr exp_postfix1 RPAREN	{}
;
exp_postfix1: COMMA exp_atr exp_postfix1	{}
			| /* epsilon */					{}
;

exp_prim: IDENTIFIER	{
			struct var_type t;
			union symbol_union u;
			Symbol *s = symbolNew(DECLARACAO_VARIAVEL, $1, t, u, @1.first_line, @1.first_column);
			s = identifierLookup(Program_Table.Global_Symbol_Table, s);
			if(!s){ YYABORT; }
			union expression_union exp = { .sym = s };
			$$ = expressionNew(IDENTIFIER, exp, NULL, NULL, @1.first_line, @1.first_line);
		}
		| number		{
			union expression_union exp = { .num = $1 };
			$$ = expressionNew(NUM_INT, exp, NULL, NULL, @1.first_line, @1.first_line);
		}
		| CHARACTER		{
			union expression_union exp = { .chr = $1 };
			$$ = expressionNew(CHARACTER, exp, NULL, NULL, @1.first_line, @1.first_line);
		}
		| STRING		{
			union expression_union exp = { .str = $1 };
			$$ = expressionNew(STRING, exp, NULL, NULL, @1.first_line, @1.first_line);
		}
		| LPAREN expressao RPAREN	{ $$ = $2; }
;

number: NUM_INT		{ $$ = $1; }
	  | NUM_HEXA	{ $$ = $1; }
	  | NUM_OCTA	{ $$ = $1; }
;

tipo: INT_T		{ g_tipo = TIPOS_INT; }
	| CHAR_T	{ g_tipo = TIPOS_CHAR; }
	| VOID_T	{ g_tipo = TIPOS_VOID; }
;

pointer: ASTERISK pointer	{ $$ = $2 + 1; }
	   | /* epsilon */		{ $$ = 0; }
;
array: LBRACK expressao RBRACK array	{
			struct array *aux = malloc(sizeof(struct array));
			aux->length = $2->node_value.num;
			// aux->length = $2; // aux->length = solveConstantExpression($2);
			aux->next = $4;

			$$ = aux;
		}
	 | /* epsilon */					{ $$ = NULL; }
;

%%

void yyerror(char *s){
	switch(yychar){
		case UNTERMINATED_COMMENT:
			printf("error:lexical:%d:%d: unterminated comment", linhas, colunas);
			break;
		case UNKNOWN_CHAR:
			colunas -= strlen(yytext);
			printf("error:lexical:%d:%d: %s", linhas, colunas, yytext);
			break;
		case END_OF_FILE:
			printf("error:syntax:%d:%d: expected declaration or statement at end of input\n", linhas, colunas);
			printLine(in_file, linhas);
			for(int i=1;i<colunas;i++)
				{ printf(" "); }
			printf("^");
			break;
		default:
			colunas -= strlen(yytext);
			printf("error:syntax:%d:%d: %s\n", linhas, colunas, yytext);
			printLine(in_file, linhas);
			for(int i=1;i<colunas;i++)
				{ printf(" "); }
			printf("^");
			break;
	}
}

int main(int argc, char **argv){
	Program_Table.Global_Symbol_Table = criaTabela(211);

	in_file = stdin;
	yyparse();

	// Symbol *aux = getPrimeiroRegistro(Program_Table.Global_Symbol_Table, "nuuuum");
	// printSymbol(*aux);
	// aux = getPrimeiroRegistro(Program_Table.Global_Symbol_Table, "abcd");
	// printSymbol(*aux);
	// aux = getPrimeiroRegistro(Program_Table.Global_Symbol_Table, "acdb");
	// printSymbol(*aux);

	hashtableFinalizar(Program_Table.Global_Symbol_Table);

    return 0;
}

int identifierInsert(HashTable symbol_table, Symbol* s){
	Symbol *aux = getPrimeiroRegistro(symbol_table, s->id);
	if(!aux){
		insereRegistro(symbol_table, s->id, s);
	}else{
		if(aux->type.type == s->type.pointers && aux->type.pointers){
			semanticError(REDECLARED_SYMBOL, s);
		}else{
			semanticError(REDEFINED_SYMBOL, s);
		}
		return 0;
	}

	return 1;
}
Symbol* identifierLookup(HashTable symbol_table, Symbol *s){
	Symbol *aux = NULL;
	if(symbol_table){
		aux = getPrimeiroRegistro(symbol_table, s->id);
	}
	if(!aux){
		aux = getPrimeiroRegistro(Program_Table.Global_Symbol_Table, s->id);
		if(!aux){
			semanticError(UNDECLARED_SYMBOL, s);
		}
	}

	return aux;
}

void semanticError(enum error_list erro, void* element){
	char error_msg[150];

	switch(erro){
		case UNDECLARED_SYMBOL:
		{
			Symbol *s = element;
			colunas = s->column;
			sprintf(error_msg, "'%s' undeclared", s->id);
			break;
		}
		case REDECLARED_SYMBOL:
		{
			Symbol *s = element;
			colunas = s->column;
			Symbol *aux = identifierLookup(Program_Table.Global_Symbol_Table, s);
			sprintf(error_msg, "variable '%s' already declared, previous declaration in line %d column %d", s->id, aux->line, aux->column);
			break;
		}
		case  REDEFINED_SYMBOL:
		{
			Symbol *s = element;
			colunas = s->column;
			Symbol *aux = identifierLookup(Program_Table.Global_Symbol_Table, s);
			sprintf(error_msg, "redefinition of '%s' previous defined in line %d column %d", s->id, aux->line, aux->column);
			break;
		}
	}

	printf("error:semantic:%d:%d: ", linhas, colunas);
	printf("%s\n", error_msg);

	printLine(in_file, linhas);
	for(int i=1;i<colunas;i++)
		{ printf(" "); }
	printf("^");
}

void printLine(FILE* in, int n){
	int i=1;
	char c;
	fseek(in, 0, SEEK_SET);

	while(i < n){
		c = fgetc(in);
		if(c == '\n')
			{ i++; }
		if(c == EOF)
			{ break; }
	}

	c = fgetc(in);
	while(c!='\n' && c!=EOF){
		printf("%c", c);
		c = fgetc(in);
	}
	printf("\n");
}
