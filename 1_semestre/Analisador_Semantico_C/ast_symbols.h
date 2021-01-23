#ifndef AST_SYMBOLS_H
#define AST_SYMBOLS_H

#include<stdbool.h>
// #include<semantico.tab.h>
#include"hashTable.h"
#include<stdarg.h>

typedef struct symbol Symbol;
typedef struct command_list Command_list;

enum tipos {
    //tipos de variável
    TIPOS_INT,
    TIPOS_CHAR,
    TIPOS_VOID,

    //tipos de declaração
    DECLARACAO_VARIAVEL,
    DECLARACAO_FUNCAO,

    //tipos de comandos
    // COM_DO_WHILE,
    COM_IF,
    COM_WHILE,
    COM_FOR,
    COM_RETURN,
    COM_EXP,
    COM_BLOCK,
};

//tipos de variáveis, incluindo ponteiros
struct var_type{
    int type;
    int pointers;
    bool constant;
};

//representação rpn de uma expressão
typedef struct expression{
    struct expression *left;
    struct expression *right;
    int node_type;
    union expression_union{
        int num;
        char *chr;
        char *str;
        Symbol *sym;
    } node_value;
    struct var_type exp_type;

    int line;
    int column;
}Expression;
struct while_t{
    struct expression *exp;
    struct command_list *commands;
};
struct if_else_t{
    struct expression *exp;
    struct command_list *then_com;
    struct command_list *else_com;
};
struct for_t{
    struct expression *exp_init;
    struct expression *exp_check;
    struct expression *exp_update;
    struct command_list *commands;
};
// struct return_t{
//     struct expression *exp_return;
// }

//struct genérica para cada comando
struct command_list{
    int com_type;
    union{
        Expression *exp_com;
        struct if_else_t *if_com;
        struct while_t *while_com;
        struct for_t *for_com;
        // struct return_t *return;
        struct expression *return_com;
        struct command_list *block;
    } com;
    struct command_list *next;
};

//possíveis informações de uma variável
struct variable{
    struct array{
        int length;
        // Expression *exp;
        struct array *next;
    } *array;
    bool constant;
    union{
        int i;
        char c;
    }value;
    int arr_dimensions;
};

//possíveis informações de uma função
struct function_prototype{
    bool has_definition;
    struct parameters{
        // char *id;
        // struct var_type type;
        // struct variable param;
        // int line;
        // int column;
        struct symbol *symbol;
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
    struct command_list *commands_head;
};

//struct principal do programa
struct{
    HashTable Global_Symbol_Table;
    struct function_list{
        struct function_definition function;
        struct function_list *next;
    } *head;
} Program_Table;

void printSymbol(Symbol*);
void printFunctionBody(Command_list*);

Symbol* symbolNew(int symbol_type, char *id, struct var_type t, union symbol_union su, int line, int column);
// struct parameters* parameterNew(char *id, struct var_type t, struct variable v, int line, int column, struct parameters *next);
Command_list* commandNew(int command_type, ...);

void freeSymbol(Symbol *);
void freeParameters(struct parameters *p);
void freeArray(struct array *a);

#endif
