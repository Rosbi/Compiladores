%{

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"ast_symbols.h"
#include"hashTable.h"
#include"commands.h"
#include"errors.h"
#include"types.h"

extern int yylex();
extern char* yytext;
void yyerror(char *s);

void printLine(FILE* in, int line_number);
void semanticError(enum error_list erro, void* element);
Symbol* identifierLookup(HashTable symbol_table, Symbol *s);
int identifierInsert(HashTable symbol_table, Symbol* s);
int varInsertAndCheck(HashTable symbol_table, Symbol* s);
int matchPrototypes(Symbol pro1, Symbol pro2);

extern int colunas;
extern int linhas;
int g_tipo = 0;
FILE* in_file = NULL;
HashTable Current_Symbol_Table = NULL;

%}

/* declare types */
%union{
	char* string;
	int integer;
	char charac;
	struct symbol* symbol_union;
	struct array* array_union;
	struct expression* expression_union;
	struct parameters* parameters_union;
	struct command_list* commands_union;
	struct function_definition* func_def_union;
}

%type <string> STRING
%type <string> IDENTIFIER
%type <integer> pointer
%type <integer> tipo
%type <integer> number
%type <integer> NUM_INT
%type <integer> NUM_HEXA
%type <integer> NUM_OCTA
%type <string> CHARACTER
%type <symbol_union> declaracao_var1
%type <symbol_union> function_header
%type <array_union> array
%type <expression_union> opt_assign
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
%type <expression_union> opt_exp
%type <parameters_union> parametros
%type <parameters_union> parametros1
%type <commands_union> comandos
%type <commands_union> lista_comandos
%type <commands_union> else_exp
%type <commands_union> bloco
%type <commands_union> function_body
%type <func_def_union> funcao

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

	/* additional tokens */
%token ADDRESS
%token MUL
%token BIT_AND
%token POINTER_DEFERENCE
%token UNR_PLUS
%token UNR_MINUS
%token CONDITIONAL_EXP
%token CONDITIONAL_EXP_THENELSE
%token SUBSCRIPT
%token CAST

	/* unused tokens */
%token BREAK_T
%token SWITCH_T
%token CASE_T
%token DEFAULT_T
%token TYPEDEF_T
%token STRUCT_T

%start programa

%%

programa: programa1 programa END_OF_FILE	{ printf("SUCCESSFUL COMPILATION."); YYACCEPT; }
		| programa1 END_OF_FILE				{ printf("SUCCESSFUL COMPILATION."); YYACCEPT; }
;
programa1: declaracoes	{}
		 | funcao		{}
;

declaracoes: 
		   NUMBER_SIGN DEFINE IDENTIFIER expressao	{
			   struct var_type t = { TIPOS_INT, 0 };
			   struct variable v = { NULL, true};
			   union symbol_union u = { .v = v };

			   if($4->node_type == STRING){
				   semanticError(STRING_DEFINE, $4);
				   YYABORT;
			   }

			   Symbol *aux = symbolNew(DECLARACAO_VARIAVEL, $3, t, u, @3.first_line, @3.first_column);
			   Const_expr_state state = evaluateConstExpr($4);
			   if(state.error != NO_ERROR || state.error > WARNINGS_START){
				   semanticError(state.error, state.exp);
				   YYABORT;
			   }else{
				   aux->var.v.value.i = state.value;
				   if(!identifierInsert(Current_Symbol_Table, aux)){ YYABORT; };
			   }
		   }
		   | declaracao_var		{}
		   | declaracao_prot	{}
;

