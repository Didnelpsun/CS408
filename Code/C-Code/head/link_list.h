#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// 单链表结点
typedef struct LinkListNode {
	element_type data;
	struct LinkListNode* next;
} LinkListNode, *LinkList;

// 由于C语言无法参数赋值，所以必须借助一个中间变量完成
// 初始化有头节点单链表
int InitLinkListWithHead(LinkList list) {
	if (list) {
		list->data = NULL;
		list->next = NULL;
		return 0;
	}
	else {
		printf("InitLinkListWithHead:指针为空无法初始化！");
		return 1;
	}
}

// C语言无法这样实现初始化，因为无法实现引用传递，不能赋值参数
// 初始化无头节点单链表
int InitLinkListWithoutHead(LinkList list) {
	list = NULL;
	return 0;
}

// 创建有头节点单链表
LinkList CreateLinkListWithHead() {
	LinkList list = (LinkListNode*)malloc(sizeof(LinkListNode));
	if (list) {
		list->data = NULL;
		list->next = NULL;
	}
	else {
		printf("CreateLinkListWithHead:分配空间失败！");
	}
	return list;
}

// 创建无头节点单链表
LinkList CreateLinkListWithoutHead() {
	return NULL;
}


// 判断有头节点单链表是否为空
int EmptyLinkListWithHead(LinkList list) {
	if (list->next) {
		return 0;
	}
	else {
		return 1;
	}
}

// 判断无头节点单链表是否为空
int EmptyLLinkListWithoutHead(LinkList list) {
	if (list) {
		return 0;
	}
	else {
		return 1;
	}
}

// 插入有头节点单链表元素
// 0号节点是头节点
int InsertLinkListWithHead(LinkList list, int index, element_type elem) {
	if (index < 1) {
		printf("InsertLinkListWithHead:插入索引值过小！\n");
		return 1;
	}
	// 定义一个结点指针p指向当前扫描到的结点
	LinkListNode* p;
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
		printf("InsertLinkListWithHead:插入索引值过大！\n");
		return 1;
	}
	// 此时i==index-1
	LinkListNode* s = (LinkListNode*)malloc(sizeof(LinkListNode));
	if (s) {
		s->data = elem;
		// 将p原来的后继给新的结点
		s->next = p->next;
		p->next = s;
		return 0;
	}
	else {
		printf("InsertLinkListWithHead:分配内存失败！\n");
		return 1;
	}
}

// 插入无头节点单链表元素
// C语言也无法调用这个函数
int InsertLinkListWithoutHead(LinkList list, int index, element_type elem) {
	return 1;
}