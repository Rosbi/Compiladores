#include"ast_symbols.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"commands.h" //tirar

struct _program_table Program_Table;

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
void printFunctionBody(Command_list* commands){
    if(!commands)
        { return; }

    switch(commands->com_type){
        case COM_IF:
            printf("if(");
            RpnWalk(commands->com.if_com->exp);
            printf(")");
            printFunctionBody(commands->com.if_com->then_com);
            printf("else");
            printFunctionBody(commands->com.if_com->else_com);
            break;
        case COM_WHILE:
            printf("while(");
            RpnWalk(commands->com.while_com->exp);
            printf(")");
            printFunctionBody(commands->com.while_com->commands);
            break;
        case COM_FOR:
            printf("for(");
            RpnWalk(commands->com.for_com->exp_init);
            printf(";");
            RpnWalk(commands->com.for_com->exp_check);
            printf(";");
            RpnWalk(commands->com.for_com->exp_update);
            printf(")");
            printFunctionBody(commands->com.for_com->commands);
            break;
        case COM_RETURN:
            printf("return ");
            RpnWalk(commands->com.return_com);
            printf(";\n");
            break;
        case COM_EXP:
            RpnWalk(commands->com.exp_com);
            printf("\n");
            break;
        case COM_BLOCK:
            printf("{\n");
            printFunctionBody(commands->com.block);
            printf("}\n");
            break;
        case COM_PRINTF:
            printf("printf(\"%s\", ", commands->com.printf_com->string);
            RpnWalk(commands->com.printf_com->exp);
            printf(")\n");
            break;
        case COM_SCANF:
            printf("scanf(\"%s\", &%s)\n", commands->com.scanf_com->string, commands->com.scanf_com->var);
            break;
        case COM_EXIT:
            printf("exit(");
            RpnWalk(commands->com.exit_com);
            printf(")\n");
            break;
        default:
            printf(" ++ shouldn't have come here ++ \n");
            return;
    }

    printFunctionBody(commands->next);
}

Symbol* symbolNew(int symbol_type, char *id, Var_type t, union symbol_union su, int line, int column){
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

// struct parameters* parameterNew(char *id, Var_type t, struct variable v, int line, int column, struct parameters *next){
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

Command_list* commandNew(int command_type, ...){
    Command_list *com = malloc(sizeof(Command_list));
    va_list args;
    va_start(args, command_type);
    com->com_type = command_type;

    switch(command_type){
        case COM_IF:
        {
            com->com.if_com = malloc(sizeof(struct if_else_t));

            com->com.if_com->exp = va_arg(args, struct expression*);
            com->com.if_com->then_com = va_arg(args, struct command_list*);
            com->com.if_com->else_com = va_arg(args, struct command_list*);
            break;
        }
        case COM_WHILE:
        {
            com->com.while_com = malloc(sizeof(struct while_t));

            com->com.while_com->exp = va_arg(args, struct expression*);
            com->com.while_com->commands = va_arg(args, struct command_list*);
            break;
        }
        case COM_FOR:
        {
            com->com.for_com = malloc(sizeof(struct for_t));

            com->com.for_com->exp_init = va_arg(args, struct expression*);
            com->com.for_com->exp_check = va_arg(args, struct expression*);
            com->com.for_com->exp_update = va_arg(args, struct expression*);
            com->com.for_com->commands = va_arg(args, struct command_list*);
            break;
        }
        case COM_RETURN:
        {
            com->com.return_com = va_arg(args, struct expression*);
            break;
        }
        case COM_EXP:
        {
            com->com.exp_com = va_arg(args, struct expression*);
            break;
        }
        case COM_BLOCK:
        {
            com->com.block = va_arg(args, struct command_list*);
            break;
        }
        case COM_PRINTF:
        {
            com->com.printf_com = malloc(sizeof(struct printf_t));

            com->com.printf_com->string = va_arg(args, char*);
            com->com.printf_com->exp    = va_arg(args, struct expression*);
            break;
        }
        case COM_SCANF:
        {
            com->com.scanf_com = malloc(sizeof(struct scanf_t));

            com->com.scanf_com->string = va_arg(args, char*);
            com->com.scanf_com->var    = va_arg(args, char*);
            break;
        }
        case COM_EXIT:
        {
            com->com.exit_com = va_arg(args, struct expression*);
            break;
        }
    }

    com->next = NULL;
    va_end(args);

    return com;
}

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