declaracao_var: tipo declaracao_var1 SEMICOLON	{}
;
declaracao_var1:
	pointer IDENTIFIER array opt_assign							{
		struct var_type t = { g_tipo, $1 };
		struct variable v = { $3, false };
		union symbol_union u = { .v = v };
		Symbol *aux = symbolNew(DECLARACAO_VARIAVEL, $2, t, u, @2.first_line, @2.first_column);
		if(!varInsertAndCheck(Current_Symbol_Table, aux)){ YYABORT; }
	}
	| declaracao_var1 COMMA pointer IDENTIFIER array opt_assign	{
		struct var_type t = { g_tipo, $3 };
		struct variable v = { $5, false };
		union symbol_union u = { .v = v };
		Symbol *aux = symbolNew(DECLARACAO_VARIAVEL, $4, t, u, @4.first_line, @4.first_column);
		if(!varInsertAndCheck(Current_Symbol_Table, aux)){ YYABORT; }
	}
;
opt_assign: ASSIGN exp_atr	{}
		  | /* epsilon */	{}
;

declaracao_prot: function_header SEMICOLON	{}
;

funcao: function_header LCBRACK {
			$1->var.f.has_definition = true;
			Current_Symbol_Table = criaTabela(211);

			struct function_definition func = { Current_Symbol_Table, NULL, $1->type, $1->var.f, NULL };
			func.name = malloc((strlen($1->id) + 1) * sizeof(char));
			strcpy(func.name, $1->id);

			for(struct parameters *params=$1->var.f.parameters;params;params=params->next){
				if(!varInsertAndCheck(Current_Symbol_Table, params->symbol)){ YYABORT; }
			}

			if(!Program_Table.head){
				Program_Table.head = malloc(sizeof(struct function_list));
				Program_Table.head->function = func;
				Program_Table.head->next = NULL;
			}else{
				struct function_list *aux = Program_Table.head;
				while(aux->next)
					{ aux = aux->next; }
				aux->next = malloc(sizeof(struct function_list));
				aux->next->function = func;
				aux->next->next = NULL;
			}
		} function_body {
			struct function_list *aux = Program_Table.head;
			while(aux->next)
				{ aux = aux->next; }
			aux->function.commands_head = $4;
			Current_Symbol_Table = Program_Table.Global_Symbol_Table;
		}
;
function_header: tipo pointer IDENTIFIER parametros	{
						struct var_type t = { $1, $2 };
						struct function_prototype fp = { false, $4 };
						union symbol_union u = { .f = fp };
						Symbol *aux = symbolNew(DECLARACAO_FUNCAO, $3, t, u, @3.first_line, @3.first_column);
						if(!identifierInsert(Current_Symbol_Table, aux)){ YYABORT; }
						$$ = aux;
					}
;
function_body: func_dec_var comandos RCBRACK {
					$$ = $2;
				}
;
func_dec_var: func_dec_var declaracao_var	{}
			| /* epsilon */					{}
;

parametros: LPAREN parametros1 RPAREN	{ $$ = $2; }
		  | LPAREN RPAREN				{ $$ = NULL; }
;
parametros1: tipo pointer IDENTIFIER array						{
					struct var_type t = { $1, $2 };
					struct variable v = { $4, false };
					union symbol_union u = { .v = v };
					struct parameters *param = malloc(sizeof(struct parameters));
					param->symbol = symbolNew(DECLARACAO_VARIAVEL, $3, t, u, @3.first_line, @3.first_column);
					param->next = NULL;
					if(t.type == TIPOS_VOID && t.pointers == 0){
						semanticError(PARAMETER_DECLARED_VOID, param->symbol);
						YYABORT;
					}
					$$ = param;
				}
		   | parametros1 COMMA tipo pointer IDENTIFIER array	{
					struct var_type t = { $3, $4 };
					struct variable v = { $6, false };
					union symbol_union u = { .v = v };
					struct parameters *aux = $1, *param = malloc(sizeof(struct parameters));
					param->symbol = symbolNew(DECLARACAO_VARIAVEL, $5, t, u, @5.first_line, @5.first_column);
					param->next = NULL;
					if(t.type == TIPOS_VOID && t.pointers == 0){
						semanticError(PARAMETER_DECLARED_VOID, param->symbol);
						YYABORT;
					}
					while(aux->next){
						aux = aux->next;
					}
					aux->next = param;
					$$ = $1;
				}
