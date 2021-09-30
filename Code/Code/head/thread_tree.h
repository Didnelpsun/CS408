#include "head.h"

// �������������
typedef struct ThreadBinaryTreeNode {
    // ����
    element_type data;
    // ���Һ��ӽ��
    ThreadBinaryTreeNode *left_child, *right_child;
    // ��������ָ��
    int left_tag, right_tag;
} ThreadBinaryTreeNode, *ThreadBinaryTree;

// �������������
bool InOrderThreadBinaryTree(ThreadBinaryTree &tree, ThreadBinaryTree &pre) {
    if (tree != nullptr) {
        // �ݹ�������������
        InOrderThreadBinaryTree(tree->left_child, pre);
        // ������Ϊ�գ�����ǰ������
        if (tree->left_child == nullptr) {
            // ��������ָ��ǰ��
            tree->left_child = pre;
            tree->left_tag = 1;
        }
        // ����ǰ����Ϊ����ǰ����������Ϊ��
        if (pre != nullptr && pre->right_child == nullptr) {
            // ��ǰ���ĺ������ָ��ǰ���
            pre->right_child = tree;
            pre->right_tag = 1;
        }
        // ����ǰ�����Ϊǰ�����
        pre = tree;
        // �ݹ�������������
        InOrderThreadBinaryTree(tree->right_child, pre);
    }
    return true;
}

// ������������������
bool CreateInOrderThreadBinaryTree(ThreadBinaryTree tree) {
    ThreadBinaryTreeNode *pre = nullptr;
    if (tree != nullptr) {
        // ������������
        InOrderThreadBinaryTree(tree, pre);
        // ������������һ�����
        pre->right_child = nullptr;
        pre->right_tag = 1;
    }
    return true;
}

// ���������������������е�һ�����
ThreadBinaryTreeNode *FirstInOrderBinaryTreeNode(ThreadBinaryTreeNode *node) {
    // �������ӽ��
    while (node->left_tag == 0) {
        // �����µĽ�㣬��һ����Ҷ�ӽ��
        node = node->left_child;
    }
    return node;
}

// ���������������������к��
ThreadBinaryTreeNode *NextInOrderBinaryTreeNode(ThreadBinaryTreeNode *node){
    // ������Һ��ӽ�㣬���ҵ�����������������
    if(node->right_tag==0){
        return FirstInOrderBinaryTreeNode(node->right_child);
    }
    else
        // ���к��������ֱ�ӷ�������
        return node->right_child;
}

// �����������������
bool InOrderThreadBinaryTree(ThreadBinaryTree *tree,bool( *function)(ThreadBinaryTreeNode)){
    for(ThreadBinaryTreeNode *node= FirstInOrderBinaryTreeNode(*tree);node != nullptr;node= NextInOrderBinaryTreeNode(node)){
        if(!function(*node))
            return false;
    }
    return true;
}

// �������������
bool PreOrderThreadBinaryTree(ThreadBinaryTree &tree, ThreadBinaryTree &pre) {
    if (tree != nullptr) {
        // ������Ϊ�գ�����ǰ������
        if (tree->left_child == nullptr) {
            // ��������ָ��ǰ��
            tree->left_child = pre;
            tree->left_tag = 1;
        }
        // ����ǰ����Ϊ����ǰ����������Ϊ��
        if (pre != nullptr && pre->right_child == nullptr) {
            // ��ǰ���ĺ������ָ��ǰ���
            pre->right_child = tree;
            pre->right_tag = 1;
        }
        // ����ǰ�����Ϊǰ�����
        pre = tree;
        // ��Ҫ�ж��Ƿ�������
        if(tree->left_tag==0){
            // �ݹ�������������
            InOrderThreadBinaryTree(tree->left_child, pre);
        }
        // �ݹ�������������
        InOrderThreadBinaryTree(tree->right_child, pre);
    }
    return true;
}

// ������������������
bool CreatePreOrderThreadBinaryTree(ThreadBinaryTree tree) {
    ThreadBinaryTreeNode *pre = nullptr;
    if (tree != nullptr) {
        // ������������
        PreOrderThreadBinaryTree(tree, pre);
        // ������������һ�����
        pre->right_child = nullptr;
        pre->right_tag = 1;
    }
    return true;
}

// �������������
bool PostOrderThreadBinaryTree(ThreadBinaryTree &tree, ThreadBinaryTree &pre) {
    if (tree != nullptr) {
        // �ݹ�������������
        InOrderThreadBinaryTree(tree->left_child, pre);
        // �ݹ�������������
        InOrderThreadBinaryTree(tree->right_child, pre);
        // ������Ϊ�գ�����ǰ������
        if (tree->left_child == nullptr) {
            // ��������ָ��ǰ��
            tree->left_child = pre;
            tree->left_tag = 1;
        }
        // ����ǰ����Ϊ����ǰ����������Ϊ��
        if (pre != nullptr && pre->right_child == nullptr) {
            // ��ǰ���ĺ������ָ��ǰ���
            pre->right_child = tree;
            pre->right_tag = 1;
        }
        // ����ǰ�����Ϊǰ�����
        pre = tree;
    }
    return true;
}

// ������������������
bool CreatePostOrderThreadBinaryTree(ThreadBinaryTree tree) {
    ThreadBinaryTreeNode *pre = nullptr;
    if (tree != nullptr) {
        // ������������
        PreOrderThreadBinaryTree(tree, pre);
        // ������������һ�����
        pre->right_child = nullptr;
        pre->right_tag = 1;
    }
    return true;
}