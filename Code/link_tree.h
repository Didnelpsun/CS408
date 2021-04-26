#include <stdio.h>
#include <stdlib.h>
#include "head.h"
#include "sequence_queue.h"

// 链二叉树
typedef struct LinkTreeNode {
	element_type data;
	// 左右孩子结点
	struct LinkTreeNode* lchild, * rchild;
} LinkTreeNode, *LinkTree;

// 初始化链树
int InitLinkTree(LinkTree tree, element_type elem) {
	tree->data = elem;
	tree->lchild = NULL;
	tree->rchild = NULL;
	return 0;
}

// 插入链树结点
int InsertLinkTree(LinkTree tree, element_type elem) {
	LinkTreeNode* node = (LinkTreeNode*)malloc(sizeof(LinkTreeNode));
	if (node) {
		node->data = elem;
		node->lchild = NULL;
		node->rchild = NULL;
		tree->lchild = node;
	}
	else {
		printf("InsertLinkTree:分配新内存空间失败！");
		return 1;
	}
	return 0;
}

// 先序遍历链树
int PreorderTraversalLinkTree(LinkTree tree, int(*visit)(LinkTree elem)) {
	if (tree != NULL) {
		// 访问根元素
		int result = visit(tree);
		if (result == 1) {
			printf("PreorderTraversalLinkTree:访问元素操作失败！");
			return 1;
		}
		// 递归调用先序遍历
		PreorderTraversalLinkTree(tree->lchild, visit);
		PreorderTraversalLinkTree(tree->rchild, visit);
	}
	return 0;
}

// 中序遍历链树
int InorderTraversalLinkTree(LinkTree tree, int(*visit)(LinkTree elem)) {
	if (tree != NULL) {
		// 递归调用中序遍历
		PreorderTraversalLinkTree(tree->lchild, visit);
		// 访问根元素
		int result = visit(tree);
		if (result == 1) {
			printf("InorderTraversalLinkTree:访问元素操作失败！");
			return 1;
		}
		PreorderTraversalLinkTree(tree->rchild, visit);
	}
	return 0;
}

// 后序遍历链树
int PostorderTraversalLinkTree(LinkTree tree, int(*visit)(LinkTree elem)) {
	if (tree != NULL) {
		// 递归调用后序遍历
		PreorderTraversalLinkTree(tree->lchild, visit);
		PreorderTraversalLinkTree(tree->rchild, visit);
		// 访问根元素
		int result = visit(tree);
		if (result == 1) {
			printf("PostorderTraversalLinkTree:访问元素操作失败！");
			return 1;
		}
	}
	return 0;
}

// 求树的深度
int GetLinkTreeDeepth(LinkTree tree) {
	if (tree == NULL) {
		return 0;
	}
	else {
		// 递归遍历左右子树
		int l = GetLinkTreeDeepth(tree->lchild);
		int r = GetLinkTreeDeepth(tree->rchild);
		// 最后访问根
		return l > r ? l + 1 : r + 1;
	}
}

// 层序遍历链树
int LevelorderTraversalLinkTree(LinkTree tree, int(*visit)(LinkTree elem)) {
	// 建立辅助队列
	SequenceQueue queue;
	// 初始化队列
	InitSequenceQueue(&queue);
	// 指定元素
	LinkTree p;
	// 根结点入队
	//EnterSequenceQueue(&queue, tree);
	// 队列不空则循环
	while (IsSequenceQueueEmpty(queue) == 0) {
		// 队头出队
		//ExitSequenceQueue(&queue, &p);
		//visit(p);
		/*if (p->lchild != NULL) {
			EnterSequenceQueue(&queue, p->lchild);
		}
		if (p->rchild != NULL) {
			EnterSequenceQueue(&queue, p->rchild);
		}*/
	}
}