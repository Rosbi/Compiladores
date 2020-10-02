#include<stdio.h>
#include<stdlib.h>
#include"stack.h"

/*
 * Essa implementação utiliza uma pilha que pode crescer indefinidamente
 *  graças à utilização de uma lista encadeada para guardar os elementos,
 *  porém tem um gasto maior de memória em relação à uma implementação com vetor
*/

//Estrutura de lista duplamente encadeada para guardar os elementos da pilha
struct stackNode{
	StackElement element;
	struct stackNode* next;
	struct stackNode* prev;
};

//Estrutura da pilha, possui ponteiros para o primeiro e últimos nós da lista,
// e também a quantidade de elementos dentro da lista
struct stack{
	struct stackNode* first;
	struct stackNode* top;
	int size;
};

int stackCreate(Stack *stck){
	struct stack **s = (struct stack**)stck;

	//Aloca espaço para a pilha, e retorna -1 se malloc der erro
	*s = malloc(sizeof(struct stack));
	if(!(*s)){
		return -1;
	}

	//Atribui os valores iniciais para os atributos da pilha
	(*s)->size = 0;
	(*s)->first = NULL;
	(*s)->top = NULL;
	return 0;
}

int stackPush(Stack stck, StackElement elem){
	struct stack *s = (struct stack*)stck;

	struct stackNode *aux = malloc(sizeof(struct stackNode));
	if(!aux){
		return -1;
	}
	aux->element = elem;
	aux->next = NULL;
	aux->prev = s->top;

	if(s->first==NULL){
		s->first = aux;
	}else{
		s->top->next = aux;
	}

	s->top = aux;
	s->size = s->size+1;
	return 0;
}

StackElement stackPop(Stack stck){
	struct stack *s = (struct stack*)stck;
	if(s->first==NULL){
		return -1;
	}

	StackElement se;
	struct stackNode *aux = s->top;

	se = aux->element;
	s->top = s->top->prev;
	free(aux);

	if(s->top==NULL){
		s->first = NULL;
	}else{
		s->top->next = NULL;
	}
	
	s->size = s->size-1;
	return se;
}

bool stackIsEmpty(Stack stck){
	struct stack *s = (struct stack*)stck;
	return s->size == 0 ? true : false;
}

int stackSize(Stack stck){
	struct stack *s = (struct stack*)stck;
	return s->size;
}

void stackDump(Stack stck){
	struct stack *s = (struct stack*)stck;
	struct stackNode *aux = s->first;
	struct stackNode *auxNext;

	while(aux!=NULL){
		auxNext = aux->next;
		aux->prev = NULL;
		aux->next = NULL;
		free(aux);
		aux = auxNext;
	}

	s->first=NULL;
	s->top=NULL;
	s->size = 0;
}

void stackFree(Stack *stck){
	struct stack **s = (struct stack**)stck;
	stackDump(*stck);
	free(*s);
	*s = NULL;
}




//
char* tokenStringify(int);

void printStack(Stack stck){
	struct stack *s = (struct stack*)stck;
	struct stackNode *aux = s->first;
	printf("stack: ");
	while(aux != NULL){
		printf("%s ", tokenStringify(aux->element));
		aux = aux->next;
	}
	printf("\n");
}
