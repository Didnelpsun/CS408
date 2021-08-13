#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// ��������
typedef struct LinkListNode {
	element_type data;
	struct LinkListNode* next;
} LinkListNode, *LinkList;

// ����C�����޷�������ֵ�����Ա������һ���м�������
// ��ʼ����ͷ�ڵ㵥����
int InitLinkListWithHead(LinkList list) {
	if (list) {
		list->data = NULL;
		list->next = NULL;
		return 0;
	}
	else {
		printf("InitLinkListWithHead:ָ��Ϊ���޷���ʼ����");
		return 1;
	}
}

// C�����޷�����ʵ�ֳ�ʼ������Ϊ�޷�ʵ�����ô��ݣ����ܸ�ֵ����
// ��ʼ����ͷ�ڵ㵥����
int InitLinkListWithoutHead(LinkList list) {
	list = NULL;
	return 0;
}

// ������ͷ�ڵ㵥����
LinkList CreateLinkListWithHead() {
	LinkList list = (LinkListNode*)malloc(sizeof(LinkListNode));
	if (list) {
		list->data = NULL;
		list->next = NULL;
	}
	else {
		printf("CreateLinkListWithHead:����ռ�ʧ�ܣ�");
	}
	return list;
}

// ������ͷ�ڵ㵥����
LinkList CreateLinkListWithoutHead() {
	return NULL;
}


// �ж���ͷ�ڵ㵥�����Ƿ�Ϊ��
int EmptyLinkListWithHead(LinkList list) {
	if (list->next) {
		return 0;
	}
	else {
		return 1;
	}
}

// �ж���ͷ�ڵ㵥�����Ƿ�Ϊ��
int EmptyLLinkListWithoutHead(LinkList list) {
	if (list) {
		return 0;
	}
	else {
		return 1;
	}
}

// ������ͷ�ڵ㵥����Ԫ��
// 0�Žڵ���ͷ�ڵ�
int InsertLinkListWithHead(LinkList list, int index, element_type elem) {
	if (index < 1) {
		printf("InsertLinkListWithHead:��������ֵ��С��\n");
		return 1;
	}
	// ����һ�����ָ��pָ��ǰɨ�赽�Ľ��
	LinkListNode* p;
	// ����һ������i��ʾ��ǰɨ�赽�Ľ���������
	int i = 0;
	// ������ͷ���ָ��p��Ϊ��0�����
	p = list;
	// ѭ����������ָ�������ŵĵ�����Ľ��
	// �����ǵ�ǰ������һ����Ϊ���������ŵ��������Ľ��һ�����ǿս��
	while (p->next != NULL && i < index - 1) {
		p = p->next;
		i++;
	}
	// �����ʱiС��index-1����ʾ�����껹û�е����Ӧ������
	if (i < index - 1) {
		printf("InsertLinkListWithHead:��������ֵ����\n");
		return 1;
	}
	// ��ʱi==index-1
	LinkListNode* s = (LinkListNode*)malloc(sizeof(LinkListNode));
	if (s) {
		s->data = elem;
		// ��pԭ���ĺ�̸��µĽ��
		s->next = p->next;
		p->next = s;
		return 0;
	}
	else {
		printf("InsertLinkListWithHead:�����ڴ�ʧ�ܣ�\n");
		return 1;
	}
}

// ������ͷ�ڵ㵥����Ԫ��
// C����Ҳ�޷������������
int InsertLinkListWithoutHead(LinkList list, int index, element_type elem) {
	return 1;
}