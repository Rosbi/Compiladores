#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include"commands.h"
#include"types.h"

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
            printf("= ");
            break;
        case ADD_ASSIGN:
            printf("+= ");
            break;
        case SUB_ASSIGN:
            printf("-= ");
            break;

        // expressão condicional (_ ? _ : _)

        // expressão or
        case BIT_OR:
            printf("| ");
            break;

        // expressão or lógico
        case LOG_OR:
            printf("|| ");
            break;

        // expressão and lógico
        case LOG_AND:
            printf("&& ");
            break;

        // expressão xor
        case BIT_XOR:
            printf("^ ");
            break;

        // expressão and
        case BIT_AND:
            printf("& ");
            break;
        // expressão igualdade
        case EQUALS:
            printf("== ");
            break;
        case NOT_EQUALS:
            printf("!= ");
            break;

        // expressão relacional
        case LESS:
            printf("< ");
            break;
        case LEQ:
            printf("<= ");
            break;
        case GEQ:
            printf(">= ");
            break;
        case GREAT:
            printf("> ");
            break;

        // expressão shift
        case RSHIFT:
            printf(">> ");
            break;
        case LSHIFT:
            printf("<< ");
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
            printf("& ");
            break;
        case POINTER_DEFERENCE:
            printf("* ");
            break;
        case UNR_PLUS:
            printf("+ ");
            break;
        case UNR_MINUS:
            printf("- ");
            break;
        case BIT_NOT:
            printf("~ ");
            break;
        case LOG_NOT:
            printf("! ");
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
            printf("%s ", root->node_value.str);
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
        case ADD_ASSIGN:
        case SUB_ASSIGN:
            if(no_l.exp->node_type == STRING || no_l.exp->node_type == CHARACTER){
                state.error = STRING_ASSIGNMENT;
                state.exp = no_l.exp;
            }else if(no_l.exp->node_type == IDENTIFIER){
                state.error = CONST_IDENTIFIER_ASSIGNMENT;
                state.exp = no_l.exp;
            }else{
                state.error = RVALUE_ASSIGNMENT;
                while(root=root->left, root!= NULL){
                    state.exp = root;
                }
            }
            break;

        // expressão condicional (_ ? _ : _)
        case CONDITIONAL_EXP:
            if(no_l.value){
                no_r = evaluateConstExpr(no_r.exp->left);
            }else{
                no_r = evaluateConstExpr(no_r.exp->right);
            }
            state.value = no_r.value;
            break;

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

struct warnings* mergeWarningsLists(struct warnings *w_left, struct warnings *w_right){
    struct warnings *aux;
    if(!w_left)
        { return w_right; }

    for(aux=w_left;aux->next;aux=aux->next);

    aux->next = w_right;
    return aux;
}
struct warnings* warningInsert(struct warnings* list, Error_list warning){
    struct warnings *aux = list;
    if(!aux){
        aux = malloc(sizeof(struct warnings));
    }else{
        for(;aux->next;aux=aux->next);
        aux->next = malloc(sizeof(struct warnings));
        aux = aux->next;
    }

    aux->warning = warning;
    aux->next = NULL;

    return aux;
}

