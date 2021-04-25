#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// 顺序队列
typedef struct {
	// 数组存放队列元素
	element_type data[MAXSIZE];
	// 声明队头指针与队尾指针，其指的是队开始索引与结束索引
	int front, rear;
} SequenceQueue;

// 初始化顺序队列
int InitSequenceQueue(SequenceQueue* queue) {
	// 队首队尾都指向0
	queue->rear = queue->front = 0;
}

// 顺序队列元素入队
int EnterSequenceQueue(SequenceQueue* queue, element_type elem) {
	// 如果队尾指针后一个就是队头指针那就是队满
	if ((queue->rear + 1) % MAXSIZE == queue->front) {
		printf("EnterSequenceQueue:队列已满无法继续进队！");
		return 1;
	}
	// 根据队尾指针插入元素
	queue->data[queue->rear] = elem;
	// 对队尾指针进行取余，从而让队尾指针指向队列前面的空闲空间
	queue->rear = (queue->rear + 1) % MAXSIZE;
	return 0;
}

// 顺序队列元素出队
int ExitSequenceQueue(SequenceQueue* queue, element_type* elem) {
	// 如果队尾指针就是队头指针那就是队空
	if (queue->rear == queue->front) {
		printf("ExitSequenceQueue:队列已空无法继续出队！");
		return 1;
	}
	// 根据队头指针删除元素
	*elem = queue->data[queue->front];
	// 对队头指针进行取余，从而让队头指针指向队列后面的空闲空间
	queue->front = (queue->front + 1) % MAXSIZE;
	return 0;
}

// 获取顺序队列队头元素
int GetSequenceQueueHead(SequenceQueue* queue, element_type* elem) {
	// 如果队尾指针就是队头指针那就是队空
	if (queue->rear == queue->front) {
		printf("GetSequenceQueueHead:队列已空无法获取元素！");
		return 1;
	}
	// 根据队头指针赋值元素
	*elem = queue->data[queue->front];
	return 0;
}

// 判断顺序队是否为空
int IsSequenceQueueEmpty(SequenceQueue queue) {
	if (queue.rear == queue.front) {
		return 1;
	}
	return 0;
}