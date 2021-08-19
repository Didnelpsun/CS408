#include <cstdio>
#include <cstdlib>
#include "head.h"

// ��������
class LinkListNode {
public:
    // ����
	element_type data;
    // ָ��
	LinkListNode* next;
	// ���캯��
	LinkListNode();
	explicit LinkListNode(element_type data);
};

class LinkList{
public:
    // ָ��
    LinkListNode* next;
    // ������
    int length;
    // ���캯��
    LinkList();
    // �п�
    bool Empty();
};

class LinkListWithHead: public LinkList{
public:
    // ���캯��
    LinkListWithHead();
};

class LinkListWithoutHead: public LinkList{
public:
    // ����
    element_type data;
    // ���캯��
    LinkListWithoutHead();
};

LinkListNode::LinkListNode() {
    this->data = NULL;
    this->next = nullptr;
}

LinkListNode::LinkListNode(element_type data) {
    this->data = data;
	this->next = nullptr;
}

LinkList::LinkList() {
    this->next= nullptr;
    this->length =0;
}

LinkListWithHead::LinkListWithHead() = default;

LinkListWithoutHead::LinkListWithoutHead() {
    this->data = NULL;
}

bool LinkList::Empty() {
    if(this->length==0){
        return true;
    } else {
        return false;
    }
}


//// ������ͷ�ڵ㵥����Ԫ��
//// 0�Žڵ���ͷ�ڵ�
//int InsertLinkListWithHead(LinkList list, int index, element_type elem) {
//	if (index < 1) {
//		printf("InsertLinkListWithHead:��������ֵ��С��\n");
//		return 1;
//	}
//	// ����һ�����ָ��pָ��ǰɨ�赽�Ľ��
//	LinkListNode* p;
//	// ����һ������i��ʾ��ǰɨ�赽�Ľ���������
//	int i = 0;
//	// ������ͷ���ָ��p��Ϊ��0�����
//	p = list;
//	// ѭ����������ָ�������ŵĵ�����Ľ��
//	// �����ǵ�ǰ������һ����Ϊ���������ŵ��������Ľ��һ�����ǿս��
//	while (p->next != NULL && i < index - 1) {
//		p = p->next;
//		i++;
//	}
//	// �����ʱiС��index-1����ʾ�����껹û�е����Ӧ������
//	if (i < index - 1) {
//		printf("InsertLinkListWithHead:��������ֵ����\n");
//		return 1;
//	}
//	// ��ʱi==index-1
//	LinkListNode* s = (LinkListNode*)malloc(sizeof(LinkListNode));
//	if (s) {
//		s->data = elem;
//		// ��pԭ���ĺ�̸��µĽ��
//		s->next = p->next;
//		p->next = s;
//		return 0;
//	}
//	else {
//		printf("InsertLinkListWithHead:�����ڴ�ʧ�ܣ�\n");
//		return 1;
//	}
//}
//
//// ������ͷ�ڵ㵥����Ԫ��
//// C����Ҳ�޷������������
//int InsertLinkListWithoutHead(LinkList list, int index, element_type elem) {
//	if (index < 0) {
//		printf("InsertLinkListWithoutHead:��������ֵ��С��\n");
//		return 1;
//	}
//	if (index == 0) {
//		LinkListNode* s = (LinkListNode*)malloc(sizeof(LinkListNode));
//		if (s) {
//			s->data = elem;
//			// ��s�ĺ����Ϊlistָ��
//			s->next = list;
//			// ��listָ������Ϊsָ��
//			list = s;
//			return 0;
//		}
//		else {
//			printf("InsertLinkListWithoutHead:�����ڴ�ʧ�ܣ�\n");
//			return 1;
//		}
//	}
//	// ����һ�����ָ��pָ��ǰɨ�赽�Ľ��
//	LinkListNode* p;
//	// ����һ������i��ʾ��ǰɨ�赽�Ľ���������
//	int i = 0;
//	// ������ͷ���ָ��p��Ϊ��0�����
//	p = list;
//	// ѭ����������ָ�������ŵĵ�����Ľ��
//	// �����ǵ�ǰ������һ����Ϊ���������ŵ��������Ľ��һ�����ǿս��
//	while (p->next != NULL && i < index - 1) {
//		p = p->next;
//		i++;
//	}
//	// �����ʱiС��index-1����ʾ�����껹û�е����Ӧ������
//	if (i < index - 1) {
//		printf("InsertLinkListWithoutHead:��������ֵ����\n");
//		return 1;
//	}
//	// ��ʱi==index-1
//	LinkListNode* s = (LinkListNode*)malloc(sizeof(LinkListNode));
//	if (s) {
//		s->data = elem;
//		// ��pԭ���ĺ�̸��µĽ��
//		s->next = p->next;
//		p->next = s;
//		return 0;
//	}
//	else {
//		printf("InsertLinkListWithoutHead:����ռ�ʧ�ܣ�\n");
//		return 1;
//	}
//}