#ifndef STACK_H
#define STACK_H

typedef int* Adjacency;

typedef struct StackElement{
    Adjacency a;
    int reg;
    struct StackElement *next;
}StackElement;

typedef struct{
    StackElement *first;
    StackElement *last;
}Stack;

Stack create_stack();
Stack push(Stack stck, Adjacency adj, int reg);
Adjacency pop(Stack *stck, int *reg);

void print_stack(Stack stck);

#endif
