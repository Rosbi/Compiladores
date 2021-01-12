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
                case TIPOS_VOID: printf(" Tipo: void"); break;
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
            printf("\nFunção: %d:%d ", s.line, s.column);
            switch(s.type.type){
                case TIPOS_INT:  printf("int");  break;
                case TIPOS_CHAR: printf("char"); break;
                case TIPOS_VOID: printf("void"); break;
            }
            for(int i=0;i<s.type.pointers;i++)
                { printf("*"); }
            printf(" %s(", s.id);
            struct parameters *aux;
            for(aux=s.var.f.parameters;aux!=NULL;aux=aux->next){
                switch(aux->type.type){
                    case TIPOS_INT:  printf("int");  break;
                    case TIPOS_CHAR: printf("char"); break;
                    case TIPOS_VOID: printf("void"); break;
                }
                for(int i=0;i<aux->type.pointers;i++)
                    { printf("*"); }
                printf(" %s", aux->id);
                struct array *arr = aux->param.array;
                while(arr){
                    printf("[%d]", arr->length);
                    arr = arr->next;
                }
                printf(", ");
            }
            printf(")\n\n");

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

struct parameters* parameterNew(char *id, struct var_type t, struct variable v, int line, int column, struct parameters *next){
    struct parameters *aux = malloc(sizeof(struct parameters));
    aux->id = malloc((strlen(id) + 1) * sizeof(char));
    strcpy(aux->id, id);
    aux->type = t;
    aux->param = v;
    aux->line = line;
    aux-> column = column;
    aux->next = next;

    return aux;
}
