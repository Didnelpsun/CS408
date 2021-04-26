#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// ˫�������
typedef struct ParentTreeNode {
	element_type data;
	// ˫��λ����
	int parent;
} ParentTreeNode;

typedef struct {
	// ˫�������
	ParentTreeNode nodes[MAXSIZE];
	// �����
	int n;
} ParentTree;

// ���������ӽ��
typedef struct ChildTreeChildNode {
	// ���ӽ���������е�����λ��
	int child;
	// ��һ������
	struct ChildTreeChildNode* next;
} ChildTreeChildNode;

// ���������
typedef struct {
	element_type data;
	// ָ���һ������
	ChildTreeChildNode* first_child;
} ChildTreeNode;

// ������
typedef struct {
	ChildTreeNode nodes[MAXSIZE];
	// ����������λ��
	int n, r;
} ChildTree;

// �����ֵ���
typedef struct ChildSiblingTreeNode {
	element_type data;
	// ��һ�����������ֵ�ָ��
	struct ChildSiblingTreeNode* first_child, * next_sibling;
} ChildSiblingTreeNode, * ChildSiblingTree;
