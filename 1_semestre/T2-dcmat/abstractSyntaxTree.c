#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include"abstractSyntaxTree.h"
#include"sintatico.tab.h"

struct ast{
    struct ast *left;
    struct ast *right;
    int node_type;
    float node_value;
};

TreeNode nodeNew(int node_t, float node_v, TreeNode left, TreeNode right){
    struct ast *aux = malloc(sizeof(struct ast));
    struct ast *l = left;
    struct ast *r = right;
    aux->left = l;
    aux->right = r;
    aux->node_type = node_t;
    aux->node_value = node_v;
    return aux;
}

TreeNode nodeGetLeft(TreeNode node){
    struct ast *aux = node;
    return aux->left;
}
TreeNode nodeGetRight(TreeNode node){
    struct ast *aux = node;
    return aux->right;
}
float nodeGetValue(TreeNode node){
    struct ast *aux = node;
    return aux->node_value;
}

void RpnWalk(TreeNode n){
    struct ast *node = n;
    if(!node)
        { return; }

    RpnWalk(node->left);
    RpnWalk(node->right);
    switch(node->node_type){
        case ADD:  
            printf("+ ");
            break;
        case SUB:  
            printf("- ");
            break;
        case MUL:  
            printf("* ");
            break;
        case DIV:  
            printf("/ ");
            break;
        case POW:  
            printf("^ ");
            break;
        case MOD:  
            printf("%c ", '%');
            break;
        case SEN:  
            printf("SEN ");
            break;
        case COS:  
            printf("COS ");
            break;
        case TAN:  
            printf("TAN ");
            break;
        case ABS:  
            printf("ABS ");
            break;
        case NUM:
        case REAL: 
            printf("%f ", node->node_value);
            break;
        case VAR:  
            printf("x ");
            break;
    }
}

float RpnSolve(struct ast *node, float x){
    if(!node)
        { return 0.0; }

    float no_l, no_r;
    float result = 0.0;
    no_l = RpnSolve(node->left, x);
    no_r = RpnSolve(node->right, x);
    switch(node->node_type){
        case ADD:  
            result = no_l + no_r;
            break;
        case SUB:  
            result = no_l - no_r;
            break;
        case MUL:  
            result = no_l * no_r;
            break;
        case DIV:  
            result = no_l / no_r;
            break;
        case POW:  
            result = powf(no_l, no_r);
            break;
        case MOD:  
            result = (int)no_l % (int)no_r;
            break;
        case SEN:  
            result = sinf(no_l);
            break;
        case COS:  
            result = cosf(no_l);
            break;
        case TAN:  
            result = tanf(no_l);
            break;
        case ABS:  
            result = fabsf(no_l);
            break;
        case NUM:  
            result = node->node_value;
            break;
        case REAL: 
            result = node->node_value;
            break;
        case VAR:  
            result = x;
            break;
    }
    return result;
}
float solveForX(TreeNode n, float x, int *error){
    struct ast *node = n;
    *error = 0;
    if(!node){ 
        *error = -1;
        return 0.0; 
    }
    
    return RpnSolve(node, x);
}

void deleteTree(TreeNode n){
    struct ast *node = n;
    if(!node)
        { return; }
    
    deleteTree(node->left);
    deleteTree(node->right);
    free(node);
}
