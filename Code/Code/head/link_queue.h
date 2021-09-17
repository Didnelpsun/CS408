#include "head.h"

// 链队结点
typedef struct LinkQueueNode {
    // 数据
    element_type* data;
    // 指针
    struct LinkQueueNode *next;
} LinkQueueNode;

// 链队
typedef struct {
    // 队头指针和队尾指针
    LinkQueueNode *front, *rear;
} LinkQueue;