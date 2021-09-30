#include "head.h"
#include <stack>
#include <queue>

// �Ƚ�Ԫ�ط���
int CompareElem(element_type elem1, element_type elem2){
    return 0;
}

// ���������
typedef struct BinaryTreeNode {
    element_type data;
    BinaryTreeNode *left_child, *right_child;
} BinaryTreeNode, *BinaryTree;

// ǰ�����
bool PreOrderBinaryTree(BinaryTree &tree, bool( *function)(BinaryTree &)) {
    if (tree != nullptr) {
        if (!function(tree))
            return false;
        PreOrderBinaryTree(tree->left_child, function);
        PreOrderBinaryTree(tree->right_child, function);
    }
    return true;
}

// �������
bool InOrderBinaryTree(BinaryTree &tree, bool(*function)(BinaryTree &)) {
    if (tree != nullptr) {
        PreOrderBinaryTree(tree->left_child, function);
        if (!function(tree))
            return false;
        PreOrderBinaryTree(tree->right_child, function);
    }
    return true;
}

// �������
bool PostOrderBinaryTree(BinaryTree &tree, bool(*function)(BinaryTree &)) {
    if (tree != nullptr) {
        PreOrderBinaryTree(tree->left_child, function);
        PreOrderBinaryTree(tree->right_child, function);
        if (!function(tree))
            return false;
    }
    return true;
}

// �ǵݹ��������
bool PreOrderNonRecursiveBinaryTree(BinaryTree &tree, bool(*function)(BinaryTree &)) {
    // ��ʼ��ջ��ջԪ��Ϊtreeָ��
    std::stack<BinaryTree> stack;
    // ��ֵһ������
    BinaryTree new_tree = tree;
    // ���ջ���ջ�new_tree����ʱѭ��
    while (new_tree || !stack.empty()) {
        // һֱ����
        if (new_tree) {
            // ���ʵ�ǰ���
            if (!function(new_tree)) {
                printf("PreOrderNonRecursive:���ʽ��ʧ�ܣ�");
                return false;
            }
            // ��ǰ�����ջ
            stack.push(new_tree);
            // ���Ӳ�����һֱ����
            new_tree = new_tree->left_child;
        }
            // ��ջ����ת��������
        else {
            // ����ջ����Ԫ�أ�����ɾ����Ԫ��
            new_tree = stack.top();
            // ɾ��ջ��Ԫ�ص���������ֵ
            stack.pop();
            // ����
            new_tree = new_tree->right_child;
            // ����while
        }
    }
    return true;
}

// �ǵݹ��������
bool InOrderNonRecursiveBinaryTree(BinaryTree &tree, bool(*function)(BinaryTree &)) {
    // ��ʼ��ջ��ջԪ��Ϊtreeָ��
    std::stack<BinaryTree> stack;
    // ��ֵһ������
    BinaryTree new_tree = tree;
    // ���ջ���ջ�new_tree����ʱѭ��
    while (new_tree || !stack.empty()) {
        // һֱ����
        if (new_tree) {
            // ��ǰ�����ջ
            stack.push(new_tree);
            // ���Ӳ�����һֱ����
            new_tree = new_tree->left_child;
        }
            // ��ջ����ת��������
        else {
            // ����ջ����Ԫ�أ�����ɾ����Ԫ��
            new_tree = stack.top();
            // ɾ��ջ��Ԫ�ص���������ֵ
            stack.pop();
            // ���ʳ�ջ���
            if (!function(new_tree)) {
                printf("InOrderNonRecursive:���ʽ��ʧ�ܣ�");
                return false;
            }
            // ����
            new_tree = new_tree->right_child;
            // ����while
        }
    }
    return true;
}

// �������
bool LevelOrderBinaryTree(BinaryTree &tree, bool(*function)(BinaryTree &)) {
    // ��ʼ����������
    std::queue<BinaryTree> queue;
    // ��ʼ�������
    BinaryTree new_tree = tree;
    // ��������
    queue.push(new_tree);
    // �����зǿ���ѭ��
    while (!queue.empty()) {
        // ��ͷ������
        new_tree = queue.front();
        queue.pop();
        // ���ʳ��ӽ��
        if (!function(new_tree)) {
            printf("LevelOrder:���ʽ��ʧ�ܣ�");
            return false;
        }
        // ������������������������
        if (new_tree->left_child != nullptr) {
            queue.push(new_tree);
        }
        if (new_tree->right_child != nullptr) {
            queue.push(new_tree);
        }
    }
    return true;
}

// ��������������
BinaryTreeNode *SearchBinarySortTree(BinaryTree tree, element_type elem) {
    BinaryTree node = tree;
    // �����ջ���ڸ����ֵ�ͽ���ѭ��
    while (node != nullptr && elem != node->data) {
        // ��С��������������
        if (CompareElem(elem, node->data) < 0)
            node = node->left_child;
        else
            node = node->right_child;
    }
    return node;
}

// ��������������
bool InsertBinarySortTree(BinaryTree &tree, element_type elem) {
    if (elem == NULL){
        printf("InsertBinarySortTree:�������ݲ�ӦΪ�գ�\n");
        return false;
    }
    // ��ԭ��Ϊ�գ����²���ļ�¼��Ϊ�����
    if (tree == nullptr) {
        tree = (BinaryTree) malloc(sizeof(BinaryTreeNode));
        tree->data = elem;
        tree->left_child = tree->right_child = nullptr;
        return true;
    }
        // ��������ͬ�ؼ��ֵĽ�������ʧ��
    else if (CompareElem(elem, tree->data) == 0)
        return false;
        // ��С������뵽������
    else if (CompareElem(elem, tree->data) < 0)
        return InsertBinarySortTree(tree->left_child, elem);
        // ������뵽������
    else
        return InsertBinarySortTree(tree->right_child, elem);
}

// �������������
bool CreateBinarySortTree(BinaryTree &tree, element_type* elem, int start, int length){
    // ������ʼ��
    tree = nullptr;
    int i = 0;
    while(i<length){
        if(!InsertBinarySortTree(tree,elem[start+i]))
            return false;
        i++;
    }
    return true;
}

// ɾ������������
bool DeleteBinarySortTree();