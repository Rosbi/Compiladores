#ifndef ABSTRACT_SYNTAX_TREE_H
#define ABSTRACT_SYNTAX_TREE_H

typedef void* TreeNode;

TreeNode nodeNew(int node_t, float node_v, TreeNode left, TreeNode right);

TreeNode nodeGetLeft(TreeNode);
TreeNode nodeGetRight(TreeNode);
float nodeGetValue(TreeNode);

void RpnWalk(TreeNode);
float solveForX(TreeNode, float x, int *error);

void deleteTree(TreeNode);

#endif