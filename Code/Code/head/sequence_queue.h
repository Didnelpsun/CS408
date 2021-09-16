#include <cstdio>
#include <cstdlib>
#include "head.h"

// 顺序队列
typedef struct {
    // 数据
    element_type *data;
    // 队头、队尾
    int front, rear;
    // 队列最大容量
    int max_size;
} SequenceQueue;

// 初始化
bool InitSequenceQueue(SequenceQueue &queue) {
    queue.data = (element_type *) malloc(sizeof(element_type) * MAXSIZE);
    queue.front = 0;
    queue.rear = 0;
    queue.max_size = MAXSIZE;
    return true;
}

bool InitSequenceQueue(SequenceQueue &queue, int max_size) {
    queue.data = (element_type *) malloc(sizeof(element_type) * max_size);
    queue.front = 0;
    queue.rear = 0;
    queue.max_size = max_size;
    return true;
}

SequenceQueue InitSequenceQueue() {
    auto *queue = (SequenceQueue *) malloc(sizeof(SequenceQueue));
    queue->data = (element_type *) malloc(sizeof(element_type) * MAXSIZE);
    queue->front = 0;
    queue->rear = 0;
    queue->max_size = MAXSIZE;
    return (SequenceQueue &) queue;
}

SequenceQueue InitSequenceQueue(int max_size) {
    auto *queue = (SequenceQueue *) malloc(sizeof(SequenceQueue));
    queue->data = (element_type *) malloc(sizeof(element_type) * max_size);
    queue->front = 0;
    queue->rear = 0;
    queue->max_size = max_size;
    return (SequenceQueue &) queue;
}

// 判空
bool EmptySequenceQueue(SequenceQueue queue){
    return queue.front == queue.rear;
}

// 判满（存在假溢出）
bool FullSequenceQueue(SequenceQueue queue){
    return queue.rear == queue.max_size;
}

// 进队