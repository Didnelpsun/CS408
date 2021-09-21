#include "head.h"

// 二叉树结点
typedef struct BinaryTreeNode {
    element_type data;
    BinaryTreeNode *left_child, *right_child;
} BinaryTreeNode, *BinaryTree;