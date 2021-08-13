#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// ˳�����
typedef struct {
	// �����Ŷ���Ԫ��
	element_type data[MAXSIZE];
	// ������ͷָ�����βָ�룬��ָ���Ƕӿ�ʼ�������������
	int front, rear;
} SequenceQueue;

// ��ʼ��˳�����
int InitSequenceQueue(SequenceQueue* queue) {
	// ���׶�β��ָ��0
	queue->rear = queue->front = 0;
}

// ˳�����Ԫ�����
int EnterSequenceQueue(SequenceQueue* queue, element_type elem) {
	// �����βָ���һ�����Ƕ�ͷָ���Ǿ��Ƕ���
	if ((queue->rear + 1) % MAXSIZE == queue->front) {
		printf("EnterSequenceQueue:���������޷��������ӣ�");
		return 1;
	}
	// ���ݶ�βָ�����Ԫ��
	queue->data[queue->rear] = elem;
	// �Զ�βָ�����ȡ�࣬�Ӷ��ö�βָ��ָ�����ǰ��Ŀ��пռ�
	queue->rear = (queue->rear + 1) % MAXSIZE;
	return 0;
}

// ˳�����Ԫ�س���
int ExitSequenceQueue(SequenceQueue* queue, element_type* elem) {
	// �����βָ����Ƕ�ͷָ���Ǿ��Ƕӿ�
	if (queue->rear == queue->front) {
		printf("ExitSequenceQueue:�����ѿ��޷��������ӣ�");
		return 1;
	}
	// ���ݶ�ͷָ��ɾ��Ԫ��
	*elem = queue->data[queue->front];
	// �Զ�ͷָ�����ȡ�࣬�Ӷ��ö�ͷָ��ָ����к���Ŀ��пռ�
	queue->front = (queue->front + 1) % MAXSIZE;
	return 0;
}

// ��ȡ˳����ж�ͷԪ��
int GetSequenceQueueHead(SequenceQueue* queue, element_type* elem) {
	// �����βָ����Ƕ�ͷָ���Ǿ��Ƕӿ�
	if (queue->rear == queue->front) {
		printf("GetSequenceQueueHead:�����ѿ��޷���ȡԪ�أ�");
		return 1;
	}
	// ���ݶ�ͷָ�븳ֵԪ��
	*elem = queue->data[queue->front];
	return 0;
}

// �ж�˳����Ƿ�Ϊ��
int IsSequenceQueueEmpty(SequenceQueue queue) {
	if (queue.rear == queue.front) {
		return 1;
	}
	return 0;
}