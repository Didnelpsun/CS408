#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// 双亲树结点
typedef struct ParentTreeNode {
	element_type data;
	// 双亲位置域
	int parent;
} ParentTreeNode;

typedef struct {
	// 双亲树结点
	ParentTreeNode nodes[MAXSIZE];
	// 结点树
	int n;
} ParentTree;

// 孩子树孩子结点
typedef struct ChildTreeChildNode {
	// 孩子结点在数组中的索引位置
	int child;
	// 下一个孩子
	struct ChildTreeChildNode* next;
} ChildTreeChildNode;

// 孩子树结点
typedef struct {
	element_type data;
	// 指向第一个孩子
	ChildTreeChildNode* first_child;
} ChildTreeNode;

// 孩子树
typedef struct {
	ChildTreeNode nodes[MAXSIZE];
	// 结点树与根的位置
	int n, r;
} ChildTree;

// 孩子兄弟树
typedef struct ChildSiblingTreeNode {
	element_type data;
	// 第一个孩子与右兄弟指针
	struct ChildSiblingTreeNode* first_child, * next_sibling;
} ChildSiblingTreeNode, * ChildSiblingTree;
