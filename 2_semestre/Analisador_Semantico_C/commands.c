#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include"commands.h"
#include"types.h"

void printLine(FILE* file, int linha);

enum type_sizes { SAME_SIZE, LEFT_BIGGER, RIGHT_BIGGER };
int compareTypesSize(Var_type v1, Var_type v2);

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
        case SUBSCRIPT:     printf("[] "); break;
        case FUNCTION_CALL: printf("() "); break;

        case COMMA_SEPARATOR:
            printf(", ");
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

extern FILE* in_file;
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
        case RSHIFT: case LSHIFT:{
            struct warnings w = { 0, state.exp, NULL };
            int error;
            switch(root->node_type){
                case LSHIFT:
                    state.value = no_l.value << no_r.value;
                    w.warning = LSHIFT_EXCEEDS_SIZE_W;
                    error = LSHIFT_NEGATIVE;
                    break;
                case RSHIFT:
                    state.value = no_l.value >> no_r.value;
                    w.warning = RSHIFT_EXCEEDS_SIZE_W;
                    error = RSHIFT_NEGATIVE;
                    break;
            }
            if(no_r.value >= TIPOS_INT){
                printWarnings(&w, in_file);
            }else if(no_r.value < 0){
                state.error = error;
            }
            break;
        }
        // case LSHIFT:
        //     state.value = no_l.value << no_r.value;
        //     if(no_r.value >= TIPOS_INT){
        //         state.warning = LSHIFT_EXCEEDS_SIZE_W;
        //     }else if(no_r.value < 0){
        //         state.error = LSHIFT_NEGATIVE;
        //     }
        //     break;

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
            state.value = 0;
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

void printWarnings(struct warnings* warnings_list, FILE* lines_file){
    struct warnings *aux;
    int coluna, linha;
    char *warning_msg = malloc(128 * sizeof(char));
    for(aux=warnings_list;aux;aux=aux->next){
        switch(aux->warning){
            case LSHIFT_EXCEEDS_SIZE_W:
                sprintf(warning_msg, "left shift count >= width of type");
                break;
            case RSHIFT_EXCEEDS_SIZE_W:
                sprintf(warning_msg, "right shift count >= width of type");
                break;
            case INDEX_OUT_OF_BOUNDS:
                sprintf(warning_msg, "array index out of bounds");
                break;
            case WRONG_TYPE_COMPARISON_W:
                sprintf(warning_msg, "comparison between '%s' and '%s' operator '%s'",
                    getType(aux->exp->left->exp_type), getType(aux->exp->right->exp_type), getOperator(aux->exp->node_type));
                break;
            case CONDITIONAL_TYPE_MISSMATCH_W:
                sprintf(warning_msg, "'%s'/'%s' type mismatch in conditional expression",
                    getType(aux->exp->left->exp_type), getType(aux->exp->right->exp_type));
                break;
            case DIFFERENT_CAST_SIZE_W:
                sprintf(warning_msg, "cast from '%s' to '%s' of different size",
                    getType(aux->exp->left->exp_type), getType(aux->exp->exp_type));
                break;
            default:
                sprintf(warning_msg, "algo deu errado ao imprimir essa warning");
                break;
        }
        coluna = aux->exp->column;
        linha = aux->exp->line;

        printf("warning:%d:%d: ", linha, coluna);
        printf("%s\n", warning_msg);

        printLine(lines_file, linha);
        for(int i=1;i<coluna;i++)
            { printf(" "); }
        printf("^\n");
    }
}

struct warnings* mergeWarningsLists(struct warnings *w_left, struct warnings *w_right){
    struct warnings *aux;
    if(!w_left)
        { return w_right; }

    for(aux=w_left;aux->next;aux=aux->next);

    aux->next = w_right;
    return w_left;
}
struct warnings* warningInsert(struct warnings* list, Error_list warning, Expression *exp){
    struct warnings *aux = list;
    if(!aux){
        aux = malloc(sizeof(struct warnings));
    }else{
        for(;aux->next;aux=aux->next);
        aux->next = malloc(sizeof(struct warnings));
        aux = aux->next;
    }

