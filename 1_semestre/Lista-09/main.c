#include<stdio.h>
#include<stdbool.h>
#include<stdarg.h>
#include"lex_analyser.h"

token_type g_token;
FILE* file_in;
bool S();
bool L();
bool E();

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

void printError(char* esperado){
	if(g_token == NEWLINE){
		myprintf("ERRO SINTATICO: CADEIA INCOMPLETA");
	}else{
		myprintf("ERRO SINTATICO EM: %s ESPERADO: %s", tokenStringify(g_token), esperado);
		// switch(){
		// 	case 'S': printf("if, begin, print"); break;
		// 	case 'L': printf("end, ;"); break;
		// 	case 'E': printf("num"); break;
		// }
	}
}

bool error(token_type t){}
bool advance(){
	do{
		g_token = getToken(file_in);
	}while(g_token == WHITESPACE);
	return true;
}
bool eat(token_type t){
	if(g_token==t){
		advance();
		return true;
	}else{
		error(t);
		return false;
	}
}

bool S(){
	switch(g_token){
		case IF: 
			if(!eat(IF)){ printError("XXX"); return false; }
			if(!E()){ return false; }
			if(!eat(THEN)){ printError("then"); return false; } 
			if(!S()){ return false; }
			if(!eat(ELSE)){ printError("else"); return false; }
			if(!S()){ return false; }
			break;
		case BEGIN:
			if(!eat(BEGIN)){ printError("XXX"); return false; }
			if(!S()){ return false; }
			if(!L()){ return false; }
			break;
		case PRINT: 
			if(!eat(PRINT)){ printError("XXX"); return false; }
			if(!E()){ return false; }
			break;
		default: 
			printError("if, begin, print");
			return false;
	}
	return true;
}
bool L(){
	switch(g_token){
		case END:
			if(!eat(END)){ printError("LLL"); return false; }
			break;
		case SEMICOLON:
			if(!eat(SEMICOLON)){ printError("LLL"); return false; }
			if(!S()){ return false; }
			if(!L()){ return false; }
			break;
		default: 
			printError("end, ;");
			return false;
	}
	return true;
}
bool E(){
	if(!eat(NUMBER)){ printError("num"); return false; }
	if(!eat(EQUALS)){ printError("="); return false; }
	if(!eat(NUMBER)){ printError("num"); return false; }
	return true;
}

int main(){
	// file_in = fopen("t.txt", "r");
	file_in = stdin;
	
	while(!feof(file_in)){
		g_token = getToken(file_in);
		if(S()){
			myprintf("CADEIA ACEITA");
		}else{
			while(g_token != NEWLINE){
				g_token = getToken(file_in);
				if(g_token == TOKEN_ERROR)
					break;
			}
		}
	}
}