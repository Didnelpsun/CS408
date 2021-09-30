#include "head.h"

// 线索二叉树结点
typedef struct ThreadBinaryTreeNode {
    // 数据
    element_type data;
    // 左右孩子结点
    ThreadBinaryTreeNode *left_child, *right_child;
    // 左右线索指针
    int left_tag, right_tag;
} ThreadBinaryTreeNode, *ThreadBinaryTree;

// 中序遍历线索化
bool InOrderThreadBinaryTree(ThreadBinaryTree &tree, ThreadBinaryTree &pre) {
    if (tree != nullptr) {
        // 递归线索化左子树
        InOrderThreadBinaryTree(tree->left_child, pre);
        // 左子树为空，建立前驱线索
        if (tree->left_child == nullptr) {
            // 将左子树指向前驱
            tree->left_child = pre;
            tree->left_tag = 1;
        }
        // 当其前驱不为空且前驱的右子树为空
        if (pre != nullptr && pre->right_child == nullptr) {
            // 将前驱的后继线索指向当前结点
            pre->right_child = tree;
            pre->right_tag = 1;
        }
        // 将当前结点设为前驱结点
        pre = tree;
        // 递归线索化右子树
        InOrderThreadBinaryTree(tree->right_child, pre);
    }
    return true;
}

// 建立中序线索二叉树
bool CreateInOrderThreadBinaryTree(ThreadBinaryTree tree) {
    ThreadBinaryTreeNode *pre = nullptr;
    if (tree != nullptr) {
        // 线索化二叉树
        InOrderThreadBinaryTree(tree, pre);
        // 处理遍历的最后一个结点
        pre->right_child = nullptr;
        pre->right_tag = 1;
    }
    return true;
}

// 中序线索二叉树中序序列第一个结点
ThreadBinaryTreeNode *FirstInOrderBinaryTreeNode(ThreadBinaryTreeNode *node) {
    // 当有左孩子结点
    while (node->left_tag == 0) {
        // 最左下的结点，不一定是叶子结点
        node = node->left_child;
    }
    return node;
}

// 中序线索二叉树中序序列后继
ThreadBinaryTreeNode *NextInOrderBinaryTreeNode(ThreadBinaryTreeNode *node){
    // 如果有右孩子结点，则找到其右子树的最左结点
    if(node->right_tag==0){
        return FirstInOrderBinaryTreeNode(node->right_child);
    }
    else
        // 若有后继线索则直接返回线索
        return node->right_child;
}

// 中序遍历线索二叉树
bool InOrderThreadBinaryTree(ThreadBinaryTree *tree,bool( *function)(ThreadBinaryTreeNode)){
    for(ThreadBinaryTreeNode *node= FirstInOrderBinaryTreeNode(*tree);node != nullptr;node= NextInOrderBinaryTreeNode(node)){
        if(!function(*node))
            return false;
    }
    return true;
}

// 先序遍历线索化
bool PreOrderThreadBinaryTree(ThreadBinaryTree &tree, ThreadBinaryTree &pre) {
    if (tree != nullptr) {
        // 左子树为空，建立前驱线索
        if (tree->left_child == nullptr) {
            // 将左子树指向前驱
            tree->left_child = pre;
            tree->left_tag = 1;
        }
        // 当其前驱不为空且前驱的右子树为空
        if (pre != nullptr && pre->right_child == nullptr) {
            // 将前驱的后继线索指向当前结点
            pre->right_child = tree;
            pre->right_tag = 1;
        }
        // 将当前结点设为前驱结点
        pre = tree;
        // 需要判断是否有左孩子
        if(tree->left_tag==0){
            // 递归线索化左子树
            InOrderThreadBinaryTree(tree->left_child, pre);
        }
        // 递归线索化右子树
        InOrderThreadBinaryTree(tree->right_child, pre);
    }
    return true;
}

// 建立先序线索二叉树
bool CreatePreOrderThreadBinaryTree(ThreadBinaryTree tree) {
    ThreadBinaryTreeNode *pre = nullptr;
    if (tree != nullptr) {
        // 线索化二叉树
        PreOrderThreadBinaryTree(tree, pre);
        // 处理遍历的最后一个结点
        pre->right_child = nullptr;
        pre->right_tag = 1;
    }
    return true;
}

// 后序遍历线索化
bool PostOrderThreadBinaryTree(ThreadBinaryTree &tree, ThreadBinaryTree &pre) {
    if (tree != nullptr) {
        // 递归线索化左子树
        InOrderThreadBinaryTree(tree->left_child, pre);
        // 递归线索化右子树
        InOrderThreadBinaryTree(tree->right_child, pre);
        // 左子树为空，建立前驱线索
        if (tree->left_child == nullptr) {
            // 将左子树指向前驱
            tree->left_child = pre;
            tree->left_tag = 1;
        }
        // 当其前驱不为空且前驱的右子树为空
        if (pre != nullptr && pre->right_child == nullptr) {
            // 将前驱的后继线索指向当前结点
            pre->right_child = tree;
            pre->right_tag = 1;
        }
        // 将当前结点设为前驱结点
        pre = tree;
    }
    return true;
}

// 建立后序线索二叉树
bool CreatePostOrderThreadBinaryTree(ThreadBinaryTree tree) {
    ThreadBinaryTreeNode *pre = nullptr;
    if (tree != nullptr) {
        // 线索化二叉树
        PreOrderThreadBinaryTree(tree, pre);
        // 处理遍历的最后一个结点
        pre->right_child = nullptr;
        pre->right_tag = 1;
    }
    return true;
}