    aux->warning = warning;
    aux->exp = exp;
    aux->next = NULL;

    return aux;
}
void freeWarningList(struct warnings *warnings_list){
    if(!warnings_list){
        return;
    }

    struct warnings* aux;
    while(aux=warnings_list, warnings_list){
        warnings_list = aux->next;
        free(aux);
    }
}

Exp_type_state evalExpTypeAndHandleWarnings(Expression *root, FILE* read_warning_line){
    Exp_type_state state = {NULL, NO_ERROR, root };
    state = evaluateExpressionType(state);
    printWarnings(state.warnings_list, read_warning_line);
    freeWarningList(state.warnings_list);
    return state;
}

Exp_type_state evaluateExpressionType(Exp_type_state root){
    Exp_type_state state = { NULL, NO_ERROR, root.exp };
    if(!root.exp)
        { return state; }

    Exp_type_state no_l = { NULL, NO_ERROR, root.exp->left };
    no_l = evaluateExpressionType(no_l);
    if(no_l.error != NO_ERROR && no_l.error < WARNINGS_START)
        { return no_l; }
    Exp_type_state no_r = { NULL, NO_ERROR, root.exp->right };
    no_r = evaluateExpressionType(no_r);
    if(no_r.error != NO_ERROR && no_r.error < WARNINGS_START){
        no_r.warnings_list = mergeWarningsLists(no_l.warnings_list, no_r.warnings_list);
        return no_r;
    }

    switch(root.exp->node_type){
        case ASSIGN: case ADD_ASSIGN: case SUB_ASSIGN:
        case LOG_OR: case LOG_AND: case BIT_OR: case BIT_XOR: case BIT_AND:
        case EQUALS: case NOT_EQUALS: case LESS: case LEQ: case GEQ: case GREAT:
        case ADD: case SUB: case MUL: case DIV: case MOD:
        case ADDRESS:
        case UNR_PLUS: case UNR_MINUS:
        case BIT_NOT: case LOG_NOT:
        case INC: case DEC:{
            switch(root.exp->node_type){
                case ASSIGN: case ADD_ASSIGN: case SUB_ASSIGN:{
                    if(no_l.exp->node_type == STRING || no_l.exp->node_type == CHARACTER){
                        state.exp->node_value.str = no_l.exp->node_value.str;
                        state.error = STRING_ASSIGNMENT;
                        break;
                    }else if(state.exp->left->exp_type.constant){
                        state.error = RVALUE_ASSIGNMENT;
                        break;
                    }
                    switch(root.exp->node_type){
                        case ASSIGN:     state.error = matchTypes(ASSIGN_COMP,     state.exp->left->exp_type, state.exp->right->exp_type); break;
                        case ADD_ASSIGN: state.error = matchTypes(ADD_ASSIGN_COMP, state.exp->left->exp_type, state.exp->right->exp_type); break;
                        case SUB_ASSIGN: state.error = matchTypes(SUB_ASSIGN_COMP, state.exp->left->exp_type, state.exp->right->exp_type); break;
                    }
                    state.exp->exp_type = state.exp->left->exp_type;
                    break;
                }
                case LOG_OR: case LOG_AND: case BIT_OR: case BIT_XOR: case BIT_AND:{
                    switch(root.exp->node_type){
                        case LOG_OR:
                            state.error = matchTypes(LOG_OR_COMP, state.exp->left->exp_type, state.exp->right->exp_type);
                            break;
                        case LOG_AND:
                            state.error = matchTypes(LOG_AND_COMP, state.exp->left->exp_type, state.exp->right->exp_type);
                            break;
                        case BIT_OR:
                            state.error = matchTypes(BIT_OR_COMP, state.exp->left->exp_type, state.exp->right->exp_type);
                            break;
                        case BIT_XOR:
                            state.error = matchTypes(BIT_XOR_COMP, state.exp->left->exp_type, state.exp->right->exp_type);
                            break;
                        case BIT_AND:
                            state.error = matchTypes(BIT_AND_COMP, state.exp->left->exp_type, state.exp->right->exp_type);
                            break;
                    }
                    state.exp->exp_type.type = TIPOS_INT;
                    state.exp->exp_type.pointers = 0;
                    state.exp->exp_type.constant = true;
                    break;
                }
                case EQUALS: case NOT_EQUALS: case LESS: case LEQ: case GEQ: case GREAT:{
                    switch(root.exp->node_type){
                        case EQUALS:
                            state.error = matchTypes(EQUAL_COMP, state.exp->left->exp_type, state.exp->right->exp_type);
                            break;
                        case NOT_EQUALS:
                            state.error = matchTypes(DIFF_COMP, state.exp->left->exp_type, state.exp->right->exp_type);
                            break;
                        case LESS:
                            state.error = matchTypes(LESS_COMP, state.exp->left->exp_type, state.exp->right->exp_type);
                            break;
                        case LEQ:
                            state.error = matchTypes(LEQ_COMP, state.exp->left->exp_type, state.exp->right->exp_type);
                            break;
                        case GEQ:
                            state.error = matchTypes(GEQ_COMP, state.exp->left->exp_type, state.exp->right->exp_type);
                            break;
                        case GREAT:
                            state.error = matchTypes(GREAT_COMP, state.exp->left->exp_type, state.exp->right->exp_type);
                            break;
                    }
                    state.exp->exp_type.type = TIPOS_INT;
                    state.exp->exp_type.pointers = 0;
                    state.exp->exp_type.constant = true;
                    break;
                }
                case ADD: case SUB: case MUL: case DIV: case MOD:{
                    switch(root.exp->node_type){
                        case ADD: state.error = matchTypes(PLUS_COMP,      state.exp->left->exp_type, state.exp->right->exp_type); break;
                        case SUB: state.error = matchTypes(MINUS_COMP,     state.exp->left->exp_type, state.exp->right->exp_type); break;
                        case MUL: state.error = matchTypes(MUL_COMP,       state.exp->left->exp_type, state.exp->right->exp_type); break;
                        case DIV: state.error = matchTypes(DIV_COMP,       state.exp->left->exp_type, state.exp->right->exp_type);
                            Const_expr_state div_result = evaluateConstExpr(state.exp->right);
                            if(div_result.error ==  NO_ERROR && div_result.value == 0){
                                state.error = DIVISION_BY_ZERO;
                                break;
                            }
                            break;
                        case MOD: state.error = matchTypes(REMAINDER_COMP, state.exp->left->exp_type, state.exp->right->exp_type); break;
                    }
                    if(verifyTypes(state.exp->left->exp_type, state.exp->right->exp_type) == MATCH){
                        if(state.exp->left->exp_type.type == TIPOS_CHAR){
                            state.exp->exp_type.type = TIPOS_CHAR;
                        }
                    }else{
                        state.exp->exp_type.type = TIPOS_INT;
                    }
                    state.exp->exp_type.pointers = state.exp->left->exp_type.pointers;
                    state.exp->exp_type.constant = true;
                    break;
                }
                case ADDRESS:{
                    if(no_l.exp->exp_type.constant){
                        state.error = RVALUE_UNARY_OPERAND;
                        break;
                    }
                    state.exp->exp_type.type = state.exp->left->exp_type.type;
                    state.exp->exp_type.pointers = state.exp->left->exp_type.pointers + 1;
                    state.exp->exp_type.constant = true;
                    state.error = matchTypes(UN_ADDRESS_COMP, state.exp->left->exp_type, state.exp->exp_type);
                    break;
                }
                case UNR_PLUS: case UNR_MINUS:{
                    switch(root.exp->node_type){
                        case UNR_PLUS:  state.error = matchTypes(UN_PLUS_COMP,  state.exp->left->exp_type, state.exp->exp_type); break;
                        case UNR_MINUS: state.error = matchTypes(UN_MINUS_COMP, state.exp->left->exp_type, state.exp->exp_type); break;
                    }
                    state.exp->exp_type = state.exp->left->exp_type;
                    state.exp->exp_type.constant = true;
                    break;
                }
                case BIT_NOT: case LOG_NOT:{
                    switch(root.exp->node_type){
                        case BIT_NOT: state.error = matchTypes(UN_BIT_NOT_COMP, state.exp->left->exp_type, state.exp->exp_type); break;
                        case LOG_NOT: state.error = matchTypes(UN_LOG_NOT_COMP, state.exp->left->exp_type, state.exp->exp_type); break;
                    }
                    state.exp->exp_type.constant = true;
                    state.exp->exp_type.pointers = 0;
                    state.exp->exp_type.type     = TIPOS_INT;
                    state.error = matchTypes(UN_BIT_NOT_COMP, state.exp->left->exp_type, state.exp->exp_type);
                    break;
                }
                case INC: case DEC:{
                    int error;
                    switch(root.exp->node_type){
                        case INC:
                            matchTypes(UN_INC_COMP, state.exp->left->exp_type, state.exp->exp_type);
                            error = RVALUE_INC_OPERAND;
                            break;
                        case DEC:
                            matchTypes(UN_DEC_COMP, state.exp->left->exp_type, state.exp->exp_type);
                            error = RVALUE_DEC_OPERAND;
                            break;
                    }

                    if(state.exp->left->exp_type.constant){
                        state.error = error;
                        break;
                    }else{
                        state.exp->exp_type = state.exp->left->exp_type;
                        state.exp->exp_type.constant = true;
                    }
                    break;
                }
            }
            
            if(state.error != NO_ERROR && state.error < WARNINGS_START){
                break;
            }else if(state.error > WARNINGS_START){
                state.warnings_list = warningInsert(state.warnings_list, state.error, state.exp);
            }
            break;
        }

        case CONDITIONAL_EXP:{
            state.exp->exp_type = no_r.exp->exp_type;
            break;
        }
        case CONDITIONAL_EXP_THENELSE:{
            bool exp_is_void = isVoid(no_l.exp->exp_type);
            exp_is_void     |= isVoid(no_r.exp->exp_type);
            if(exp_is_void){
                state.error = VOID_NOT_IGNORED;
                break;
            }

            int matching = verifyTypes(state.exp->left->exp_type, state.exp->right->exp_type);
            if(matching != MATCH){
                switch(matching){
                    case PTR_MISSMATCH: case PTR_AND_NON_PTR:
                        state.exp->exp_type =
                            (state.exp->left->exp_type.pointers > state.exp->right->exp_type.pointers) ? state.exp->left->exp_type : state.exp->right->exp_type;
                        break;
                    case BASE_PTR_MISSMATCH: case TYPE_MISSMATCH:
                        state.exp->exp_type =
                            (state.exp->left->exp_type.type < state.exp->right->exp_type.type) ? state.exp->left->exp_type : state.exp->right->exp_type;
                        break;
                }
                state.warnings_list = warningInsert(state.warnings_list, CONDITIONAL_TYPE_MISSMATCH_W, state.exp);
            }else{
                state.exp->exp_type = state.exp->left->exp_type;
            }
            state.exp->exp_type.constant = true;
            break;
        }

        case RSHIFT: case LSHIFT:{
            int negative_shift_error, exceeds_size_warning;
            switch(root.exp->node_type){
                case RSHIFT:
                    state.error = matchTypes(RSHIFT_COMP, state.exp->left->exp_type, state.exp->right->exp_type);
                    negative_shift_error = RSHIFT_NEGATIVE;
                    exceeds_size_warning = RSHIFT_EXCEEDS_SIZE_W;
                    break;
                case LSHIFT:
                    state.error = matchTypes(LSHIFT_COMP, state.exp->left->exp_type, state.exp->right->exp_type);
                    negative_shift_error = LSHIFT_NEGATIVE;
                    exceeds_size_warning = LSHIFT_EXCEEDS_SIZE_W;
                    break;
            }

            if(state.error != NO_ERROR && state.error < WARNINGS_START){
                if(no_r.exp->exp_type.pointers > 0){
                    state.error = IMPOSSIBLE_INT_CONVERSION;
                    state.exp->exp_type = no_r.exp->exp_type;
                }
                break;
            }else if(state.error > WARNINGS_START){
                state.warnings_list = warningInsert(state.warnings_list, state.error, state.exp);
            }
            //verifica o valor da expressão direita
            Const_expr_state right_value = evaluateConstExpr(state.exp->right);
            if(right_value.error == NO_ERROR){
                if(state.exp->left->exp_type.pointers > 0){
                    if(right_value.value >= TIPOS_POINTER_SIZE){
                        state.warnings_list = warningInsert(state.warnings_list, exceeds_size_warning, state.exp);
                    }
                }else if(state.exp->left->exp_type.type == TIPOS_INT){
                    if(right_value.value >= TIPOS_INT_SIZE){
                        state.warnings_list = warningInsert(state.warnings_list, exceeds_size_warning, state.exp);
                    }
                }else if(state.exp->left->exp_type.type == TIPOS_CHAR){
                    if(right_value.value >= TIPOS_CHAR_SIZE){
                        state.warnings_list = warningInsert(state.warnings_list, exceeds_size_warning, state.exp);
                    }
                } 
            }
            if(right_value.value < 0){
                state.error = negative_shift_error;
                break;
            }
            state.exp->exp_type = state.exp->left->exp_type;
            state.exp->exp_type.constant = true;
            break;
        }

        case CAST:{
            bool left_is_void = isVoid(no_l.exp->exp_type);
            bool exp_is_void  = isVoid(state.exp->exp_type);
            if(left_is_void && !exp_is_void){
                state.error = VOID_NOT_IGNORED;
                break;
            }

            if(compareTypesSize(state.exp->exp_type, state.exp->left->exp_type) == RIGHT_BIGGER){
                state.warnings_list = warningInsert(state.warnings_list, DIFFERENT_CAST_SIZE_W, state.exp);
            }
            break;
        }

        case POINTER_DEFERENCE:{
            state.error = matchTypes(UN_DEFERENCE_COMP, state.exp->left->exp_type, state.exp->exp_type);
            if(state.error != NO_ERROR && state.error < WARNINGS_START)
                { break; }
            if(state.exp->left->exp_type.pointers == 0){
                state.error = INVALID_UNR_OPERAND;
                break;
            }else{
                state.exp->exp_type = state.exp->left->exp_type;
                state.exp->exp_type.pointers = state.exp->left->exp_type.pointers - 1;
                state.exp->exp_type.constant = false;
            }
            break;
        }

        case SUBSCRIPT:{
            if(no_l.exp->node_type == IDENTIFIER && no_l.exp->node_value.sym->symbol_type == DECLARACAO_VARIAVEL){
                state.exp->exp_type = no_l.exp->exp_type;
                // if(no_l.exp->node_value.sym->var.v.array){
                //     state.exp->exp_type.pointers += no_l.exp->node_value.sym->var.v.array->dimension;
                // }
            }else if(no_l.exp->node_type == SUBSCRIPT){
                state.exp->exp_type = no_l.exp->exp_type;
            }else{
                state.error = INVALID_SUBSCRIPTOR;
                break;
            }
            if(no_r.exp->exp_type.pointers > 0){
                state.error = NOT_INT_SUBSCRIPTOR;
                state.exp->exp_type = no_r.exp->exp_type;
                break;
            }

            if(state.exp->exp_type.pointers == 0){
                state.error = INVALID_SUBSCRIPTOR;
                break;
            }
            state.exp->exp_type.pointers--;

            Const_expr_state index = evaluateConstExpr(no_r.exp);
            if(index.error == NO_ERROR){
                if(index.value < 0){
                    state.warnings_list = warningInsert(state.warnings_list, INDEX_OUT_OF_BOUNDS, state.exp);
                }
            }
            break;
        }
        case FUNCTION_CALL:{
            // printf("%d, %d\n\n", state.exp->line, state.exp->column);
            break;
        }

        case NUM_INT:{
            state.exp->exp_type.type     = TIPOS_INT;
            state.exp->exp_type.pointers = 0;
            state.exp->exp_type.constant = true;
            break;
        }
        case STRING:{
            state.exp->exp_type.type     = TIPOS_CHAR;
            state.exp->exp_type.pointers = 1;
            state.exp->exp_type.constant = true;
            break;
        }
        case CHARACTER:{
            state.exp->exp_type.type     = TIPOS_CHAR;
            state.exp->exp_type.pointers = 0;
            state.exp->exp_type.constant = true;
            break;
        }
        case IDENTIFIER:{
            state.exp->exp_type = state.exp->node_value.sym->type;
            if(state.exp->node_value.sym->symbol_type == DECLARACAO_FUNCAO){
                state.exp->exp_type = state.exp->node_value.sym->type;
                state.exp->exp_type.constant = true;
            }else if(state.exp->node_value.sym->var.v.constant){
                state.exp->exp_type.constant = true;
            }else{
                state.exp->exp_type.constant = false;
                if(state.exp->node_value.sym->var.v.array){
                    state.exp->exp_type.pointers += state.exp->node_value.sym->var.v.array->dimension;
                }
            }
            break;
        }
    }

    state.warnings_list = mergeWarningsLists(state.warnings_list, no_r.warnings_list);
    state.warnings_list = mergeWarningsLists(no_l.warnings_list, state.warnings_list);

    return state;
}

