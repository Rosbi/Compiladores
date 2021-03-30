#ifndef HASH_TABLE
#define HASH_TABLE

#include<stdbool.h>
#include<stdarg.h>

typedef void* HashTable;	//Ponteiro genérico para uma tabela de espalhamento
typedef void* Info;		//Ponteiro genérico para um dado qualquer

//Cria uma nova tabela de tamanho n;
//Pré-requisito: n maior que 0;
//Pós condição: retorna um ponteiro para a tabela criada.
HashTable criaTabela(int n);

//Insere um registro em uma posição determinada por uma função interna (hashFunction);
//Pré-requisito: existir a tabela e chave não nula;
//Pós condição: novo registro {"chave" => Info} na tabela, retorna a posição onde o registro foi inserido.
int insereRegistro(HashTable, char* chave, Info);

//Retorna o primeiro registro referente à chave
//Pré-requisito: tabela existe e chave não nula;
//Pós condição: -.
Info getPrimeiroRegistro(HashTable, char* key);

//Retorna um vetor com todos os registros referentes à chave;
//Pré-requisito: tabela existe e chave não nula;
//Pós condição: -;
//Nota: O vetor é alocado na memória, portanto é necessário dar free() no ponteiro retornado.
Info* getVetorRegistros(HashTable, char* key, int* tamanhoDoVetor);

//Exclui a chave 'key' da tabela, e retorna a posição excluída (-1 caso não encontre);
//Pré-requisito: tabela existe e chave não nula;
//Pós condição: chave excluída da tabela.
int removeChave(HashTable, char* key);

//Verifica se existe a chave;
//Pré-requisito: tabela existe e chave não nula;
//Pós condição: -.
bool existeChave(HashTable, char* key);

//Aplica a função a todos os registro da tabela;
//Pré-requisito: tabela existir;
//Pós condição: função aplicada aos registros.
void HshTblMap(HashTable, void (*func)(Info, va_list), ...);

//Deleta a tabela e todos os seus registros;
//Pré-requisito: tabela existe;
//Pós condição: tabela não existe mais.
void* hashtableFinalizar(HashTable);

void printTable(HashTable tabela);
#endif