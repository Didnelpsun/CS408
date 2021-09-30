#include "head.h"

// 链队结点
typedef struct LinkQueueNode {
    // 数据
    element_type data;
    // 指针
    struct LinkQueueNode *next;
} LinkQueueNode;

// 链队
typedef struct {
    // 队头指针和队尾指针
    LinkQueueNode *front, *rear;
} LinkQueue;

// 初始化
bool InitLinkQueue(LinkQueue &queue){
    // 建立头节点
    queue.front = queue.rear = (LinkQueueNode*) malloc(sizeof(LinkQueueNode));
    // 初始为空
    queue.front->next = nullptr;
    queue.front->data = DEFAULTELEM;
    return true;
}

LinkQueue InitLinkQueue(){
    auto* queue = (LinkQueue*) malloc(sizeof(LinkQueue));
    queue->front = queue->rear = (LinkQueueNode*) malloc(sizeof(LinkQueueNode));
    // 初始为空
    queue->front->next = nullptr;
    queue->front->data = DEFAULTELEM;
    return (LinkQueue &) queue;
}

// 判空
bool EmptyLinkQueue(LinkQueue queue){
    return queue.front==queue.rear;
}

// 入队
bool EnterLinkQueue(LinkQueue &queue, element_type elem){
    // 创建新结点
    auto *node = (LinkQueueNode *) malloc(sizeof(LinkQueueNode));
    node->data = elem;
    node->next = nullptr;
    // 把最后一个元素的next连接到node
    queue.rear->next = node;
    // 移动尾指针
    queue.rear = node;
    return true;
}

// 出队
element_type DepartLinkQueue(LinkQueue &queue){
    if(EmptyLinkQueue(queue)){
        printf("DepartLinkQueue:The queue is empty!");
        return false;
    }
    // 获取对首元素下一个元素的数据
    element_type elem = queue.front->next->data;
    // 后移移位
    queue.front->next=queue.front->next->next;
    // 若队列空
    return true;
}