Func_type_state matchFunctionCall(Expression *func, Expression *call, FILE* read_warning_line){
    struct parameters *param = func->node_value.sym->var.f.parameters;
    Exp_type_state c_state;
    Func_type_state f_state = { NO_ERROR, func, func->node_value.sym->id };
    f_state.func_name = func->node_value.sym->id;

    for(int i=1;param && call;i++, param=param->next, call=call->right){
        if(call->node_type == COMMA_SEPARATOR){
            c_state = evalExpTypeAndHandleWarnings(call->left, read_warning_line);
        }else{
            c_state = evalExpTypeAndHandleWarnings(call, read_warning_line);
        }

        if(c_state.error != NO_ERROR && c_state.error < WARNINGS_START){
            f_state.error = c_state.error;
            f_state.func  = c_state.exp;
            return f_state;
        }

        if(isVoid(call->exp_type)){
            f_state.error = VOID_NOT_IGNORED;
            f_state.func = call;
            return f_state;
        }
        if(verifyTypes(param->symbol->type, c_state.exp->exp_type) != MATCH){
            f_state.error = INCOMPATIBLE_ARGUMENT_TYPE;
            f_state.expected_type = param->symbol->type;
            f_state.received_type = c_state.exp->exp_type;
            f_state.wrong_arg = i;
            f_state.func = func;
            return f_state;
        }
    }

    if(param){
        f_state.error = TOO_FEW_ARGUMENTS;
        return f_state;
    }else if(call){
        f_state.error = TOO_MANY_ARGUMENTS;
        return f_state;
    }

    return f_state;
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

        case IDENTIFIER: return "ID";
        case NUM_INT:    return "NUMBER";
        default: return "OPERATOR NOT FOUND";
    }
}
char* getType(Var_type type){
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

int compareTypesSize(Var_type v1, Var_type v2){
    int size_l, size_r;
    if(!v1.pointers != !v2.pointers){
        if(v1.pointers > 0){
            size_l = TIPOS_POINTER_SIZE;
        }else{
            size_r = TIPOS_POINTER_SIZE;
        }
    }else if(v1.type != v2.type && v1.pointers == 0){
        // if(v1.type == TIPOS_INT){
        //     return LEFT_BIGGER;
        // }else{
        //     return RIGHT_BIGGER;
        // }
        switch(v1.type){
            case TIPOS_INT: size_l = TIPOS_INT_SIZE;  break;
            default:        size_l = TIPOS_CHAR_SIZE; break;
        }
        switch(v2.type){
            case TIPOS_INT: size_r = TIPOS_INT_SIZE;  break;
            default:        size_r = TIPOS_CHAR_SIZE; break;
        }
    }else{
        size_l = size_r = TIPOS_POINTER_SIZE;
    }

    if(size_l == size_r){
        return SAME_SIZE;
    }else if(size_l > size_r){
        return LEFT_BIGGER;
    }else{
        return RIGHT_BIGGER;
    }
}