Exp_type_state evaluateExpressionType(Exp_type_state root){
    Exp_type_state state = { NULL, NO_ERROR, NULL };
    if(!root.exp)
        { return state; }
    
    Exp_type_state no_l = { NULL, NO_ERROR, root.exp->left };
    evaluateExpressionType(no_l);
    if(no_l.error != NO_ERROR)
        { return no_l; }
    Exp_type_state no_r = { NULL, NO_ERROR, root.exp->right };
    no_r = evaluateExpressionType(no_r);
    if(no_r.error != NO_ERROR)
        { return no_r; }
    state.exp = root.exp;

    switch(root.exp->node_type){
        // expressão atribuição
        case ASSIGN:
        case ADD_ASSIGN:
        case SUB_ASSIGN:
            
            break;

        // expressão condicional (_ ? _ : _)
        case CONDITIONAL_EXP:
            // if(no_l.value){
            //     no_r = evaluateConstExpr(no_r.exp->left);
            // }else{
            //     no_r = evaluateConstExpr(no_r.exp->right);
            // }
            // state.value = no_r.value;
            break;
        case CONDITIONAL_EXP_THENELSE:
            break;

        // expressão or lógico
        case LOG_OR:
            // state.value = no_l.value > no_r.value;
            break;

        // expressão and lógico
        case LOG_AND:
            // state.value = no_l.value && no_r.value;
            break;

        // expressão or
        case BIT_OR:
            // state.value = no_l.value | no_r.value;
            break;

        // expressão xor
        case BIT_XOR:
            // state.value = no_l.value ^ no_r.value;
            break;

        // expressão and
        case BIT_AND:
            // state.value = no_l.value & no_r.value;
            break;
        // expressão igualdade
        case EQUALS:
            // state.value = no_l.value == no_r.value;
            break;
        case NOT_EQUALS:
            // state.value = no_l.value != no_r.value;
            break;

        // expressão relacional
        case LESS:
            // state.value = no_l.value < no_r.value;
            break;
        case LEQ:
            // state.value = no_l.value <= no_r.value;
            break;
        case GEQ:
            // state.value = no_l.value >= no_r.value;
            break;
        case GREAT:
            // state.value = no_l.value > no_r.value;
            break;

        // expressão shift
        case RSHIFT:
            // state.value = no_l.value >> no_r.value;
            break;
        case LSHIFT:
            // state.value = no_l.value << no_r.value;
            break;

        // expressão aditiva
        case ADD:
            // state.value = no_l.value + no_r.value;
            break;
        case SUB:
            // state.value = no_l.value - no_r.value;
            break;

        // expressão multiplicativa
        case MUL:
            // state.value = no_l.value * no_r.value;
            break;
        case DIV:
            // state.value = no_l.value / no_r.value;
            break;
        case MOD:
            // state.value = no_l.value % no_r.value;
            break;

        // expressão unária
        case ADDRESS:
            // printf("%s ", root->node_value.sym->id);
            break;
        case POINTER_DEFERENCE:
            state.error = matchTypes(UN_DEFERENCE_COMP, state.exp->left->exp_type, state.exp->exp_type);
            if(state.error != NO_ERROR)
                { return state; }
            if(state.exp->left->exp_type.pointers == 0){
                state.error = INVALID_UNR_OPERAND;
            }else{
                state.exp->exp_type = state.exp->left->exp_type;
                state.exp->exp_type.pointers--;
            }
            break;
        case UNR_PLUS:
            state.error = matchTypes(UN_PLUS_COMP, state.exp->left->exp_type, state.exp->exp_type);
            if(state.error != NO_ERROR)
                { return state; }
            state.exp->exp_type = state.exp->left->exp_type;
            break;
        case UNR_MINUS:
            state.error = matchTypes(UN_MINUS_COMP, state.exp->left->exp_type, state.exp->exp_type);
            if(state.error != NO_ERROR)
                { return state; }
            state.exp->exp_type = state.exp->left->exp_type;
            break;
        case BIT_NOT:
            state.error = matchTypes(UN_BIT_NOT_COMP, state.exp->left->exp_type, state.exp->exp_type);
            if(state.error != NO_ERROR)
                { return state; }
            state.exp->exp_type.constant = true;
            state.exp->exp_type.pointers = 0;
            state.exp->exp_type.type     = TIPOS_INT;
            break;
        case LOG_NOT:
            state.error = matchTypes(UN_LOG_NOT_COMP, state.exp->left->exp_type, state.exp->exp_type);
            if(state.error != NO_ERROR)
                { return state; }
            state.exp->exp_type.constant = true;
            state.exp->exp_type.pointers = 0;
            state.exp->exp_type.type     = TIPOS_INT;
            break;

        // expressão pósfixa E unária
        case INC:
            state.error = matchTypes(UN_INC_COMP, state.exp->left->exp_type, state.exp->exp_type);
            if(state.error != NO_ERROR)
                { return state; }
            if(state.exp->left->exp_type.constant){
                state.error = RVALUE_INC_OPERAND;
            }else{
                state.exp->exp_type = state.exp->left->exp_type;
            }
            break;
        case DEC:
            state.error = matchTypes(UN_DEC_COMP, state.exp->left->exp_type, state.exp->exp_type);
            if(state.error != NO_ERROR)
                { return state; }
            if(state.exp->left->exp_type.constant){
                state.error = RVALUE_DEC_OPERAND;
            }else{
                state.exp->exp_type = state.exp->left->exp_type;
            }
            // state.value = no_l.value - 1;
            break;

        // expressão primária
        case NUM_INT:
            state.exp->exp_type.type     = TIPOS_INT;
            state.exp->exp_type.pointers = 0;
            state.exp->exp_type.constant = true;
            break;
        case STRING:
            state.exp->exp_type.type     = TIPOS_CHAR;
            state.exp->exp_type.pointers = 1;
            state.exp->exp_type.constant = true;
            break;
        case CHARACTER:
            state.exp->exp_type.type     = TIPOS_CHAR;
            state.exp->exp_type.pointers = 0;
            state.exp->exp_type.constant = true;
            break;
        case IDENTIFIER:
            state.exp->exp_type = state.exp->node_value.sym->type;
            if(state.exp->node_value.sym->symbol_type == DECLARACAO_VARIAVEL && state.exp->node_value.sym->var.v.constant){
                state.exp->exp_type.constant = true;
            }else{
                state.exp->exp_type.constant = false;
            }
            break;
    }

    if(state.warnings_list){
        state.warnings_list->next = no_r.warnings_list;
    }else{
        state.warnings_list = no_r.warnings_list;
    }
    state.warnings_list = mergeWarningsLists(no_l.warnings_list, state.warnings_list);

    return state;
}