;

bloco: LCBRACK comandos RCBRACK	{
			$$ = commandNew(COM_BLOCK, $2);
		}
;

comandos: comandos lista_comandos	{
				Command_list *aux;
				for(aux=$1;aux->next;aux=aux->next);
				aux->next = $2;
				$$ = $1;
			}
		| lista_comandos			{ $$ = $1; }
;

lista_comandos: DO_T bloco WHILE_T LPAREN expressao RPAREN SEMICOLON	{
				  $$ = commandNew(COM_WHILE, $5, $2);
			  }
			  | IF_T LPAREN expressao RPAREN bloco else_exp				{
				  $$ = commandNew(COM_IF, $3, $5, $6);
			  }
			  | WHILE_T LPAREN expressao RPAREN bloco					{
				  Exp_type_state state = { NULL, NO_ERROR, $3 };
				  state = evaluateExpressionType(state);
				  printWarnings(state.warnings_list, in_file);
				  free(state.warnings_list);
				  if(state.error != NO_ERROR && state.error < WARNINGS_START){
					  semanticError(state.error, state.exp);
					  YYABORT;
				  }
				  $$ = commandNew(COM_WHILE, $3, $5);
			  }
			  | FOR_T LPAREN opt_exp SEMICOLON opt_exp SEMICOLON opt_exp RPAREN bloco	{
				  $$ = commandNew(COM_FOR, $3, $5, $7, $9);
			  }
			  | PRINTF_T LPAREN STRING printf_exp RPAREN SEMICOLON		{}
			  | SCANF_T LPAREN STRING COMMA AMPERSAND IDENTIFIER RPAREN SEMICOLON		{}
			  | EXIT_T LPAREN expressao RPAREN SEMICOLON				{}
			  | RETURN_T opt_exp SEMICOLON								{
				  $$ = commandNew(COM_RETURN, $2);
			  }
			  | expressao SEMICOLON										{
				  $$ = commandNew(COM_EXP, $1);
			  }
			  | SEMICOLON												{ $$ = NULL; }
			  | bloco													{
				  $$ = commandNew(COM_BLOCK, $1);
			  }
;
printf_exp: COMMA expressao	{}
		  | /* epsilon */	{}
;
else_exp: ELSE_T bloco		{ $$ = $2; }
		| /* epsilon */		{ $$ = NULL; }
;
opt_exp: expressao		{ $$ = $1; }
	   | /* epsilon */	{ $$ = NULL;}
;

expressao: exp_atr					{ $$ = $1; }
		 | expressao COMMA exp_atr	{ $$ = $3; }
;

exp_atr: exp_cond						{ $$ = $1; }
	   | exp_unary ASSIGN exp_atr		{
		   union expression_union u;
		   $$ = expressionNew(ASSIGN, u, $1, $3, @2.first_line, @2.first_column);
	   }
	   | exp_unary ADD_ASSIGN exp_atr	{
		   union expression_union u;
		   $$ = expressionNew(ADD_ASSIGN, u, $1, $3, @2.first_line, @2.first_column);
	   }
	   | exp_unary SUB_ASSIGN exp_atr	{
		   union expression_union u;
		   $$ = expressionNew(SUB_ASSIGN, u, $1, $3, @2.first_line, @2.first_column);
	   }
;

exp_cond: exp_log_or										{ $$ = $1; }
		| exp_log_or QUEST_MARK expressao COLON exp_cond	{
			union expression_union u;
			Expression *aux = expressionNew(CONDITIONAL_EXP_THENELSE, u, $3, $5, @4.first_line, @4.first_column);
			$$ = expressionNew(CONDITIONAL_EXP, u, $1, aux, @2.first_line, @2.first_column);
		}
;

exp_log_or: exp_log_and						{ $$ = $1; }
		  | exp_log_or LOG_OR exp_log_and	{
			union expression_union u;
			$$ = expressionNew(LOG_OR, u, $1, $3, @2.first_line, @2.first_column);
		  }
