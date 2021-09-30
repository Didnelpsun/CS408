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
bool EmptySequenceQueue(SequenceQueue queue) {
    return queue.front == queue.rear;
}

// 判满（存在假溢出）
bool FullSequenceQueue(SequenceQueue queue) {
    return queue.rear == queue.max_size;
}

// 判循环队列满
bool FullCircularSequenceQueue(SequenceQueue queue) {
    return (queue.rear + 1) % queue.max_size == queue.front;
}

// 进队
bool EnterSequenceQueue(SequenceQueue &queue, element_type elem) {
    // 判断队满
    if (FullSequenceQueue(queue)) {
        printf("EnterSequenceQueue:队满无法进队！\n");
        return false;
    }
    queue.data[queue.rear++] = elem;
    return true;
}

// 进循环队
bool EnterCircularSequenceQueue(SequenceQueue &queue, element_type elem) {
    // 判循环队满
    if (FullCircularSequenceQueue(queue)) {
        printf("EnterCircularSequenceQueue:队满无法进队！\n");
        return false;
    }
    queue.data[queue.rear] = elem;
    queue.rear = (queue.rear + 1) % queue.max_size;
    return true;
}

// 出队
element_type DepartSequenceQueue(SequenceQueue &queue) {
    // 判断队空
    if (EmptySequenceQueue(queue)) {
        printf("DepartSequenceQueue:队空无法出队！\n");
        return DEFAULTELEM;
    }
    return queue.data[queue.front++];
}

// 出循环队
element_type DepartCircularDepartSequence(SequenceQueue &queue) {
    // 判断队空
    if (EmptySequenceQueue(queue)) {
        printf("DepartCircularDepartSequence:队空无法出队！\n");
        return DEFAULTELEM;
    }
    element_type elem = queue.data[queue.front];
    queue.front = (queue.front + 1) % queue.max_size;
    return elem;
}

// 获取队长
int LengthSequenceQueue(SequenceQueue queue) {
    return (queue.rear - queue.front + queue.max_size) % queue.max_size;
}

// 读队头
element_type HeadSequenceQueue(SequenceQueue &queue) {
    // 判断队空
    if (EmptySequenceQueue(queue)) {
        printf("HeadSequenceQueue:队空无法读队头！\n");
        return DEFAULTELEM;
    }
    return queue.data[queue.front];
}