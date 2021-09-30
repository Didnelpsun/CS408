#include "head.h"

// ˳�����
typedef struct {
    // ����
    element_type *data;
    // ��ͷ����β
    int front, rear;
    // �����������
    int max_size;
} SequenceQueue;

// ��ʼ��
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

// �п�
bool EmptySequenceQueue(SequenceQueue queue) {
    return queue.front == queue.rear;
}

// ���������ڼ������
bool FullSequenceQueue(SequenceQueue queue) {
    return queue.rear == queue.max_size;
}

// ��ѭ��������
bool FullCircularSequenceQueue(SequenceQueue queue) {
    return (queue.rear + 1) % queue.max_size == queue.front;
}

// ����
bool EnterSequenceQueue(SequenceQueue &queue, element_type elem) {
    // �ж϶���
    if (FullSequenceQueue(queue)) {
        printf("EnterSequenceQueue:�����޷����ӣ�\n");
        return false;
    }
    queue.data[queue.rear++] = elem;
    return true;
}

// ��ѭ����
bool EnterCircularSequenceQueue(SequenceQueue &queue, element_type elem) {
    // ��ѭ������
    if (FullCircularSequenceQueue(queue)) {
        printf("EnterCircularSequenceQueue:�����޷����ӣ�\n");
        return false;
    }
    queue.data[queue.rear] = elem;
    queue.rear = (queue.rear + 1) % queue.max_size;
    return true;
}

// ����
element_type DepartSequenceQueue(SequenceQueue &queue) {
    // �ж϶ӿ�
    if (EmptySequenceQueue(queue)) {
        printf("DepartSequenceQueue:�ӿ��޷����ӣ�\n");
        return DEFAULTELEM;
    }
    return queue.data[queue.front++];
}

// ��ѭ����
element_type DepartCircularDepartSequence(SequenceQueue &queue) {
    // �ж϶ӿ�
    if (EmptySequenceQueue(queue)) {
        printf("DepartCircularDepartSequence:�ӿ��޷����ӣ�\n");
        return DEFAULTELEM;
    }
    element_type elem = queue.data[queue.front];
    queue.front = (queue.front + 1) % queue.max_size;
    return elem;
}

// ��ȡ�ӳ�
int LengthSequenceQueue(SequenceQueue queue) {
    return (queue.rear - queue.front + queue.max_size) % queue.max_size;
}

// ����ͷ
element_type HeadSequenceQueue(SequenceQueue &queue) {
    // �ж϶ӿ�
    if (EmptySequenceQueue(queue)) {
        printf("HeadSequenceQueue:�ӿ��޷�����ͷ��\n");
        return DEFAULTELEM;
    }
    return queue.data[queue.front];
}