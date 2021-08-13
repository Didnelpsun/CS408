#include <stdio.h>
#include <stdlib.h>
#include "head.h"
#include "sequence_queue.h"

// ��������
typedef struct LinkTreeNode {
	element_type data;
	// ���Һ��ӽ��
	struct LinkTreeNode* lchild, * rchild;
} LinkTreeNode, *LinkTree;

// ��ʼ������
int InitLinkTree(LinkTree tree, element_type elem) {
	tree->data = elem;
	tree->lchild = NULL;
	tree->rchild = NULL;
	return 0;
}

// �����������
int InsertLinkTree(LinkTree tree, element_type elem) {
	LinkTreeNode* node = (LinkTreeNode*)malloc(sizeof(LinkTreeNode));
	if (node) {
		node->data = elem;
		node->lchild = NULL;
		node->rchild = NULL;
		tree->lchild = node;
	}
	else {
		printf("InsertLinkTree:�������ڴ�ռ�ʧ�ܣ�");
		return 1;
	}
	return 0;
}

// �����������
int PreorderTraversalLinkTree(LinkTree tree, int(*visit)(LinkTree elem)) {
	if (tree != NULL) {
		// ���ʸ�Ԫ��
		int result = visit(tree);
		if (result == 1) {
			printf("PreorderTraversalLinkTree:����Ԫ�ز���ʧ�ܣ�");
			return 1;
		}
		// �ݹ�����������
		PreorderTraversalLinkTree(tree->lchild, visit);
		PreorderTraversalLinkTree(tree->rchild, visit);
	}
	return 0;
}

// �����������
int InorderTraversalLinkTree(LinkTree tree, int(*visit)(LinkTree elem)) {
	if (tree != NULL) {
		// �ݹ�����������
		PreorderTraversalLinkTree(tree->lchild, visit);
		// ���ʸ�Ԫ��
		int result = visit(tree);
		if (result == 1) {
			printf("InorderTraversalLinkTree:����Ԫ�ز���ʧ�ܣ�");
			return 1;
		}
		PreorderTraversalLinkTree(tree->rchild, visit);
	}
	return 0;
}

// �����������
int PostorderTraversalLinkTree(LinkTree tree, int(*visit)(LinkTree elem)) {
	if (tree != NULL) {
		// �ݹ���ú������
		PreorderTraversalLinkTree(tree->lchild, visit);
		PreorderTraversalLinkTree(tree->rchild, visit);
		// ���ʸ�Ԫ��
		int result = visit(tree);
		if (result == 1) {
			printf("PostorderTraversalLinkTree:����Ԫ�ز���ʧ�ܣ�");
			return 1;
		}
	}
	return 0;
}

// ���������
int GetLinkTreeDeepth(LinkTree tree) {
	if (tree == NULL) {
		return 0;
	}
	else {
		// �ݹ������������
		int l = GetLinkTreeDeepth(tree->lchild);
		int r = GetLinkTreeDeepth(tree->rchild);
		// �����ʸ�
		return l > r ? l + 1 : r + 1;
	}
}

// �����������
int LevelorderTraversalLinkTree(LinkTree tree, int(*visit)(LinkTree elem)) {
	// ������������
	SequenceQueue queue;
	// ��ʼ������
	InitSequenceQueue(&queue);
	// ָ��Ԫ��
	LinkTree p;
	// ��������
	//EnterSequenceQueue(&queue, tree);
	// ���в�����ѭ��
	while (IsSequenceQueueEmpty(queue) == 0) {
		// ��ͷ����
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

// ������������������
LinkTreeNode* TraversalSearchBST(LinkTree tree, element_type elem) {
	while (tree != NULL && elem != tree->data) {
		if (elem < tree->data) {
			tree = tree->lchild;
		}
		else {
			tree = tree->rchild;
		}
	}
	return tree;
}

// �����������ݹ����
LinkTreeNode* RecursiveSearchBST(LinkTree tree, element_type elem) {
	if (tree == NULL) {
		// Ϊ����
		return NULL;
	}
	if (elem = tree->data) {
		return tree;
	}
	else if (elem < tree->data) {
		return RecursiveSearchBST(tree->lchild, elem);
	}
	else {
		return RecursiveSearchBST(tree->rchild, elem);
	}
}

// �����������ݹ����
int InsertBST(LinkTree tree, element_type elem) {
	if (tree == NULL) {
		tree = (LinkTree)malloc(sizeof(LinkTree));
		if (tree) {
			tree->data = elem;
			tree->lchild = tree->rchild = NULL;
			return 0;
		}
		else {
			printf("BSTInsert:�������ռ�ʧ�ܣ�");
			return 1;
		}
	}
	// �ؼ����ظ�
	else if (elem == tree->data) {
		printf("BSTInsert:�ؼ����ظ���");
		return 1;
	}
	else if (elem < tree->data) {
		return InsertBST(tree->lchild, elem);
	}
	else {
		return InsertBST(tree->rchild, elem);
	}
}

// ���ݹؼ��ֽ�������������
int CreateBST(LinkTree tree, element_type elem[], int n) {
	tree = NULL;
	int i = 0;
	while (true)
	{
		InsertBST(tree, elem[i]);
		i++;
	}
	return 0;
}