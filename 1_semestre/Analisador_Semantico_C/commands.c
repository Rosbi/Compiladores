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
            printf("%s ", root->node_value.chr);
            break;
        case IDENTIFIER:
            printf("%s ", root->node_value.sym->id);
            break;
    }
}

Const_expr_state evaluateConstExpr(Expression *root){
    Const_expr_state state = { 0, NO_ERROR, root };
    if(!root)
        { return state; }

    Const_expr_state no_l = evaluateConstExpr(root->left);
    if(no_l.error != NO_ERROR)
        { return no_l; }
    Const_expr_state no_r = evaluateConstExpr(root->right);
    if(no_r.error != NO_ERROR)
        { return no_r; }

    switch(root->node_type){
        // expressão atribuição
        case ASSIGN:
            state.value = no_r.value;
            break;
        case ADD_ASSIGN:
            state.value = no_r.value;
            break;
        case SUB_ASSIGN:
            state.value = no_r.value;
            break;

        // expressão condicional (_ ? _ : _)

        // expressão or lógico
        case LOG_OR:
            state.value = no_l.value > no_r.value;
            break;

        // expressão and lógico
        case LOG_AND:
            state.value = no_l.value && no_r.value;
            break;

        // expressão or
        case BIT_OR:
            state.value = no_l.value | no_r.value;
            break;

        // expressão xor
        case BIT_XOR:
            state.value = no_l.value ^ no_r.value;
            break;

        // expressão and
        case BIT_AND:
            state.value = no_l.value & no_r.value;
            break;
        // expressão igualdade
        case EQUALS:
            state.value = no_l.value == no_r.value;
            break;
        case NOT_EQUALS:
            state.value = no_l.value != no_r.value;
            break;

        // expressão relacional
        case LESS:
            state.value = no_l.value < no_r.value;
            break;
        case LEQ:
            state.value = no_l.value <= no_r.value;
            break;
        case GEQ:
            state.value = no_l.value >= no_r.value;
            break;
        case GREAT:
            state.value = no_l.value > no_r.value;
            break;

        // expressão shift
        case RSHIFT:
            state.value = no_l.value >> no_r.value;
            break;
        case LSHIFT:
            state.value = no_l.value << no_r.value;
            break;

        // expressão aditiva
        case ADD:
            state.value = no_l.value + no_r.value;
            break;
        case SUB:
            state.value = no_l.value - no_r.value;
            break;

        // expressão multiplicativa
        case MUL:
            state.value = no_l.value * no_r.value;
            break;
        case DIV:
            if(no_r.value == 0){
                state.error = DIVISION_BY_ZERO;
            }else{
                state.value = no_l.value / no_r.value;
            }
            break;
        case MOD:
            state.value = no_l.value % no_r.value;
            break;

        // expressão unária
        case ADDRESS:
            // printf("%s ", root->node_value.sym->id);
            break;
        case POINTER_DEFERENCE:
            // printf("%s ", root->node_value.sym->id);
            break;
        case UNR_PLUS:
            state.value = no_l.value;
            break;
        case UNR_MINUS:
            state.value = no_l.value * (-1);
            break;
        case BIT_NOT:
            state.value = ~no_l.value;
            break;
        case LOG_NOT:
            state.value = !no_l.value;
            break;

        // expressão pósfixa E unária
        case INC:
            state.value = no_l.value + 1;
            break;
        case DEC:
            state.value = no_l.value - 1;
            break;


        // expressão primária
        case NUM_INT:
            state.value = root->node_value.num;
            break;
        case STRING:
            printf("\"%s\" ", root->node_value.str);
            break;
        case CHARACTER:
            state.value = root->node_value.chr[1];
            break;
        case IDENTIFIER:
            if(root->node_value.sym->symbol_type == DECLARACAO_VARIAVEL){
                if(root->node_value.sym->var.v.constant){
                    state.value = root->node_value.sym->var.v.value.i;
                }else{
                    state.error = INITIALIZER_NOT_CONST;
                }
            }
            break;
    }
    return state;
}

void deleteTree(Expression *root){
    if(!root)
        { return; }
    
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}