const char* getOperator(int operator){
    switch(operator){
        // expressão atribuição
        case ASSIGN:     return  "=";
        case ADD_ASSIGN: return "+=";
        case SUB_ASSIGN: return "-=";

        // expressão condicional (_ ? _ : _)
        case CONDITIONAL_EXP:          return "?";
        case CONDITIONAL_EXP_THENELSE: return ":";

        // expressão or lógico
        case LOG_OR: return "||";

        // expressão and lógico
        case LOG_AND: return "&&";

        // expressão or
        case BIT_OR: return "|";

        // expressão xor
        case BIT_XOR: return "^";

        // expressão and
        case BIT_AND: return "&";

        // expressão igualdade
        case EQUALS:     return "==";
        case NOT_EQUALS: return "!=";

        // expressão relacional
        case LESS:  return  "<";
        case LEQ:   return "<=";
        case GEQ:   return ">=";
        case GREAT: return  ">";

        // expressão shift
        case RSHIFT: return ">>";
        case LSHIFT: return "<<";

        // expressão aditiva
        case ADD: return "+";
        case SUB: return "-";

        // expressão multiplicativa
        case MUL: return "*";
        case DIV: return "/";
        case MOD: return "%%";

        // expressão unária
        case ADDRESS:           return "&";
        case POINTER_DEFERENCE: return "*";
        case UNR_PLUS:          return "+";
        case UNR_MINUS:         return "-";
        case BIT_NOT:           return "~";
        case LOG_NOT:           return "!";

        // expressão pósfixa E unária
        case INC: return "++";
        case DEC: return "--";
        default: return "OPERATOR NOT FOUND";
    }
}
char* getType(struct var_type type){
    char *str = malloc((5 + type.pointers) * sizeof(char));
    switch(type.type){
        case TIPOS_INT:  strcpy(str, "int");  break;
        case TIPOS_CHAR: strcpy(str, "char"); break;
        case TIPOS_VOID: strcpy(str, "void"); break;
    }
    for(int i=0;i<type.pointers;i++)
        { strcat(str, "*"); }
    return str;
}

void deleteTree(Expression *root){
    if(!root)
        { return; }
    
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}