;

exp_log_and: exp_or						{ $$ = $1; }
		   | exp_log_and LOG_AND exp_or	{
				union expression_union u;
				$$ = expressionNew(LOG_AND, u, $1, $3, @2.first_line, @2.first_column);
		   }
;

exp_or: exp_xor					{ $$ = $1; }
	  | exp_or BIT_OR exp_xor	{
		   union expression_union u;
		   $$ = expressionNew(BIT_OR, u, $1, $3, @2.first_line, @2.first_column);
	  }
;

exp_xor: exp_and					{ $$ = $1; }
	   | exp_xor BIT_XOR exp_and	{
		   union expression_union u;
		   $$ = expressionNew(BIT_XOR, u, $1, $3, @2.first_line, @2.first_column);
	   }
;

exp_and: exp_equal					{ $$ = $1; }
	   | exp_and AMPERSAND exp_equal	{
		   union expression_union u;
		   $$ = expressionNew(BIT_AND, u, $1, $3, @2.first_line, @2.first_column);
	   }
;

exp_equal: exp_relat						{ $$ = $1; }
		 | exp_equal EQUALS exp_relat		{
			union expression_union u;
			$$ = expressionNew(EQUALS, u, $1, $3, @2.first_line, @2.first_column);
		 }
		 | exp_equal NOT_EQUALS exp_relat	{
			union expression_union u;
			$$ = expressionNew(NOT_EQUALS, u, $1, $3, @2.first_line, @2.first_column);
		 }
;

exp_relat: exp_shift					{ $$ = $1; }
		 | exp_relat LESS exp_shift		{
		   union expression_union u;
		   $$ = expressionNew(LESS, u, $1, $3, @2.first_line, @2.first_column);
		 }
		 | exp_relat LEQ exp_shift		{
		   union expression_union u;
		   $$ = expressionNew(LEQ, u, $1, $3, @2.first_line, @2.first_column);
		 }
		 | exp_relat GEQ exp_shift		{
		   union expression_union u;
		   $$ = expressionNew(GEQ, u, $1, $3, @2.first_line, @2.first_column);
		 }
		 | exp_relat GREAT exp_shift	{
		   union expression_union u;
		   $$ = expressionNew(GREAT, u, $1, $3, @2.first_line, @2.first_column);
		 }
;

exp_shift: exp_add					{ $$ = $1; }
		 | exp_shift LSHIFT exp_add	{
			union expression_union u;
			$$ = expressionNew(LSHIFT, u, $1, $3, @2.first_line, @2.first_column);
		 }
		 | exp_shift RSHIFT exp_add	{
			union expression_union u;
			$$ = expressionNew(RSHIFT, u, $1, $3, @2.first_line, @2.first_column);
		 }
;

exp_add: exp_mult				{ $$ = $1; }
	   | exp_add ADD exp_mult	{
			union expression_union u;
			$$ = expressionNew(ADD, u, $1, $3, @2.first_line, @2.first_column);
	   }
	   | exp_add SUB exp_mult	{
			union expression_union u;
			$$ = expressionNew(SUB, u, $1, $3, @2.first_line, @2.first_column);
	   }
;

exp_mult: exp_cast						{ $$ = $1; }
		| exp_mult ASTERISK exp_cast	{
			union expression_union u;
			$$ = expressionNew(MUL, u, $1, $3, @2.first_line, @2.first_column);
		}
		| exp_mult DIV exp_cast			{
			union expression_union u;
			$$ = expressionNew(DIV, u, $1, $3, @2.first_line, @2.first_column);
		}
		| exp_mult MOD exp_cast			{
			union expression_union u;
			$$ = expressionNew(MOD, u, $1, $3, @2.first_line, @2.first_column);
		}
;

