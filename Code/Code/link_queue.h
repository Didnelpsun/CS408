#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// �����н��
typedef struct LinkQueueNode {
	element_type data;
	struct LinkQueueNode* next;
} LinkQueueNode;

// ������
typedef struct {
	// ���еĶ�ͷָ��Ͷ�βָ��
	LinkQueueNode* front, * rear;
} LinkQueue;

// ��ʼ����ͷ�ڵ�������
int InitLinkQueueWithHead(LinkQueue* queue) {
	// ��ʼ��ʱ��ͷָ��Ͷ�βָ�붼ָ��ͷ���
	queue->front = queue->rear = (LinkQueueNode*)malloc(sizeof(LinkQueueNode));
	if (queue->front) {
		queue->front->next = NULL;
	}
	if (queue->front == NULL || queue->rear == NULL) {
		printf("InitLinkQueueWithHead:��ʼ�������ڴ�ʧ�ܣ�");
		return 1;
	}
	return 0;
}

// ��ʼ������ͷ�ڵ�������
int InitLinkQueueWithoutHead(LinkQueue* queue) {
	// ��ʼ��ʱͷ�����β��㶼ָ��NULL
	queue->front = NULL;
	queue->rear = NULL;
}

// �жϴ�ͷ����������Ƿ�Ϊ��
int IsLinkQueueEmptyWithHead(LinkQueue* queue) {
	// ����ͷָ��Ͷ�βָ��ָ��ͬһ���ط�
	if (queue->front == queue->rear) {
		return 1;
	}
	else {
		return 0;
	}
}

// �жϲ���ͷ����������Ƿ�Ϊ��
int IsLinkQueueEmptyWithoutHead(LinkQueue* queue) {
	// ����ͷָ��Ͷ�βָ����һ��ΪNULL
	if (queue->front == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

// ��ͷ�ڵ����������
int EnterLinkQueueWithHead(LinkQueue* queue, element_type elem) {
	LinkQueueNode* p = (LinkQueueNode*)malloc(sizeof(LinkQueueNode));
	if (p) {
		// ���ݸ�ֵ
		p->data = elem;
		// nextָ��NULL
		p->next = NULL;
		// �½����뵽rear֮��
		queue->rear->next = p;
		// �޸�βָ��
		queue->rear = p;
		return 0;
	}
	else {
		printf("EnterLinkQueueWithHead:�����㽨��ʧ�ܣ�");
		return 1;
	}
}

// ����ͷ�ڵ����������
int EnterLinkQueueWithoutHead(LinkQueue* queue, element_type elem) {
	LinkQueueNode* p = (LinkQueueNode*)malloc(sizeof(LinkQueueNode));
	if (p) {
		// ���ݸ�ֵ
		p->data = elem;
		// nextָ��NULL
		p->next = NULL;
		// ����ǿն��в����һ��Ԫ��
		if (queue->front == NULL) {
			// ����ͷָ����½���Ԫ��
			queue->front = p;
		}
		else {
			// �½����뵽rear֮��
			queue->rear->next = p;
		}
		// �޸�βָ��
		queue->rear = p;
		return 0;
	}
	else {
		printf("EnterLinkQueueWithHead:�����㽨��ʧ�ܣ�");
		return 1;
	}
}

// ��ͷ������ӳ���
int ExitLinkQueueWithHead(LinkQueue* queue, element_type* elem) {
	// ����ǿն�
	if (queue->front == queue->rear) {
		printf("ExitLinkQueueWithHead:�����ѿ��޷����ӣ�");
		return 1;
	}
	// ����һ����������ֵΪ��ͷ��㣨ͷ��㣩����һ�����
	LinkQueueNode* p = queue->front->next;
	// ���ص�һ��Ԫ��
	*elem = p->data;
	// �޸�ͷ����nextָ����ָ��
	// ������һ�����
	queue->front->next = p->next;
	// ��������һ��������
	if (queue->rear == p) {
		queue->rear = queue->front;
	}
	// ��malloc����Ŀռ��ͷ�
	free(p);
	return 0;
}

// ����ͷ������ӳ���
int ExitLinkQueueWithoutHead(LinkQueue* queue, element_type* elem) {
	// ����ǿն�
	if (queue->front == NULL) {
		printf("ExitLinkQueueWithoutHead:�����ѿ��޷����ӣ�");
		return 1;
	}
	// ����һ����������ֵΪ��ͷ���
	LinkQueueNode* p = queue->front;
	// ���ص�һ��Ԫ��
	*elem = p->data;
	// �޸�ͷ����ָ����ָ��
	// ������һ�����
	queue->front = p->next;
	// ��������һ��������
	if (queue->rear == p) {
		// ��ͷ��βָ�붼��ֵΪNULL
		queue->front = NULL;
		queue->rear = NULL;
	}
	// ��malloc����Ŀռ��ͷ�
	free(p);
	return 0;
}

