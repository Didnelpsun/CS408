#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// 双链表结点
typedef struct DoubleLinkNode{
	element_type data;
	struct DoubleLinkNode* prior, * next;
} DoubleLinkNode, *DoubleLinkList;


// 初始化有头节点双链表
int InitDoubleLinkListWithHead(DoubleLinkList list) {
	list = (DoubleLinkNode*)malloc(sizeof(DoubleLinkNode));
	// 分配内存失败
	if (list == NULL) {
		printf("InitDoubleLinkListWithHead:初始化分配内存失败！");
		return 1;
	}
	// 头结点的前驱结点始终为NULL
	list->prior = NULL;
	list->next = NULL;
	return 0;
}

// 判断有头节点双链表是否为空
int IsDoubleLinkListEmptyWithHead(DoubleLinkList list) {
	if (list->next == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

// 后插入双链表元素
int InsertNextDoubleLinkNode(DoubleLinkNode* node, element_type elem) {
	if (node == NULL) {
		printf("InsertNextDoubleLinkNode:插入结点为空！");
		return 1;
	}
	DoubleLinkNode* s = (DoubleLinkNode*)malloc(sizeof(DoubleLinkNode));
	// 如果分配空间失败
	if (s == NULL) {
		printf("InsertNextDoubleLinkNode:分配内存失败！\n");
		return 1;
	}
	s->data = elem;
	// 将新建结点s插入结点node后
	s->next = node->next;
	// 如果有后继结点，将p原来的后继给s结点
	if (node->next->prior) {
		node->next->prior = s;
	}
	// 交换s的前驱和后继
	s->prior = node;
	node->next = s;
	return 0;
}

// 前插入双链表元素
int InsertPriorDoubleLinkNode(DoubleLinkNode* node, element_type elem) {
	if (node == NULL) {
		printf("InsertPriorDoubleLinkNode:插入结点为空！");
		return 1;
	}
	DoubleLinkNode* s = (DoubleLinkNode*)malloc(sizeof(DoubleLinkNode));
	// 如果分配空间失败
	if (s == NULL) {
		printf("InsertPriorDoubleLinkNode:分配内存失败！\n");
		return 1;
	}
	s->next = node->next;
	node->next = s;
	s->data = node->data;
	node->data = elem;
	return 0;
}

// 删除双链表后续结点
int DeleteNextDoubleLinkListNode(DoubleLinkNode* node) {
	if (node == NULL) {
		printf("DeleteDoubleLinkListNode:删除结点为空！");
		return 1;
	}
	DoubleLinkNode* p = node->next;
	if (p == NULL) {
		printf("DeleteDoubleLinkListNode:删除结点后续结点为空！");
		return 1;
	}
	node->next = p->next;
	// 如果p结点为最后一个结点
	if (p->next != NULL) {
		p->next->prior = node;
	}
	free(p);
	return 0;
}

// 销毁双链表
int DestroyDoubleLinkList(DoubleLinkList list) {
	// 循环删除各个结点
	while (list->next != NULL) {
		DeleteNextDoubleLinkListNode(list);
	}
	// 释放头结点
	free(list);
	list = NULL;
	return 0;
}

// 初始化有头节点循环双链表
int InitCircularDoubleLinkListWithHead(DoubleLinkList list) {
	list = (DoubleLinkNode*)malloc(sizeof(DoubleLinkNode));
	if (list == NULL) {
		printf("InitCircularDoubleLinkListWithHead:初始化分配内存失败！");
		return 1;
	}
	// 前后指针都指向其本身
	list->next = list;
	list->prior = list;
	return 0;
}

// 判断有头节点循环双链表是否为空
int IsCircularDoubleLinkListEmptyWithHead(DoubleLinkList list) {
	if (list->next == list) {
		return 1;
	}
	else {
		return 0;
	}
}

// 判断结点是否尾有头节点循环双链表的尾结点
int IsCircularDoubleLinkListEndWithHead(DoubleLinkList list, DoubleLinkNode* node) {
	if (node->next == list) {
		return 1;
	}
	else {
		return 0;
	}
}

// 后插入循环双链表元素
// 与双链表一样，唯一区别就是不用判别后一个元素是否为NULL，因为是连接在一起的
int InsertNextCircularDoubleLinkNode(DoubleLinkNode* node, element_type elem) {
	if (node == NULL) {
		printf("InsertNextDoubleLinkNode:插入结点为空！");
		return 1;
	}
	DoubleLinkNode* s = (DoubleLinkNode*)malloc(sizeof(DoubleLinkNode));
	// 如果分配空间失败
	if (s == NULL) {
		printf("InsertNextDoubleLinkNode:分配内存失败！\n");
		return 1;
	}
	s->data = elem;
	// 将新建结点s插入结点node后
	s->next = node->next;
	// 不同之处，一定有后继结点，将p原来的后继给s结点
	node->next->prior = s;
	// 交换s的前驱和后继
	s->prior = node;
	node->next = s;
	return 0;
}

// 删除循环双链表后续结点
// 与双链表一样，唯一区别就是不用判别后一个元素是否为NULL，因为是连接在一起的
int DeleteNextCircularDoubleLinkListNode(DoubleLinkNode* node) {
	if (node == NULL) {
		printf("DeleteDoubleLinkListNode:删除结点为空！");
		return 1;
	}
	DoubleLinkNode* p = node->next;
	if (p == NULL) {
		printf("DeleteDoubleLinkListNode:删除结点后续结点为空！");
		return 1;
	}
	node->next = p->next;
	// 不同之处
	p->next->prior = node;
	free(p);
	return 0;
}