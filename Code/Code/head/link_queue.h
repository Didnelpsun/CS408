#include "head.h"

// ���ӽ��
typedef struct LinkQueueNode {
    // ����
    element_type data;
    // ָ��
    struct LinkQueueNode *next;
} LinkQueueNode;

// ����
typedef struct {
    // ��ͷָ��Ͷ�βָ��
    LinkQueueNode *front, *rear;
} LinkQueue;

// ��ʼ��
bool InitLinkQueue(LinkQueue &queue){
    // ����ͷ�ڵ�
    queue.front = queue.rear = (LinkQueueNode*) malloc(sizeof(LinkQueueNode));
    // ��ʼΪ��
    queue.front->next = nullptr;
    queue.front->data = DEFAULTELEM;
    return true;
}

LinkQueue InitLinkQueue(){
    auto* queue = (LinkQueue*) malloc(sizeof(LinkQueue));
    queue->front = queue->rear = (LinkQueueNode*) malloc(sizeof(LinkQueueNode));
    // ��ʼΪ��
    queue->front->next = nullptr;
    queue->front->data = DEFAULTELEM;
    return (LinkQueue &) queue;
}

// �п�
bool EmptyLinkQueue(LinkQueue queue){
    return queue.front==queue.rear;
}

// ���
bool EnterLinkQueue(LinkQueue &queue, element_type elem){
    // �����½��
    auto *node = (LinkQueueNode *) malloc(sizeof(LinkQueueNode));
    node->data = elem;
    node->next = nullptr;
    // �����һ��Ԫ�ص�next���ӵ�node
    queue.rear->next = node;
    // �ƶ�βָ��
    queue.rear = node;
    return true;
}

// ����
element_type DepartLinkQueue(LinkQueue &queue){
    if(EmptyLinkQueue(queue)){
        printf("DepartLinkQueue:The queue is empty!");
        return false;
    }
    // ��ȡ����Ԫ����һ��Ԫ�ص�����
    element_type elem = queue.front->next->data;
    // ������λ
    queue.front->next=queue.front->next->next;
    // �����п�
    return true;
}