#ifndef ABSTRACT_SYNTAX_TREE_H
#define ABSTRACT_SYNTAX_TREE_H

typedef void* TreeNode;

TreeNode nodeNew(int node_t, float node_v, TreeNode left, TreeNode right);
void RpnWalk(TreeNode);
void deleteTree(TreeNode);

#endif