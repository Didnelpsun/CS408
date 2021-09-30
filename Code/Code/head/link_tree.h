#include "head.h"
#include <stack>
#include <queue>

// 比较元素方法
int CompareElem(element_type elem1, element_type elem2){
    return 0;
}

// 二叉树结点
typedef struct BinaryTreeNode {
    element_type data;
    BinaryTreeNode *left_child, *right_child;
} BinaryTreeNode, *BinaryTree;

// 前序遍历
bool PreOrderBinaryTree(BinaryTree &tree, bool( *function)(BinaryTree &)) {
    if (tree != nullptr) {
        if (!function(tree))
            return false;
        PreOrderBinaryTree(tree->left_child, function);
        PreOrderBinaryTree(tree->right_child, function);
    }
    return true;
}

// 中序遍历
bool InOrderBinaryTree(BinaryTree &tree, bool(*function)(BinaryTree &)) {
    if (tree != nullptr) {
        PreOrderBinaryTree(tree->left_child, function);
        if (!function(tree))
            return false;
        PreOrderBinaryTree(tree->right_child, function);
    }
    return true;
}

// 后序遍历
bool PostOrderBinaryTree(BinaryTree &tree, bool(*function)(BinaryTree &)) {
    if (tree != nullptr) {
        PreOrderBinaryTree(tree->left_child, function);
        PreOrderBinaryTree(tree->right_child, function);
        if (!function(tree))
            return false;
    }
    return true;
}

// 非递归先序遍历
bool PreOrderNonRecursiveBinaryTree(BinaryTree &tree, bool(*function)(BinaryTree &)) {
    // 初始化栈，栈元素为tree指针
    std::stack<BinaryTree> stack;
    // 赋值一个新树
    BinaryTree new_tree = tree;
    // 如果栈不空或new_tree不空时循环
    while (new_tree || !stack.empty()) {
        // 一直向左
        if (new_tree) {
            // 访问当前结点
            if (!function(new_tree)) {
                printf("PreOrderNonRecursive:访问结点失败！");
                return false;
            }
            // 当前结点入栈
            stack.push(new_tree);
            // 左孩子不空则一直向左
            new_tree = new_tree->left_child;
        }
            // 出栈，并转向右子树
        else {
            // 返回栈顶的元素，但不删除该元素
            new_tree = stack.top();
            // 删除栈顶元素但不返回其值
            stack.pop();
            // 向右
            new_tree = new_tree->right_child;
            // 返回while
        }
    }
    return true;
}

// 非递归中序遍历
bool InOrderNonRecursiveBinaryTree(BinaryTree &tree, bool(*function)(BinaryTree &)) {
    // 初始化栈，栈元素为tree指针
    std::stack<BinaryTree> stack;
    // 赋值一个新树
    BinaryTree new_tree = tree;
    // 如果栈不空或new_tree不空时循环
    while (new_tree || !stack.empty()) {
        // 一直向左
        if (new_tree) {
            // 当前结点入栈
            stack.push(new_tree);
            // 左孩子不空则一直向左
            new_tree = new_tree->left_child;
        }
            // 出栈，并转向右子树
        else {
            // 返回栈顶的元素，但不删除该元素
            new_tree = stack.top();
            // 删除栈顶元素但不返回其值
            stack.pop();
            // 访问出栈结点
            if (!function(new_tree)) {
                printf("InOrderNonRecursive:访问结点失败！");
                return false;
            }
            // 向右
            new_tree = new_tree->right_child;
            // 返回while
        }
    }
    return true;
}

// 层序遍历
bool LevelOrderBinaryTree(BinaryTree &tree, bool(*function)(BinaryTree &)) {
    // 初始化辅助队列
    std::queue<BinaryTree> queue;
    // 初始化树结点
    BinaryTree new_tree = tree;
    // 根结点入队
    queue.push(new_tree);
    // 若队列非空则循环
    while (!queue.empty()) {
        // 队头结点出队
        new_tree = queue.front();
        queue.pop();
        // 访问出队结点
        if (!function(new_tree)) {
            printf("LevelOrder:访问结点失败！");
            return false;
        }
        // 如果左子树不空则其根结点入队
        if (new_tree->left_child != nullptr) {
            queue.push(new_tree);
        }
        if (new_tree->right_child != nullptr) {
            queue.push(new_tree);
        }
    }
    return true;
}

// 二叉排序树查找
BinaryTreeNode *SearchBinarySortTree(BinaryTree tree, element_type elem) {
    BinaryTree node = tree;
    // 若树空或等于根结点值就结束循环
    while (node != nullptr && elem != node->data) {
        // 若小于则左子树查找
        if (CompareElem(elem, node->data) < 0)
            node = node->left_child;
        else
            node = node->right_child;
    }
    return node;
}

// 二叉排序树插入
bool InsertBinarySortTree(BinaryTree &tree, element_type elem) {
    if (elem == NULL){
        printf("InsertBinarySortTree:插入数据不应为空！\n");
        return false;
    }
    // 若原树为空，则将新插入的记录作为根结点
    if (tree == nullptr) {
        tree = (BinaryTree) malloc(sizeof(BinaryTreeNode));
        tree->data = elem;
        tree->left_child = tree->right_child = nullptr;
        return true;
    }
        // 若存在相同关键字的结点则插入失败
    else if (CompareElem(elem, tree->data) == 0)
        return false;
        // 若小于则插入到左子树
    else if (CompareElem(elem, tree->data) < 0)
        return InsertBinarySortTree(tree->left_child, elem);
        // 否则插入到右子树
    else
        return InsertBinarySortTree(tree->right_child, elem);
}

// 构造二叉排序树
bool CreateBinarySortTree(BinaryTree &tree, element_type* elem, int start, int length){
    // 将树初始化
    tree = nullptr;
    int i = 0;
    while(i<length){
        if(!InsertBinarySortTree(tree,elem[start+i]))
            return false;
        i++;
    }
    return true;
}

// 删除二叉排序树
bool DeleteBinarySortTree();