#include<stdio.h>
#include"lex_analyser.h"

void printToken(token_type token){
    switch(token){
        case TOKEN_ERROR: printf("erro\n");break;
        case IF:        printf("if\n");break;
        case THEN:      printf("then\n");break;
        case ELSE:      printf("else\n");break;
        case BEGIN:     printf("begin\n");break;
        case END:       printf("end\n");break;
        case PRINT:     printf("print\n");break;
        case NUMBER:    printf("number\n");break;
        case EQUALS:    printf("equals\n");break;
        case SEMICOLON: printf("semicolon\n");break;
        case WHITESPACE:  printf("ws\n");break;
        default:        printf("wtf\n");break;
    }
}

int main(){
    FILE* file_in = stdin;
    while(!feof(file_in)){
        token_type token = getToken(file_in);
        printToken(token);
    }
}