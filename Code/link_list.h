#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// 链表结点
typedef struct {
	element_type data;
	struct LinkNode* next;
} LinkNode, *LinkList;

// 初始化有头节点单链表
int InitLinkListWithHead(LinkList list) {
	list = (LinkNode*)malloc(sizeof(LinkNode));
	if (list == NULL) {
		return 1;
	}
	list->next = NULL;
	return 0;
}

// 初始化无头节点单链表
int InitLinkListWithoutHead(LinkList list) {
	list = NULL;
	return 0;
}

// 判断有头节点单链表是否为空
int IsLLinkListEmptyWithHead(LinkList list) {
	if (list->next == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

// 判断无头节点单链表是否为空
int IsLLinkListEmptyWithoutHead(LinkList list) {
	if (list == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

// 插入有头节点单链表元素
int InsertLinkListWithHead(LinkList list, int index, element_type elem) {
	if (index < 1) {
		printf("InsertLinkListWithHead:插入索引值过小！\n");
		return 1;
	}
	// 定义一个结点指针p指向当前扫描到的结点
	LinkNode* p;
	// 定义一个变量i表示当前扫描到的结点的索引号
	int i = 0;
	// 将链表头结点指向p，为第0个结点
	p = list;
	// 循环遍历到达指定索引号的单链表的结点
	// 条件是当前结点的下一个不为空且索引号到达，所到达的结点一定不是空结点
	while (p->next != NULL && i < index-1) {
		p = p->next;
		i++;
	}
	// 如果此时i小于index-1，表示遍历完还没有到达对应的索引
	if (i < index-1) {
		printf("InsertLinkListWithHead:插入索引值过大！\n");
		return 1;
	}
	// 此时i==index-1
	LinkNode* s = (LinkNode*)malloc(sizeof(LinkNode));
	if (s == NULL) {
		printf("InsertLinkListWithHead:分配内存失败！\n");
		return 1;
	}
	s->data = elem;
	// 将p原来的后继给新的结点
	s->next = p->next;
	p->next = s;
	return 0;
}

// 插入无头节点单链表元素
int InsertLinkListWithoutHead(LinkList list, int index, element_type elem) {
	if (index < 0) {
		printf("InsertLinkListWithoutHead:插入索引值过小！\n");
		return 1;
	}
	if (index == 0) {
		LinkNode* s = (LinkNode*)malloc(sizeof(LinkNode));
		if (s == NULL) {
			printf("InsertLinkListWithoutHead:分配内存失败！\n");
			return 1;
		}
		s->data = elem;
		// 将s的后继设为list指针
		s->next = list;
		// 将list指针设置为s指针
		list = s;
		return 0;
	}
	// 定义一个结点指针p指向当前扫描到的结点
	LinkNode* p;
	// 定义一个变量i表示当前扫描到的结点的索引号
	int i = 0;
	// 将链表头结点指向p，为第0个结点
	p = list;
	// 循环遍历到达指定索引号的单链表的结点
	// 条件是当前结点的下一个不为空且索引号到达，所到达的结点一定不是空结点
	while (p->next != NULL && i < index - 1) {
		p = p->next;
		i++;
	}
	// 如果此时i小于index-1，表示遍历完还没有到达对应的索引
	if (i < index - 1) {
		printf("InsertLinkListWithoutHead:插入索引值过大！\n");
		return 1;
	}
	// 此时i==index-1
	LinkNode* s = (LinkNode*)malloc(sizeof(LinkNode));
	s->data = elem;
	// 将p原来的后继给新的结点
	s->next = p->next;
	p->next = s;
	return 0;
}

// 后插入单链表元素
int InsertNextLinkNode(LinkNode* node, element_type elem) {
	if (node == NULL) {
		return 1;
	}
	LinkNode* s = (LinkNode*)malloc(sizeof(LinkNode));
	// 如果分配空间失败
	if (s == NULL) {
		printf("InsertNextLinkNode:分配内存失败！\n");
		return 1;
	}
	s->data = elem;
	s->next = node->next;
	node->next = s;
	return 0;
}

// 前插入单链表元素
int InsertPriorLinkNode(LinkNode* node, element_type elem) {
	if (node == NULL) {
		return 1;
	}
	LinkNode* s = (LinkNode*)malloc(sizeof(LinkNode));
	// 如果分配空间失败
	if (s == NULL) {
		printf("InsertPriorLinkNode:分配内存失败！\n");
		return 1;
	}
	s->next = node->next;
	node->next = s;
	s->data = node->data;
	node->data = elem;
	return 0;
}