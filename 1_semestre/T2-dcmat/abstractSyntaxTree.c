#include<stdlib.h>
#include<stdio.h>
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
            printf("%d ", (int)node->node_value);
            break;
        case REAL: 
            printf("%f ", node->node_value);
            break;
        case VAR:  
            printf("x ");
            break;
    }
}

void deleteTree(TreeNode n){
    struct ast *node = n;
    if(!node)
        { return; }
    
    deleteTree(node->left);
    deleteTree(node->right);
    free(node);
}
