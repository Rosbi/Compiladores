#ifndef AST_SYMBOLS_H
#define AST_SYMBOLS_H

#include<stdbool.h>
// #include<semantico.tab.h>
#include"hashTable.h"

typedef struct symbol Symbol;

enum tipos {
    TIPOS_INT,
    TIPOS_CHAR,
    TIPOS_VOID,
    DECLARACAO_VARIAVEL,
    DECLARACAO_FUNCAO,
    COM_IF,
    COM_WHILE
    //...
};

//representação rpn de uma expressão
typedef struct expression{
    struct expression *left;
    struct expression *right;
    int node_type;
    union expression_union{
        int num;
        char chr;
        char *str;
        Symbol *sym;
    } node_value;

    int line;
    int column;
}Expression;

//struct genérica para cada comando
struct command{
    int com_type;
    union{
        Expression e;
    } com;
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
};

//possíveis informações de uma função
struct function_prototype{
    struct parameters{
        struct variable param;
        struct parameters *next;
    } *parameters;
};

//informações de símbolos (variáveis e funções)
struct symbol{
    int symbol_type;
    char* id;
    struct var_type type;
    union symbol_union{
        struct variable v;
        struct function_prototype f;
    } var;

    int line;
    int column;
};

//definição da função, com sua próŕia tabela de símbolos
struct function_definition{
    HashTable Local_Symbol_Table;
    char *name;
    struct var_type return_type;
    struct function_prototype f;
};

//struct principal do programa
struct{
    HashTable Global_Symbol_Table;
    struct function_list{
        struct function_definition function;
        struct function_list *next;
    } *head;
} Program_Table;

void printSymbol(Symbol);
Symbol* symbolNew(int symbol_type, char *id, struct var_type t, union symbol_union su, int line, int column);

#endif
