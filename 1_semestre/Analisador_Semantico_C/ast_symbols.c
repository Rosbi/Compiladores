#include"ast_symbols.h"
#include<stdio.h>

void printSymbol(Symbol s){
    switch(s.symbol_type){
        case TIPOS_VARIAVEL:
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
            printf(" Linha: %d\n", s.var.v.line);
            printf(" Coluna: %d\n\n", s.var.v.column);
            break;
    }
}
