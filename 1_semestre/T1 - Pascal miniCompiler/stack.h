#ifndef DATASTRUCT_STACK_H
#define DATASTRUCT_STACK_H

#include<stdbool.h>

typedef void* Stack;
typedef int StackElement;

/*
 * Implementação trivial de pilha em C, utilizando double-linked list 
 * Funções de push, pop, e create levam tempo O(1)
 * Funções dump e free levam tempo tempo O(n)
*/

//Istancia a pilha.
//O parametro da funcao é o endereço da pilha
//Retorna -1 se houve erro na criação, 0 com êxito
int stackCreate(Stack *);

//Insere um elemento na pilha
//Retorna -1 se houve erro na criação, 0 com êxito
int stackPush(Stack, StackElement);

//Retira um elemento da pilha, e o devolve
StackElement stackPop(Stack);

//
bool stackIsEmpty(Stack);

//Retira todos os elementos da pilha, mas ela ainda existe e pode ser utilizada
void stackDump(Stack);

//Exclui todos os elementos da pilha, e libera toda a memória da estrutura
//O parametro da funcao é o endereço da pilha
void stackFree(Stack *);

#endif