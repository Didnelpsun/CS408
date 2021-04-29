#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// �ڽӾ���ͼ
typedef struct {
	// �����
	element_type vex[MAXSIZE];
	// �ڽӾ��󣬱߱�
	int edge[MAXSIZE][MAXSIZE];
	// ͼ��ǰ�Ķ������ͱ���/����
	int vex_num, arc_num;
} AdjacencyMatrixGraph;

// �ڽӱ���
typedef struct AdjacencyListNode {
	// ������Ϣ
	element_type vex;
	// ��һ����
	AdjacencyListNode* first;
} AdjacencyListNode, AdjacencyList[MAXSIZE];

// �ڽӱ�
typedef struct {
	AdjacencyList data;
	int vex_num, arc_num;
} AdjacencyListGraph;
