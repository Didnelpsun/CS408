#include <cstdio>
#include <cstdlib>
#include "head.h"

// ���������
typedef struct LinkListNode {
	element_type data;
	struct LinkListNode* next;
} LinkListNode, *LinkList;

// ����C�����޷�������ֵ�����Ա������һ���м�������
// ��ʼ����ͷ�ڵ㵥����
int InitLinkListWithHead(LinkList &list) {
    list = (LinkListNode*)malloc(sizeof(LinkListNode));
	if (list) {
		list->data = NULL;
		list->next = nullptr;
		return 0;
	}
	else {
		printf("InitLinkListWithHead:����ռ�ʧ�ܣ�");
		return 1;
	}
}

// ��ʼ����ͷ�ڵ㵥����
int InitLinkListWithoutHead(LinkList &list) {
	list = nullptr;
	return 0;
}

// ������ͷ�ڵ㵥����
LinkList CreateLinkListWithHead() {
	auto list = (LinkListNode*)malloc(sizeof(LinkListNode));
	if (list) {
		list->data = NULL;
		list->next = nullptr;
	}
	else {
		printf("CreateLinkListWithHead:����ռ�ʧ�ܣ�");
	}
	return list;
}

// ������ͷ�ڵ㵥����
LinkList CreateLinkListWithoutHead() {
	return nullptr;
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
int EmptyLinkListWithoutHead(LinkList list) {
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
	// ѭ����������ָ�������ŵĵ������Ľ��
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
	if (index < 0) {
		printf("InsertLinkListWithoutHead:��������ֵ��С��\n");
		return 1;
	}
	if (index == 0) {
		LinkListNode* s = (LinkListNode*)malloc(sizeof(LinkListNode));
		if (s) {
			s->data = elem;
			// ��s�ĺ����Ϊlistָ��
			s->next = list;
			// ��listָ������Ϊsָ��
			list = s;
			return 0;
		}
		else {
			printf("InsertLinkListWithoutHead:�����ڴ�ʧ�ܣ�\n");
			return 1;
		}
	}
	// ����һ�����ָ��pָ��ǰɨ�赽�Ľ��
	LinkListNode* p;
	// ����һ������i��ʾ��ǰɨ�赽�Ľ���������
	int i = 0;
	// ������ͷ���ָ��p��Ϊ��0�����
	p = list;
	// ѭ����������ָ�������ŵĵ������Ľ��
	// �����ǵ�ǰ������һ����Ϊ���������ŵ��������Ľ��һ�����ǿս��
	while (p->next != NULL && i < index - 1) {
		p = p->next;
		i++;
	}
	// �����ʱiС��index-1����ʾ�����껹û�е����Ӧ������
	if (i < index - 1) {
		printf("InsertLinkListWithoutHead:��������ֵ����\n");
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
		printf("InsertLinkListWithoutHead:����ռ�ʧ�ܣ�\n");
	}
}