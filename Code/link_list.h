#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// 单链表结点
typedef struct LinkListNode {
	element_type data;
	struct LinkListNode* next;
} LinkListNode, *LinkList;

// 初始化有头节点单链表
int InitLinkListWithHead(LinkList list) {
	list = (LinkListNode*)malloc(sizeof(LinkListNode));
	if (list == NULL) {
		printf("InitLinkListWithHead:初始化分配内存失败！");
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
int IsLinkListEmptyWithHead(LinkList list) {
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
	LinkListNode* p;
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
	LinkListNode* s = (LinkListNode*)malloc(sizeof(LinkListNode));
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
		LinkListNode* s = (LinkListNode*)malloc(sizeof(LinkListNode));
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
		printf("InsertLinkListWithoutHead:插入索引值过大！\n");
		return 1;
	}
	// 此时i==index-1
	LinkListNode* s = (LinkListNode*)malloc(sizeof(LinkListNode));
	s->data = elem;
	// 将p原来的后继给新的结点
	s->next = p->next;
	p->next = s;
	return 0;
}

// 后插入单链表元素
int InsertNextLinkListNode(LinkListNode* node, element_type elem) {
	if (node == NULL) {
		printf("InsertNextLinkListNode:插入结点为空！");
		return 1;
	}
	LinkListNode* s = (LinkListNode*)malloc(sizeof(LinkListNode));
	// 如果分配空间失败
	if (s == NULL) {
		printf("InsertNextLinkListNode:分配内存失败！\n");
		return 1;
	}
	s->data = elem;
	s->next = node->next;
	node->next = s;
	return 0;
}

// 前插入单链表元素
int InsertPriorLinkListNode(LinkListNode* node, element_type elem) {
	if (node == NULL) {
		printf("InsertPriorLinkListNode:插入结点为空！");
		return 1;
	}
	LinkListNode* s = (LinkListNode*)malloc(sizeof(LinkListNode));
	// 如果分配空间失败
	if (s == NULL) {
		printf("InsertPriorLinkListNode:分配内存失败！\n");
		return 1;
	}
	s->next = node->next;
	node->next = s;
	s->data = node->data;
	node->data = elem;
	return 0;
}

// 删除有头节点单链表元素
int DeleteLinkListWithHead(LinkList list, int index, element_type *elem) {
	if (index < 1) {
		printf("DeleteLinkListWithHead:删除索引值过小！\n");
		return 1;
	}
	// p指向当前扫描的结点
	LinkListNode* p;
	// i表示当前指向的是第几个结点
	int i = 0;
	// 指向头结点
	p = list;
	while (p != NULL && i < index - 1) {
		p = p->next;
		i++;
	}
	if (p == NULL || p->next == NULL) {
		printf("DeleteLinkListWithHead:删除索引值过大！\n");
		return 1;
	}
	// q指向被删除的结点
	LinkListNode* q = p->next;
	// 获取删除的元素数据
	*elem = q->data;
	// 将q结点从链表中断开
	p->next = q->next;
	free(q);
	return 0;
}

// 删除无头节点单链表元素
int DeleteLinkListWithHead(LinkList list, int index, element_type* elem) {
	if (index < 0) {
		printf("DeleteLinkListWithHead:删除索引值过小！\n");
		return 1;
	}
	// p指向当前扫描的结点
	LinkListNode* p;
	// i表示当前指向的是第几个结点
	int i = 0;
	// 指向头结点
	p = list;
	// 如果删除第一个第0号结点
	if (index == 0) {
		list = p->next;
		free(p);
		return 0;
	}
	while (p != NULL && i < index - 1) {
		p = p->next;
		i++;
	}
	if (p == NULL || p->next == NULL) {
		printf("DeleteLinkListWithHead:删除索引值过大！\n");
		return 1;
	}
	// q指向被删除的结点
	LinkListNode* q = p->next;
	// 获取删除的元素数据
	*elem = q->data;
	// 将q结点从链表中断开
	p->next = q->next;
	free(q);
	return 0;
}

// 删除单链表元素
int DeleteLinkListNode(LinkListNode* node) {
	if (node == NULL) {
		printf("DeleteLinkListNode:本结点是空结点无法删除！");
		return 1;
	}
	// 如果该结点为最后一个结点，无法找到前驱结点，无法操作
	if (node->next = NULL) {
		printf("DeleteLinkListNode:后继结点为空无法操作！");
		return 1;
	}
	// 指向后继结点
	LinkListNode* p = node->next;
	// 交换数据
	node->data = p->data;
	// 断开结点
	node->next = p->next;
	free(p);
	return 0;
}

// 按位查找单链表元素
element_type GetLinkListElement(LinkList list, int index) {
	if (index < 0) {
		printf("GetLinkListElement:查找索引值过小！\n");
		return NULL;
	}
	// 定义一个结点指针p指向当前扫描到的结点
	LinkListNode* p;
	// 定义一个变量i表示当前扫描到的结点的索引号
	int i = 0;
	// 将链表头结点指向p，为第0个结点
	p = list;
	// 循环遍历到达指定索引号的单链表的结点
	// 条件是当前结点的下一个不为空且索引号到达，所到达的结点一定不是空结点
	while (p->next != NULL && i < index) {
		p = p->next;
		i++;
	}
	// 如果查找索引大于当前扫描索引
	if (i < index) {
		printf("GetLinkListElement:查找索引值过大！\n");
		return NULL;
	}
	return p->data;
}

// 按位查找单链表结点
LinkListNode* GetLinkListNode(LinkList list, int index) {
	if (index < 0) {
		printf("GetLinkListNode:查找索引值过小！\n");
		return NULL;
	}
	// 定义一个结点指针p指向当前扫描到的结点
	LinkListNode* p;
	// 定义一个变量i表示当前扫描到的结点的索引号
	int i = 0;
	// 将链表头结点指向p，为第0个结点
	p = list;
	// 循环遍历到达指定索引号的单链表的结点
	// 条件是当前结点的下一个不为空且索引号到达，所到达的结点一定不是空结点
	while (p->next != NULL && i < index) {
		p = p->next;
		i++;
	}
	// 如果查找索引大于当前扫描索引
	if (i < index) {
		printf("GetLinkListNode:查找索引值过大！\n");
	}
	// 如果索引值过大，其p也会指向最后一个NULL，所以返回值都是一样为NULL，不需要单独处理
	return p;
}


// 按值查找单链表结点
LinkListNode* LocateLinkListNode(LinkList list, element_type elem) {
	LinkListNode* p = list;
	while (p != NULL && p->data != elem) {
		p = p->next;
	}
	return p;
}

// 求链表长度
int GetLength(LinkList list) {
	int len = 0;
	LinkListNode* p = list;
	while (p->next != NULL) {
		p = p->next;
		len++;
	}
	return len;
}

// 后插建立带头节点单链表
LinkList TailBuildLinkListWithHead(LinkList list, int length) {
	element_type elem;
	list = (LinkList)malloc(sizeof(LinkListNode));
	// s指针为一个中间变量指针，r指针为尾指针（next指向最后一个元素）
	LinkListNode* s, * r = list;
	int i = 0;
	element_type x;
	if (length < 1) {
		printf("TailBuildLinkListWithHead:输入的单链表长度过小！");
		return 1;
	}
	while (i < length) {
		scanf("%d", &x);
		s = (LinkListNode*)malloc(sizeof(LinkListNode));
		s->data = x;
		r->next = s;
		r = s;
		i++;
	}
	r->next = NULL;
	return list;
}

// 前插建立带头节点单链表
LinkList HeadBuildLinkListWithHead(LinkList list, int length) {
	element_type elem;
	list = (LinkList)malloc(sizeof(LinkListNode));
	// 将单链表尾部设置为NULL
	list->next = NULL;
	// s指针为一个中间变量指针
	LinkListNode* s;
	int i = 0;
	element_type x;
	if (length < 1) {
		printf("HeadBuildLinkListWithHead:输入的单链表长度过小！");
		return 1;
	}
	while (i < length) {
		scanf("%d", &x);
		s = (LinkListNode*)malloc(sizeof(LinkListNode));
		s->data = x;
		s->next = list->next;
		list->next = s;
		i++;
	}
	return list;
}

// 初始化有头节点循环单链表
int InitCircularLinkListWithHead(LinkList list) {
	list = (LinkListNode*)malloc(sizeof(LinkListNode));
	if (list == NULL) {
		printf("InitCircularLinkListWithHead:初始化分配内存失败！");
		return 1;
	}
	list->next = list;
	return 0;
}

// 判断有头节点循环单链表是否为空
int IsCircularLinkListEmptyWithHead(LinkList list) {
	if (list->next == list) {
		return 1;
	}
	else {
		return 0;
	}
}

// 判断结点是否尾有头节点循环单链表的尾结点
int IsCircularLinkListEndWithHead(LinkList list, LinkListNode* node) {
	if (node->next == list) {
		return 1;
	}
	else {
		return 0;
	}
}