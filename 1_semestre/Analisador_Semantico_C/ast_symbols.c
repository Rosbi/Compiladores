#include"ast_symbols.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void printSymbol(Symbol s){
    switch(s.symbol_type){
        case DECLARACAO_VARIAVEL:
            printf("\nVariável \"%s\":\n", s.id);
            switch(s.type.type){
                case TIPOS_INT:  printf(" Tipo: int");  break;
                case TIPOS_CHAR: printf(" Tipo: char"); break;
            }
            for(int i=0;i<s.type.pointers;i++)
                { printf("*"); }
            printf("\n Constante: %s\n", s.var.v.constant ? "SIM" : "NAO");
            printf(" Valor: %d\n", s.var.v.value.i);
            if(s.var.v.array){
                printf(" Array: ");
                struct array *aux = s.var.v.array;
                while(aux){
                    printf("[%d]", aux->length);
                    aux = aux->next;
                }
                printf("\n");
            }
            printf(" Linha: %d\n", s.line);
            printf(" Coluna: %d\n\n", s.column);
            break;
        case DECLARACAO_FUNCAO:
            break;
    }
}

Symbol* symbolNew(int symbol_type, char *id, struct var_type t, union symbol_union su, int line, int column){
    Symbol *aux = malloc(sizeof(Symbol));
    aux->symbol_type = symbol_type;
    aux->id = malloc((strlen(id) + 1) * sizeof(char));
    strcpy(aux->id, id);
    aux->type = t;
    aux->var = su;
    aux->line = line;
    aux->column = column;

    return aux;
}
