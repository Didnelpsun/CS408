#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// �������������
typedef struct ThreadTreeNode {
	element_type data;
	struct ThreadTreeNode* lchild, * rchild;
	int ltag, rtag;
} ThreadTreeNode, *ThreadTree;

// ȫ�ֱ�����ָ��ǰ���ʵ��ǰ��
ThreadTreeNode* pre = NULL;
// ����������
int InorderThread(ThreadTreeNode* node) {
	// ������Ϊ�գ�����ǰ������
	if (node->lchild == NULL) {
		node->lchild = pre;
		node->ltag = 1;
	}
	if (pre != NULL && pre->rchild==NULL) {
		// ����ǰ�����ĺ������
		pre->rchild = node;
		pre->rtag = 1;
	}
	pre = node;
	return 0;
}

// �ҵ���nodeΪ�����������е�һ������������Ľ��
ThreadTreeNode* FristInOrderNode(ThreadTreeNode* node) {
	//ѭ���ҵ������½ǽ�㣬��һ����Ҷ�ӽ��
	while (node->ltag == 0) {
		node = node->lchild;
	}
	return node;
}

// �������������������ҵ����node�ĺ�̽��
ThreadTreeNode* NextInOrderNode(ThreadTreeNode* node) {
	// �����������
	if (node->rtag == 0) {
		return FristInOrderNode(node->rchild);
	}
	else {
		return node->rchild;
	}
}

// ����������������ʵ�ַǵݹ���������
int InorderTraversalThreadTree(ThreadTree tree, int(*visit)(ThreadTreeNode* node)) {
	for (ThreadTreeNode* p = FristInOrderNode(tree); p != NULL; p = NextInOrderNode(p)) {
		visit(p);
	}
	return 0;
}

// �ҵ���nodeΪ������������ǰ�����һ������������Ľ��
ThreadTreeNode* LastInOrderNode(ThreadTreeNode* node) {
	//ѭ���ҵ������½ǽ�㣬��һ����Ҷ�ӽ��
	while (node->rtag == 0) {
		node = node->rchild;
	}
	return node;
}

// �������������������ҵ����node��ǰ�����
ThreadTreeNode* PreInOrderNode(ThreadTreeNode* node) {
	// �����������
	if (node->ltag == 0) {
		return LastInOrderNode(node->rchild);
	}
	else {
		return node->lchild;
	}
}

// ����������������ʵ�ַǵݹ�������������
int ReverseInorderTraversalThreadTree(ThreadTree tree, int(*visit)(ThreadTreeNode* node)) {
	for (ThreadTreeNode* p = LastInOrderNode(tree); p != NULL; p = PreInOrderNode(p)) {
		visit(p);
	}
	return 0;
}