exp_cast: exp_unary								{ $$ = $1; }
		| LPAREN tipo pointer RPAREN exp_cast	{
			union expression_union u;
			$$ = expressionNew(CAST, u, $5, NULL, @1.first_line, @1.first_column);
			struct var_type v = { .type=$2, .pointers=$3, .constant=true };
			$$->exp_type = v;
		}
;

exp_unary: exp_postfix			{ $$ = $1; }
		 | INC exp_unary		{
			union expression_union u;
			$$ = expressionNew(INC, u, $2, NULL, @1.first_line, @1.first_column);
		 }
		 | DEC exp_unary		{
			union expression_union u;
			$$ = expressionNew(DEC, u, $2, NULL, @1.first_line, @1.first_column);
		 }
		 | AMPERSAND exp_cast	{
			union expression_union u;
			$$ = expressionNew(ADDRESS, u, $2, NULL, @1.first_line, @1.first_column);
		 }
		 | ASTERISK exp_cast	{
			union expression_union u;
			$$ = expressionNew(POINTER_DEFERENCE, u, $2, NULL, @1.first_line, @1.first_column);
		 }
		 | ADD exp_cast			{
			union expression_union u;
			$$ = expressionNew(UNR_PLUS, u, $2, NULL, @1.first_line, @1.first_column);
		 }
		 | SUB exp_cast			{
			union expression_union u;
			$$ = expressionNew(UNR_MINUS, u, $2, NULL, @1.first_line, @1.first_column);
		 }
		 | BIT_NOT exp_cast		{
			union expression_union u;
			$$ = expressionNew(BIT_NOT, u, $2, NULL, @1.first_line, @1.first_column);
		 }
		 | LOG_NOT exp_cast		{
			union expression_union u;
			$$ = expressionNew(LOG_NOT, u, $2, NULL, @1.first_line, @1.first_column);
		 }
;

exp_postfix: exp_prim				{ $$ = $1; }
		   | exp_postfix INC		{
				union expression_union u;
				$$ = expressionNew(INC, u, $1, NULL, @2.first_line, @2.first_column);
		   }
		   | exp_postfix DEC		{
				union expression_union u;
				$$ = expressionNew(DEC, u, $1, NULL, @2.first_line, @2.first_column);
		   }
		   | exp_postfix LBRACK expressao RBRACK			{
			   union expression_union u;
			   $$ = expressionNew(SUBSCRIPT, u, $1, $3, @2.first_line, @2.first_column);
		   }
		   | exp_postfix LPAREN RPAREN						{}
		   | exp_postfix LPAREN exp_postfix1 RPAREN	{}
;
exp_postfix1: exp_atr						{}
			| exp_postfix1 COMMA exp_atr	{}
;

exp_prim: IDENTIFIER	{
			struct var_type t;
			union symbol_union u;
			Symbol *s = symbolNew(DECLARACAO_VARIAVEL, $1, t, u, @1.first_line, @1.first_column);
			s = identifierLookup(Current_Symbol_Table, s);
			if(!s){ YYABORT; }
			union expression_union exp = { .sym = s };
			$$ = expressionNew(IDENTIFIER, exp, NULL, NULL, @1.first_line, @1.first_column);
		}
		| number		{
			union expression_union exp = { .num = $1 };
			$$ = expressionNew(NUM_INT, exp, NULL, NULL, @1.first_line, @1.first_column);
		}
		| CHARACTER		{
			union expression_union exp = { .chr = $1 };
			$$ = expressionNew(CHARACTER, exp, NULL, NULL, @1.first_line, @1.first_column);
		}
		| STRING		{
			union expression_union exp = { .str = $1 };
			$$ = expressionNew(STRING, exp, NULL, NULL, @1.first_line, @1.first_column);
		}
		| LPAREN expressao RPAREN	{ $$ = $2; }
;

number: NUM_INT		{ $$ = $1; }
	  | NUM_HEXA	{ $$ = $1; }
	  | NUM_OCTA	{ $$ = $1; }
;

