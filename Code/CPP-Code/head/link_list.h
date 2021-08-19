#include <cstdio>
#include <cstdlib>
#include "head.h"

// 单链表结点
class LinkListNode {
public:
    // 数据
    element_type data;
    // 指针
    LinkListNode* next;
    // 构造函数
    LinkListNode();
    explicit LinkListNode(element_type data);
};

class LinkList{
public:
    // 指针
    LinkListNode* next;
    // 链表长度
    int length;
    // 构造函数
    LinkList();
    // 判空
    bool Empty();
};

class LinkListWithHead: public LinkList{
public:
    // 构造函数
    LinkListWithHead();
};

class LinkListWithoutHead: public LinkList{
public:
    // 数据
    element_type data;
    // 构造函数
    LinkListWithoutHead();
};

LinkListNode::LinkListNode() {
    this->data = NULL;
    this->next = nullptr;
}

LinkListNode::LinkListNode(element_type data) {
    this->data = data;
    this->next = nullptr;
}

LinkList::LinkList() {
    this->next= nullptr;
    this->length =0;
}

LinkListWithHead::LinkListWithHead() = default;

LinkListWithoutHead::LinkListWithoutHead() {
    this->data = NULL;
}

bool LinkList::Empty() {
    if(this->length==0){
        return true;
    } else {
        return false;
    }
}


//// 插入有头节点单链表元素
//// 0号节点是头节点
//int InsertLinkListWithHead(LinkList list, int index, element_type elem) {
//	if (index < 1) {
//		printf("InsertLinkListWithHead:插入索引值过小！\n");
//		return 1;
//	}
//	// 定义一个结点指针p指向当前扫描到的结点
//	LinkListNode* p;
//	// 定义一个变量i表示当前扫描到的结点的索引号
//	int i = 0;
//	// 将链表头结点指向p，为第0个结点
//	p = list;
//	// 循环遍历到达指定索引号的单链表的结点
//	// 条件是当前结点的下一个不为空且索引号到达，所到达的结点一定不是空结点
//	while (p->next != NULL && i < index - 1) {
//		p = p->next;
//		i++;
//	}
//	// 如果此时i小于index-1，表示遍历完还没有到达对应的索引
//	if (i < index - 1) {
//		printf("InsertLinkListWithHead:插入索引值过大！\n");
//		return 1;
//	}
//	// 此时i==index-1
//	LinkListNode* s = (LinkListNode*)malloc(sizeof(LinkListNode));
//	if (s) {
//		s->data = elem;
//		// 将p原来的后继给新的结点
//		s->next = p->next;
//		p->next = s;
//		return 0;
//	}
//	else {
//		printf("InsertLinkListWithHead:分配内存失败！\n");
//		return 1;
//	}
//}
//
//// 插入无头节点单链表元素
//// C语言也无法调用这个函数
//int InsertLinkListWithoutHead(LinkList list, int index, element_type elem) {
//	if (index < 0) {
//		printf("InsertLinkListWithoutHead:插入索引值过小！\n");
//		return 1;
//	}
//	if (index == 0) {
//		LinkListNode* s = (LinkListNode*)malloc(sizeof(LinkListNode));
//		if (s) {
//			s->data = elem;
//			// 将s的后继设为list指针
//			s->next = list;
//			// 将list指针设置为s指针
//			list = s;
//			return 0;
//		}
//		else {
//			printf("InsertLinkListWithoutHead:分配内存失败！\n");
//			return 1;
//		}
//	}
//	// 定义一个结点指针p指向当前扫描到的结点
//	LinkListNode* p;
//	// 定义一个变量i表示当前扫描到的结点的索引号
//	int i = 0;
//	// 将链表头结点指向p，为第0个结点
//	p = list;
//	// 循环遍历到达指定索引号的单链表的结点
//	// 条件是当前结点的下一个不为空且索引号到达，所到达的结点一定不是空结点
//	while (p->next != NULL && i < index - 1) {
//		p = p->next;
//		i++;
//	}
//	// 如果此时i小于index-1，表示遍历完还没有到达对应的索引
//	if (i < index - 1) {
//		printf("InsertLinkListWithoutHead:插入索引值过大！\n");
//		return 1;
//	}
//	// 此时i==index-1
//	LinkListNode* s = (LinkListNode*)malloc(sizeof(LinkListNode));
//	if (s) {
//		s->data = elem;
//		// 将p原来的后继给新的结点
//		s->next = p->next;
//		p->next = s;
//		return 0;
//	}
//	else {
//		printf("InsertLinkListWithoutHead:分配空间失败！\n");
//		return 1;
//	}
//}