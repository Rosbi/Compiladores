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
        case ADD:  
            printf("+ ");
            break;
        case SUB:  
            printf("- ");
            break;
        // case MUL:  
        //     printf("* ");
        //     break;
        // case DIV:  
        //     printf("/ ");
        //     break;
        // case POW:  
        //     printf("^ ");
        //     break;
        // case MOD:  
        //     printf("%c ", '%');
        //     break;
        // case SEN:  
        //     printf("SEN ");
        //     break;
        // case COS:  
        //     printf("COS ");
        //     break;
        // case TAN:  
        //     printf("TAN ");
        //     break;
        // case ABS:  
        //     printf("ABS ");
        //     break;
        // case NUM:
        // case REAL: 
        //     printf("%f ", node->node_value);
        //     break;
        // case VAR:  
        //     printf("x ");
        //     break;
    }
}

int constExprSolve(Expression *root){
    int no_l, no_r;
    int result = 0.0;
    no_l = constExprSolve(root->left);
    no_r = constExprSolve(root->right);
    switch(root->node_type){
        case ADD:  
            result = no_l + no_r;
            break;
        case SUB:  
            result = no_l - no_r;
            break;
        // case MUL:  
        //     result = no_l * no_r;
        //     break;
        // case DIV:  
        //     result = no_l / no_r;
        //     break;
        // case POW:  
        //     result = powf(no_l, no_r);
        //     break;
        // case MOD:  
        //     result = (int)no_l % (int)no_r;
        //     break;
        // case SEN:  
        //     result = sinf(no_l);
        //     break;
        // case COS:  
        //     result = cosf(no_l);
        //     break;
        // case TAN:  
        //     result = tanf(no_l);
        //     break;
        // case ABS:  
        //     result = fabsf(no_l);
        //     break;
        // case NUM:  
        //     result = node->node_value;
        //     break;
        // case REAL: 
        //     result = node->node_value;
        //     break;
        // case VAR:  
        //     result = x;
        //     break;
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
