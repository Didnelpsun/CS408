#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// 链队列结点
typedef struct LinkQueueNode {
	element_type data;
	struct LinkQueueNode* next;
} LinkQueueNode;

// 链队列
typedef struct {
	// 队列的队头指针和队尾指针
	LinkQueueNode* front, * rear;
} LinkQueue;

// 初始化带头节点链队列
int InitLinkQueueWithHead(LinkQueue* queue) {
	// 初始化时队头指针和队尾指针都指向头结点
	queue->front = queue->rear = (LinkQueueNode*)malloc(sizeof(LinkQueueNode));
	if (queue->front) {
		queue->front->next = NULL;
	}
	if (queue->front == NULL || queue->rear == NULL) {
		printf("InitLinkQueueWithHead:初始化分配内存失败！");
		return 1;
	}
	return 0;
}

// 初始化不带头节点链队列
int InitLinkQueueWithoutHead(LinkQueue* queue) {
	// 初始化时头结点与尾结点都指向NULL
	queue->front = NULL;
	queue->rear = NULL;
}

// 判断带头结点链队列是否为空
int IsLinkQueueEmptyWithHead(LinkQueue* queue) {
	// 当队头指针和队尾指针指向同一个地方
	if (queue->front == queue->rear) {
		return 1;
	}
	else {
		return 0;
	}
}

// 判断不带头结点链队列是否为空
int IsLinkQueueEmptyWithoutHead(LinkQueue* queue) {
	// 当队头指针和队尾指针有一个为NULL
	if (queue->front == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

// 带头节点链队列入队
int EnterLinkQueueWithHead(LinkQueue* queue, element_type elem) {
	LinkQueueNode* p = (LinkQueueNode*)malloc(sizeof(LinkQueueNode));
	if (p) {
		// 数据赋值
		p->data = elem;
		// next指向NULL
		p->next = NULL;
		// 新结点插入到rear之后
		queue->rear->next = p;
		// 修改尾指针
		queue->rear = p;
		return 0;
	}
	else {
		printf("EnterLinkQueueWithHead:插入结点建立失败！");
		return 1;
	}
}

// 不带头节点链队列入队
int EnterLinkQueueWithoutHead(LinkQueue* queue, element_type elem) {
	LinkQueueNode* p = (LinkQueueNode*)malloc(sizeof(LinkQueueNode));
	if (p) {
		// 数据赋值
		p->data = elem;
		// next指向NULL
		p->next = NULL;
		// 如果是空队列插入第一个元素
		if (queue->front == NULL) {
			// 将队头指针给新建的元素
			queue->front = p;
		}
		else {
			// 新结点插入到rear之后
			queue->rear->next = p;
		}
		// 修改尾指针
		queue->rear = p;
		return 0;
	}
	else {
		printf("EnterLinkQueueWithHead:插入结点建立失败！");
		return 1;
	}
}

// 带头结点链队出队
int ExitLinkQueueWithHead(LinkQueue* queue, element_type* elem) {
	// 如果是空队
	if (queue->front == queue->rear) {
		printf("ExitLinkQueueWithHead:队列已空无法出队！");
		return 1;
	}
	// 建立一个结点变量赋值为队头结点（头结点）的下一个结点
	LinkQueueNode* p = queue->front->next;
	// 返回第一个元素
	*elem = p->data;
	// 修改头结点的next指针所指向
	// 即后移一个结点
	queue->front->next = p->next;
	// 如果是最后一个结点出队
	if (queue->rear == p) {
		queue->rear = queue->front;
	}
	// 对malloc申请的空间释放
	free(p);
	return 0;
}

// 不带头结点链队出队
int ExitLinkQueueWithoutHead(LinkQueue* queue, element_type* elem) {
	// 如果是空队
	if (queue->front == NULL) {
		printf("ExitLinkQueueWithoutHead:队列已空无法出队！");
		return 1;
	}
	// 建立一个结点变量赋值为队头结点
	LinkQueueNode* p = queue->front;
	// 返回第一个元素
	*elem = p->data;
	// 修改头结点的指针所指向
	// 即后移一个结点
	queue->front = p->next;
	// 如果是最后一个结点出队
	if (queue->rear == p) {
		// 队头队尾指针都赋值为NULL
		queue->front = NULL;
		queue->rear = NULL;
	}
	// 对malloc申请的空间释放
	free(p);
	return 0;
}

