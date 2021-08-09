#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// 线索二叉树结点
typedef struct ThreadTreeNode {
	element_type data;
	struct ThreadTreeNode* lchild, * rchild;
	int ltag, rtag;
} ThreadTreeNode, *ThreadTree;

// 全局变量，指向当前访问点的前驱
ThreadTreeNode* pre = NULL;
// 中序线索化
int InorderThread(ThreadTreeNode* node) {
	// 左子树为空，建立前驱线索
	if (node->lchild == NULL) {
		node->lchild = pre;
		node->ltag = 1;
	}
	if (pre != NULL && pre->rchild==NULL) {
		// 建立前驱结点的后继线索
		pre->rchild = node;
		pre->rtag = 1;
	}
	pre = node;
	return 0;
}

// 找到以node为根结点的子树中第一个被中序遍历的结点
ThreadTreeNode* FristInOrderNode(ThreadTreeNode* node) {
	//循环找到最左下角结点，不一定是叶子结点
	while (node->ltag == 0) {
		node = node->lchild;
	}
	return node;
}

// 在中序线索二叉树中找到结点node的后继结点
ThreadTreeNode* NextInOrderNode(ThreadTreeNode* node) {
	// 如果有右子树
	if (node->rtag == 0) {
		return FristInOrderNode(node->rchild);
	}
	else {
		return node->rchild;
	}
}

// 对中序线索二叉树实现非递归的中序遍历
int InorderTraversalThreadTree(ThreadTree tree, int(*visit)(ThreadTreeNode* node)) {
	for (ThreadTreeNode* p = FristInOrderNode(tree); p != NULL; p = NextInOrderNode(p)) {
		visit(p);
	}
	return 0;
}

// 找到以node为根结点的子树中前面最后一个被中序遍历的结点
ThreadTreeNode* LastInOrderNode(ThreadTreeNode* node) {
	//循环找到最右下角结点，不一定是叶子结点
	while (node->rtag == 0) {
		node = node->rchild;
	}
	return node;
}

// 在中序线索二叉树中找到结点node的前驱结点
ThreadTreeNode* PreInOrderNode(ThreadTreeNode* node) {
	// 如果有左子树
	if (node->ltag == 0) {
		return LastInOrderNode(node->rchild);
	}
	else {
		return node->lchild;
	}
}

// 对中序线索二叉树实现非递归的逆向中序遍历
int ReverseInorderTraversalThreadTree(ThreadTree tree, int(*visit)(ThreadTreeNode* node)) {
	for (ThreadTreeNode* p = LastInOrderNode(tree); p != NULL; p = PreInOrderNode(p)) {
		visit(p);
	}
	return 0;
}