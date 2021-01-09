#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include"commands.h"

Expression* expressionNew(int node_t, union expression_union value, Expression *left, Expression *right, int line, int column){
    Expression *aux = malloc(sizeof(Expression));
    aux->left = left;
    aux->right = right;
    aux->node_type = node_t;
    aux->node_value = value;
    aux->line = line;
    aux->column = column;
    return aux;
}

void RpnWalk(Expression *root){
    if(!root)
        { return; }

    RpnWalk(root->left);
    RpnWalk(root->right);
    switch(root->node_type){
        // expressão atribuição
        case ASSIGN:
            printf("%s ", root->node_value.sym->id);
            break;
        case ADD_ASSIGN:
            printf("%s ", root->node_value.sym->id);
            break;
        case SUB_ASSIGN:
            printf("%s ", root->node_value.sym->id);
            break;

        // expressão condicional (_ ? _ : _)

        // expressão or
        case BIT_OR:
            printf("%s ", root->node_value.sym->id);
            break;

        // expressão or lógico
        case LOG_OR:
            printf("%s ", root->node_value.sym->id);
            break;

        // expressão and lógico
        case LOG_AND:
            printf("%s ", root->node_value.sym->id);
            break;

        // expressão xor
        case BIT_XOR:
            printf("%s ", root->node_value.sym->id);
            break;

        // expressão and
        case BIT_AND:
            printf("%s ", root->node_value.sym->id);
            break;
        // expressão igualdade
        case EQUALS:
            printf("%s ", root->node_value.sym->id);
            break;
        case NOT_EQUALS:
            printf("%s ", root->node_value.sym->id);
            break;

        // expressão relacional
        case LESS:
            printf("%s ", root->node_value.sym->id);
            break;
        case LEQ:
            printf("%s ", root->node_value.sym->id);
            break;
        case GEQ:
            printf("%s ", root->node_value.sym->id);
            break;
        case GREAT:
            printf("%s ", root->node_value.sym->id);
            break;

        // expressão shift
        case RSHIFT:
            printf("%s ", root->node_value.sym->id);
            break;
        case LSHIFT:
            printf("%s ", root->node_value.sym->id);
            break;

        // expressão aditiva
        case ADD:
            printf("+ ");
            break;
        case SUB:
            printf("- ");
            break;

        // expressão multiplicativa
        case MUL:
            printf("* ");
            break;
        case DIV:
            printf("/ ");
            break;
        case MOD:
            printf("%c ", '%');
            break;

        // expressão unária
        case ADDRESS:
            printf("%s ", root->node_value.sym->id);
            break;
        case POINTER_DEFERENCE:
            printf("%s ", root->node_value.sym->id);
            break;
        case UNR_PLUS:
            printf("%s ", root->node_value.sym->id);
            break;
        case UNR_MINUS:
            printf("%s ", root->node_value.sym->id);
            break;
        case BIT_NOT:
            printf("%s ", root->node_value.sym->id);
            break;
        case LOG_NOT:
            printf("%s ", root->node_value.sym->id);
            break;

        // expressão pósfixa E unária
        case INC:
            printf("1 + ");
            break;
        case DEC:
            printf("1 - ");
            break;


        // expressão primária
        case NUM_INT:
            printf("%d ", root->node_value.num);
            break;
        case STRING:
            printf("\"%s\" ", root->node_value.str);
            break;
        case CHARACTER:
            printf("'%c' ", root->node_value.chr);
            break;
        case IDENTIFIER:
            printf("%s ", root->node_value.sym->id);
            break;
    }
}

int evaluateConstExpr(Expression *root){
    int result = 0;
    int no_l = evaluateConstExpr(root->left);
    int no_r = evaluateConstExpr(root->right);
    switch(root->node_type){
        // expressão atribuição
        case ASSIGN:
            printf("%s ", root->node_value.sym->id);
            break;
        case ADD_ASSIGN:
            printf("%s ", root->node_value.sym->id);
            break;
        case SUB_ASSIGN:
            printf("%s ", root->node_value.sym->id);
            break;

        // expressão condicional (_ ? _ : _)

        // expressão or
        case BIT_OR:
            printf("%s ", root->node_value.sym->id);
            break;

        // expressão or lógico
        case LOG_OR:
            printf("%s ", root->node_value.sym->id);
            break;

        // expressão and lógico
        case LOG_AND:
            printf("%s ", root->node_value.sym->id);
            break;

        // expressão xor
        case BIT_XOR:
            printf("%s ", root->node_value.sym->id);
            break;

        // expressão and
        case BIT_AND:
            printf("%s ", root->node_value.sym->id);
            break;
        // expressão igualdade
        case EQUALS:
            printf("%s ", root->node_value.sym->id);
            break;
        case NOT_EQUALS:
            printf("%s ", root->node_value.sym->id);
            break;

        // expressão relacional
        case LESS:
            printf("%s ", root->node_value.sym->id);
            break;
        case LEQ:
            printf("%s ", root->node_value.sym->id);
            break;
        case GEQ:
            printf("%s ", root->node_value.sym->id);
            break;
        case GREAT:
            printf("%s ", root->node_value.sym->id);
            break;

        // expressão shift
        case RSHIFT:
            printf("%s ", root->node_value.sym->id);
            break;
        case LSHIFT:
            printf("%s ", root->node_value.sym->id);
            break;

        // expressão aditiva
        case ADD:
            result = no_l + no_r;
            break;
        case SUB:
            result = no_l - no_r;
            break;

        // expressão multiplicativa
        case MUL:
            result = no_l * no_r;
            break;
        case DIV:
            result = no_l  / no_r;
            break;
        case MOD:
            result = no_l % no_r;
            break;

        // expressão unária
        case ADDRESS:
            printf("%s ", root->node_value.sym->id);
            break;
        case POINTER_DEFERENCE:
            printf("%s ", root->node_value.sym->id);
            break;
        case UNR_PLUS:
            printf("%s ", root->node_value.sym->id);
            break;
        case UNR_MINUS:
            printf("%s ", root->node_value.sym->id);
            break;
        case BIT_NOT:
            printf("%s ", root->node_value.sym->id);
            break;
        case LOG_NOT:
            printf("%s ", root->node_value.sym->id);
            break;

        // expressão pósfixa E unária
        case INC:
            printf("1 + ");
            break;
        case DEC:
            printf("1 - ");
            break;


        // expressão primária
        case NUM_INT:
            printf("%d ", root->node_value.num);
            break;
        case STRING:
            printf("\"%s\" ", root->node_value.str);
            break;
        case CHARACTER:
            printf("'%c' ", root->node_value.chr);
            break;
        case IDENTIFIER:
            printf("%s ", root->node_value.sym->id);
            break;
    }
    return result;
}

void deleteTree(Expression *root){
    if(!root)
        { return; }
    
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}
