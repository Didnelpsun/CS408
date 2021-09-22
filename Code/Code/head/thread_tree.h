#include "head.h"

// 线索二叉树结点
typedef struct ThreadTreeNode{
    // 数据
    element_type data;
    // 左右孩子结点
    ThreadTreeNode *left_child, *right_child;
    // 左右线索指针
    int left_tag, right_tag;
} ThreadTreeNode, *ThreadTree;
