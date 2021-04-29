#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// 邻接矩阵图
typedef struct {
	// 顶点表
	element_type vex[MAXSIZE];
	// 邻接矩阵，边表
	int edge[MAXSIZE][MAXSIZE];
	// 图当前的顶点数和边数/弧数
	int vex_num, arc_num;
} AdjacencyMatrixGraph;

// 邻接表结点
typedef struct AdjacencyListNode {
	// 顶点信息
	element_type vex;
	// 第一条边
	AdjacencyListNode* first;
} AdjacencyListNode, AdjacencyList[MAXSIZE];

// 邻接表
typedef struct {
	AdjacencyList data;
	int vex_num, arc_num;
} AdjacencyListGraph;
