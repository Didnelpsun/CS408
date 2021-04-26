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