tipo: INT_T		{ $$ = g_tipo = TIPOS_INT; }
	| CHAR_T	{ $$ = g_tipo = TIPOS_CHAR; }
	| VOID_T	{ $$ = g_tipo = TIPOS_VOID; }
;

pointer: ASTERISK pointer	{ $$ = $2 + 1; }
	   | /* epsilon */		{ $$ = 0; }
;
array: LBRACK expressao RBRACK array	{
			struct array *aux = malloc(sizeof(struct array));
			Const_expr_state state = evaluateConstExpr($2);
			if(state.error != NO_ERROR || state.error > WARNINGS_START){
				semanticError(state.error, state.exp);
				YYABORT;
			}
			
			aux->exp = $2;
			aux->length = state.value;
			aux->next = $4;
			if(aux->next){
				aux->dimension = aux->next->dimension + 1;
			}else{
				aux->dimension = 1;
			}

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
	Current_Symbol_Table = Program_Table.Global_Symbol_Table;

	in_file = stdin;
	yyparse();

	// printa as tabelas
	printf("\nGlobal Symbols:\n");
	HshTblMap(Program_Table.Global_Symbol_Table, printSymbol);
	for(struct function_list *aux=Program_Table.head;aux;aux=aux->next){
		printf("\n%s Local Symbols:\n", aux->function.name);
		HshTblMap(aux->function.Local_Symbol_Table, printSymbol);
		printFunctionBody(aux->function.commands_head);
	}
	/*
	//liberação de memória
	HshTblMap(Program_Table.Global_Symbol_Table, freeSymbol);
	for(struct function_list *aux=Program_Table.head;aux;aux=aux->next){
		HshTblMap(aux->function.Local_Symbol_Table, freeSymbol);
	}

	hashtableFinalizar(Program_Table.Global_Symbol_Table);
	*/
    return 0;
}

