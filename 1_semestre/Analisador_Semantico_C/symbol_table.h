#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include<stdbool.h>
// #include<semantico.tab.h>
#include"hashTable.h"
//tipos
// int;
// char;
// void;

enum tipos {
    TIPOS_INT,
    TIPOS_CHAR,
    TIPOS_VOID,
    TIPOS_VARIAVEL,
    TIPOS_FUNCAO
};

//tipos de variáveis, incluindo ponteiros
struct var_type{
    int type;
    int pointers;
};

//possíveis informações de uma variável
struct variable{
    struct array{
        int length;
        struct array *next;
    } *array;
    bool constant;
    union{
        int i;
        char c;
    }value;

    int line;
    int column;
};

//possíveis informações de uma função
struct function_prototype{
    struct parameters{
        struct variable param;
        struct parameters *next;
    } *parameters;

    int line;
    int column;
};

typedef struct symbol{
    int symbol_type;
    char* id;
    struct var_type type;
    union{
        struct variable v;
        struct function_prototype f;
    } var;
}Symbol;

struct function_definition{
    HashTable Local_Symbol_Table;
    char *name;
    struct var_type return_type;
    struct function_prototype f;
};

struct{
    HashTable Global_Symbol_Table;
    struct function_list{
        struct function_definition function;
        struct function_list *next;
    } *head;
} Program_Table;

void printSymbol(Symbol);

#endif
