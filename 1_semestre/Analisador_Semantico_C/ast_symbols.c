#include"ast_symbols.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void printSymbol(Symbol *s){
    switch(s->symbol_type){
        case DECLARACAO_VARIAVEL:
            printf("%d:%d: ", s->line, s->column);
            printf("%s", s->var.v.constant ? "const " : "");
            switch(s->type.type){
                case TIPOS_INT:  printf("int");  break;
                case TIPOS_CHAR: printf("char"); break;
                case TIPOS_VOID: printf("void"); break;
            }
            for(int i=0;i<s->type.pointers;i++)
                { printf("*"); }
            printf(" %s", s->id);
            if(s->var.v.array){
                struct array *aux = s->var.v.array;
                while(aux){
                    printf("[%d]", aux->length);
                    aux = aux->next;
                }
            }
            if(s->var.v.constant)
                { printf(" = %d", s->var.v.value.i); }
            printf("\n");
            break;
        case DECLARACAO_FUNCAO:
            printf("%d:%d ", s->line, s->column);
            switch(s->type.type){
                case TIPOS_INT:  printf("int");  break;
                case TIPOS_CHAR: printf("char"); break;
                case TIPOS_VOID: printf("void"); break;
            }
            for(int i=0;i<s->type.pointers;i++)
                { printf("*"); }
            printf(" %s(", s->id);
            struct parameters *aux;
            for(aux=s->var.f.parameters;aux!=NULL;aux=aux->next){
                printf("%s", aux->symbol->var.v.constant ? "const " : "");
                switch(aux->symbol->type.type){
                    case TIPOS_INT:  printf("int");  break;
                    case TIPOS_CHAR: printf("char"); break;
                    case TIPOS_VOID: printf("void"); break;
                }
                for(int i=0;i<aux->symbol->type.pointers;i++)
                    { printf("*"); }
                printf(" %s", aux->symbol->id);
                if(aux->symbol->var.v.array){
                    struct array *arr = aux->symbol->var.v.array;
                    while(arr){
                        printf("[%d]", arr->length);
                        arr = arr->next;
                    }
                }
                printf(", ");
            }
            printf(")\n");

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

// struct parameters* parameterNew(char *id, struct var_type t, struct variable v, int line, int column, struct parameters *next){
//     struct parameters *aux = malloc(sizeof(struct parameters));
//     aux->id = malloc((strlen(id) + 1) * sizeof(char));
//     strcpy(aux->id, id);
//     aux->type = t;
//     aux->param = v;
//     aux->line = line;
//     aux-> column = column;
//     aux->next = next;

//     return aux;
// }

void freeSymbol(Symbol *s){
    if(!s) { return; }

    switch(s->symbol_type){
        case DECLARACAO_VARIAVEL: freeArray(s->var.v.array);           break;
        case DECLARACAO_FUNCAO:   freeParameters(s->var.f.parameters); break;
    }
    if(s->id) { free(s->id); s->id = NULL; }
    free(s);
}

void freeParameters(struct parameters *p){
    if(!p) { return; }

    struct parameters *aux = p;
    while(aux){
        aux = p->next;
        if(p->symbol->id)          { free(p->symbol->id); p->symbol->id = NULL; }
        if(p->symbol->var.v.array) { free(p->symbol->var.v.array); p->symbol->var.v.array = NULL; }
        if(p->symbol)              { free(p->symbol); p->symbol = NULL; }
        if(p)                      { free(p); p = NULL; }
        p = aux;
    }
}

void freeArray(struct array *a){
    if(!a) { return; }

    struct array *aux = a;
    while(aux){
        aux = a->next;
        if(a) { free(a); a = NULL; }
        a = aux;
    }
}
