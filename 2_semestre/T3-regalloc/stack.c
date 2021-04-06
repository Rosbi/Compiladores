#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include"stack.h"

Stack create_stack(){
    Stack s = {NULL, NULL};
    
    return s;
}

Stack push(Stack stck, Adjacency adj, int reg){
    StackElement *aux = stck.first;
    
    if(!aux){
        stck.first       = malloc(sizeof(StackElement));
        stck.first->a    = adj;
        stck.first->reg  = reg;
        stck.first->next = NULL;
        stck.last        = stck.first;
        return stck;
    }

    while(aux->next){
        aux = aux->next;
    }
    aux->next       = malloc(sizeof(StackElement));
    aux->next->a    = adj;
    aux->next->reg  = reg;
    aux->next->next = NULL;
    stck.last       = aux->next;
    return stck;
}

Adjacency pop(Stack *stck, int *reg){
    Adjacency adj;

    if(stck->first == NULL){
        return NULL;
    }

    if(stck->first == stck->last){
        adj  = stck->first->a;
        *reg = stck->first->reg;
        free(stck->first);
        stck->last = stck->first = NULL;
        return adj;
    }

    StackElement *aux1 = stck->first;
    StackElement *aux2 = aux1;
    while(aux1->next){
        aux2 = aux1;
        aux1 = aux1->next;
    }
    adj  = aux1->a;
    *reg = aux1->reg;
    free(aux1);
    stck->last = aux2;
    stck->last->next = NULL;
    return adj;
}

void print_stack(Stack stck){
    StackElement *aux = stck.first;

    while(aux){
        printf("%d -> ", aux->reg);
        aux=aux->next;
    }
    printf("\n");
}

/* REMOVE
int main(){
    Stack s = create_stack();
    int* a = malloc(sizeof(int)*3);
    int* b = malloc(sizeof(int)*3);
    int* c = malloc(sizeof(int)*3);
    for(int i=0;i<3;i++){ a[i]=i+0; }
    for(int i=0;i<3;i++){ b[i]=i+3; }
    for(int i=0;i<3;i++){ c[i]=i+6; }
    s = push(s, b);
    s = push(s, a);
    s = push(s, c);

    a = pop(&s);
    for(int i=0;i<3;i++){ printf("%d ", a[i]); }
    printf("\n");
    a = pop(&s);
    for(int i=0;i<3;i++){ printf("%d ", a[i]); }
    printf("\n");
    a = pop(&s);
    for(int i=0;i<3;i++){ printf("%d ", a[i]); }
    printf("\n");
}
*/