int matchPrototypes(Symbol pro1, Symbol pro2){
	struct parameters *param1 = pro1.var.f.parameters;
	struct parameters *param2 = pro2.var.f.parameters;
	for(;param1 && param2;param1=param1->next, param2=param2->next){
		Symbol sym1 = *param1->symbol;
		Symbol sym2 = *param2->symbol;
		if(sym1.type.type != sym2.type.type /**/ || sym1.type.pointers != sym2.type.pointers /**/){
			semanticError(ARGUMENT_DIFF_PROTOTYPE, &sym2);
			return ARGUMENT_DIFF_PROTOTYPE;
		}
		// else if(!sym1.var.v.array && !sym2.var.v.array){
		// 	if(sym1.type.pointers != sym2.type.pointers)
		// 		{ return ARGUMENT_DIFF_PROTOTYPE; }
		// }else if(sym1.var.v.array){

		// }
	}
	if(param1){
		semanticError(PROTOTYPE_MORE_ARGS, &pro2);
		return PROTOTYPE_MORE_ARGS;
	}
	if(param2){
		semanticError(PROTOTYPE_FEWER_ARGS, &pro2);
		return PROTOTYPE_FEWER_ARGS;
	}
	if(pro1.type.type != pro2.type.type || pro1.type.pointers != pro2.type.pointers){
		semanticError(CONFLICTING_TYPES, &pro2);
		return CONFLICTING_TYPES;
	}

	return NO_ERROR;
}
int identifierInsert(HashTable symbol_table, Symbol* s){
	Symbol *aux = getPrimeiroRegistro(symbol_table, s->id);
	if(!aux){
		insereRegistro(symbol_table, s->id, s);
	}else if(s->symbol_type == DECLARACAO_VARIAVEL){
		if(aux->type.type == s->type.type && aux->type.pointers == s->type.pointers){
			semanticError(REDECLARED_SYMBOL, s);
		}else{
			semanticError(REDEFINED_SYMBOL, s);
		}
		return 0;
	}else if(s->symbol_type == DECLARACAO_FUNCAO){
		if(aux->var.f.has_definition){
			semanticError(REDEFINED_SYMBOL, s);
			return 0;
		}
		if(matchPrototypes(*aux, *s) != NO_ERROR)
			{ return 0; }
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
int varInsertAndCheck(HashTable symbol_table, Symbol* s){
	struct array *a = s->var.v.array;
	while(a){
		if(a->length < 0){
			semanticError(ARR_NEGATIVE_INITIALIZER, s);
			return 0;
		}else if(a->length == 0){
			semanticError(ARR_ZERO_INITIALIZER, s);
			return 0;
		}
		a = a->next;
	}

	if(s->type.type == TIPOS_VOID && s->type.pointers == 0){
		semanticError(VARIABLE_DECLARED_VOID, s);
		return 0;
	}
	if(!identifierInsert(symbol_table, s)){
		return 0;
	};
	return 1;
}

void semanticError(enum error_list erro, void* element){
	char error_msg[150];

	switch(erro){
		case UNDECLARED_SYMBOL:{
			Symbol *s = element;
			linhas = s->line;
			colunas = s->column;
			sprintf(error_msg, "'%s' undeclared", s->id);
			break;
		}
		case REDECLARED_SYMBOL:{
			Symbol *s = element;
			linhas = s->line;
			colunas = s->column;
			Symbol *aux = identifierLookup(Current_Symbol_Table, s);
			sprintf(error_msg, "variable '%s' already declared, previous declaration in line %d column %d", s->id, aux->line, aux->column);
			break;
		}
		case REDEFINED_SYMBOL:{
			Symbol *s = element;
			linhas = s->line;
			colunas = s->column;
			Symbol *aux = identifierLookup(Current_Symbol_Table, s);
			sprintf(error_msg, "redefinition of '%s' previous defined in line %d column %d", s->id, aux->line, aux->column);
			break;
		}
		case VARIABLE_DECLARED_VOID:{
			Symbol *s = element;
			linhas = s->line;
			colunas = s->column;
			sprintf(error_msg, "variable '%s' declared void", s->id);
			break;
		}
		case DIVISION_BY_ZERO:{
			Expression *exp = element;
			linhas = exp->line;
			colunas = exp->column;
			sprintf(error_msg, "division by zero");
			break;
		}
		case INITIALIZER_NOT_CONST:{
			Expression *exp = element;
			linhas = exp->line;
			colunas = exp->column;
			sprintf(error_msg, "'%s' initializer element is not constant", exp->node_value.sym->id);
			break;
		}
		case STRING_DEFINE:{
			Expression *exp = element;
			linhas = exp->line;
			colunas = exp->column;
			sprintf(error_msg, "string type is not compatible with define");
			break;
		}
		case STRING_ASSIGNMENT:{
			Expression *exp = element;
			linhas = exp->line;
			colunas = exp->column;
			sprintf(error_msg, "assignment of read-only location %s", exp->node_value.str);
			break;
		}
		case CONST_IDENTIFIER_ASSIGNMENT:{
			Expression *exp = element;
			linhas = exp->line;
			colunas = exp->column;
			sprintf(error_msg, "assignment of read-only identifier \"%s\"", exp->node_value.sym->id);
			break;
		}
		case RVALUE_ASSIGNMENT:{
			Expression *exp = element;
			linhas = exp->line;
			colunas = exp->column;
			sprintf(error_msg, "lvalue required as left operand of assignment");
			break;
		}
		case ARR_NEGATIVE_INITIALIZER:{
			Symbol *s = element;
			linhas = s->line;
			colunas = s->column;
			sprintf(error_msg, "size of array '%s' is negative", s->id);
			break;
		}
		case ARR_ZERO_INITIALIZER:{
			Symbol *s = element;
			linhas = s->line;
			colunas = s->column;
			sprintf(error_msg, "size of array '%s' is zero", s->id);
			break;
		}
		case PARAMETER_DECLARED_VOID:{
			Symbol *s = element;
			linhas = s->line;
			colunas = s->column;
			sprintf(error_msg, "parameter '%s' declared void", s->id);
			break;
		}
		case ARGUMENT_DIFF_PROTOTYPE:{
			Symbol *s = element;
			linhas = s->line;
			colunas = s->column;
			sprintf(error_msg, "argument '%s' does not match prototype", s->id);
			break;
		}
		case PROTOTYPE_MORE_ARGS:{
			Symbol *s = element;
			linhas = s->line;
			colunas = s->column;
			sprintf(error_msg, "prototype for '%s' declares more arguments", s->id);
			break;
		}
		case PROTOTYPE_FEWER_ARGS:{
			Symbol *s = element;
			linhas = s->line;
			colunas = s->column;
			sprintf(error_msg, "prototype for '%s' declares fewer arguments", s->id);
			break;
		}
		case CONFLICTING_TYPES:{
			Symbol *s = element;
			linhas = s->line;
			colunas = s->column;
			sprintf(error_msg, "conflicting types for '%s'", s->id);
			break;
		}
		case RVALUE_INC_OPERAND:{
			Expression *exp = element;
			linhas = exp->line;
			colunas = exp->column;
			sprintf(error_msg, "lvalue required as increment operand");
			break;
		}
		case RVALUE_DEC_OPERAND:{
			Expression *exp = element;
			linhas = exp->line;
			colunas = exp->column;
			sprintf(error_msg, "lvalue required as decrement operand");
			break;
		}
		case INVALID_UNR_OPERAND:{
			Expression *exp = element;
			linhas = exp->line;
			colunas = exp->column;
			sprintf(error_msg, "invalid type argument of unary '%s' (have '%s')",
				getOperator(exp->node_type), getType(exp->left->exp_type));
			break;
		}
		case WRONG_TYPE_COMPARISON:{
			Expression *exp = element;
			linhas = exp->line;
			colunas = exp->column;
			sprintf(error_msg, "comparison between '%s' and '%s' operator '%s'",
				getType(exp->left->exp_type), getType(exp->right->exp_type), getOperator(exp->node_type));
			break;
		}
		case INCOMPATIBLE_ASSIGNMENT:{
			Expression *exp = element;
			linhas = exp->line;
			colunas = exp->column;
			sprintf(error_msg, "incompatible types when assigning to type ’%s’ from type ’%s’",
				getType(exp->left->exp_type), getType(exp->right->exp_type));
			break;
		}
		case INVALID_BIN_OPERANDS:{
			Expression *exp = element;
			linhas = exp->line;
			colunas = exp->column;
			sprintf(error_msg, "invalid operands to binary ’%s’ (have ’%s’ and ’%s’)",
				getOperator(exp->node_type), getType(exp->left->exp_type), getType(exp->right->exp_type));
			break;
		}
		case RSHIFT_NEGATIVE:{
			Expression *exp = element;
			linhas = exp->line;
			colunas = exp->column;
			sprintf(error_msg, "right shift count is negative");
			break;
		}
		case LSHIFT_NEGATIVE:{
			Expression *exp = element;
			linhas = exp->line;
			colunas = exp->column;
			sprintf(error_msg, "left shift count is negative");
			break;
		}
		case INVALID_SUBSCRIPTOR:{
			Expression *exp = element;
			linhas = exp->line;
			colunas = exp->column;
			sprintf(error_msg, "subscripted value is neither array nor pointer");
			break;
		}
		case IMPOSSIBLE_INT_CONVERSION:{
			Expression *exp = element;
			linhas = exp->line;
			colunas = exp->column;
			sprintf(error_msg, "cannot convert from ’%s’ to int", getType(exp->exp_type));
			break;
		}
		case NO_ERROR:
			printf("problem in parsing, no semantic error passed to semantic error function");
			return;
		// default:
		// 	printf("unknown error code in semantic error function");
		// 	return;
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

	int starting_point = ftell(in);
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
	fseek(in, starting_point, SEEK_SET);
}
