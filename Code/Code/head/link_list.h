#include "head.h"

// ��������
typedef struct LinkListNode {
    element_type data;
    struct LinkListNode *next;
} LinkListNode, *LinkList;

// ��ʼ��
bool InitLinkList(LinkList &list) {
    list->data = DEFAULTELEM;
    list->next = nullptr;
    return true;
}

LinkList InitLinkList() {
    auto list = (LinkList) malloc(sizeof(LinkList));
    list->data = DEFAULTELEM;
    list->next = nullptr;
    return list;
}

// �п�
bool EmptyLinkList(LinkList list) {
    return list->next == nullptr && list->data == DEFAULTELEM;
}

// �ж���������
bool TypeLinkList(LinkList list) {
    if (EmptyLinkList(list)) {
        return NULL;
    } else {
        // �����һ����Ϊ�վʹ�����ͷ�ڵ�
        if (list->data == DEFAULTELEM) {
            return true;
        } else {
            return false;
        }
    }
}

// ��ӡ
bool PrintLinkList(LinkList list) {
    int i = 0;
    if (EmptyLinkList(list)) {
        return true;
    }
    // ��ǰ����ָ��
    LinkListNode *node = list;
    while (!TypeLinkList(list) && node != nullptr && node->data != DEFAULTELEM ||
           TypeLinkList(list) && node != nullptr) {
        printf("��%d��Ԫ��ֵΪ%c\n", i, node->data);
        node = node->next;
        i++;
    }
    return true;
}

// ��ͷ�ڵ����
bool InsertLinkListWithHead(LinkList &list, int index, element_type elem) {
    //if (!TypeLinkList(list)) {
    //	printf("InsertLinkListWithHead:����Ӧ������ͷ�ڵ����ͣ�\n");
    //	return false;
    //}
    if (index < 1) {
        printf("InsertLinkListWithHead:��������ֵ%d��С��\n", index);
        return false;
    }
    // ����һ�����ָ��pָ��ǰɨ�赽�Ľ��
    LinkListNode *p;
    // ����һ������i��ʾ��ǰɨ�赽�Ľ���������
    int i = 0;
    // ������ͷ���ָ��p��Ϊ��0�����
    p = list;
    // ѭ����������ָ�������ŵĵ�����Ľ��
    // �����ǵ�ǰ������һ����Ϊ���������ŵ��������Ľ��һ�����ǿս��
    while (p->next != nullptr && i < index - 1) {
        p = p->next;
        i++;
    }
    // �����ʱiС��index-1����ʾ�����껹û�е����Ӧ������
    if (i < index - 1) {
        printf("InsertLinkListWithHead:��������ֵ����\n");
        return false;
    }
    // ��ʱi==index-1
    auto *s = (LinkListNode *) malloc(sizeof(LinkListNode));
    s->data = elem;
    // ��pԭ���ĺ�̸��µĽ��
    s->next = p->next;
    p->next = s;
    return true;
}

// ��ͷ�ڵ����
bool InsertLinkListWithoutHead(LinkList &list, int index, element_type elem) {
    //if (TypeLinkList(list)) {
    //	printf("InsertLinkListWithoutHead:����Ӧ������ͷ�ڵ����ͣ�\n");
    //	return false;
    //}
    if (index < 0) {
        printf("InsertLinkListWithoutHead:��������ֵ%d��С��\n", index);
        return false;
    }
    auto *s = (LinkListNode *) malloc(sizeof(LinkListNode));
    if (index == 0) {
        s->data = elem;
        // ��s�ĺ����Ϊlistָ��
        s->next = list;
        // ��listָ������Ϊsָ��
        list = s;
        return true;
    }
    // ����һ�����ָ��pָ��ǰɨ�赽�Ľ��
    LinkListNode *p;
    // ����һ������i��ʾ��ǰɨ�赽�Ľ���������
    int i = 0;
    // ������ͷ���ָ��p��Ϊ��0�����
    p = list;
    // ѭ����������ָ�������ŵĵ�����Ľ��
    // �����ǵ�ǰ������һ����Ϊ���������ŵ��������Ľ��һ�����ǿս��
    while (p->next != nullptr && i < index - 1) {
        p = p->next;
        i++;
    }
    // �����ʱiС��index-1����ʾ�����껹û�е����Ӧ������
    if (i < index - 1) {
        printf("InsertLinkListWithoutHead:��������ֵ����\n");
        return false;
    }
    // ��ʱi==index-1
    s->data = elem;
    // ��pԭ���ĺ�̸��µĽ��
    s->next = p->next;
    p->next = s;
    return true;
}

// ���
bool NextInsertLinkList(LinkList &list, element_type *elem, int start, int length) {
    if (!TypeLinkList(list)) {
        for (int i = 0; i < length; i++) {
            bool result = InsertLinkListWithoutHead(list, i, elem[i + start]);
            if (!result) {
                printf("NextInsertLinkList:ѭ������ʧ�ܣ�����ֵΪ%d\n", i + start);
                return false;
            }
        }
    } else {
        for (int i = 0; i < length; i++) {
            bool result = InsertLinkListWithHead(list, i + 1, elem[i + start]);
            if (!result) {
                printf("NextInsertLinkList:ѭ������ʧ�ܣ�����ֵΪ%d\n", i + start);
                return false;
            }
        }
    }
    return true;
}

// ǰ��
bool PriorInsertLinkList(LinkList &list, element_type *elem, int start, int length) {
    if (!TypeLinkList(list)) {
        for (int i = 0; i < length; i++) {
            bool result = InsertLinkListWithoutHead(list, 0, elem[i + start]);
            if (!result) {
                printf("PriorInsertLinkList:ѭ������ʧ�ܣ�����ֵΪ%d\n", i + start);
                return false;
            }
        }
        return true;
    } else {
        for (int i = 0; i < length; i++) {
            bool result = InsertLinkListWithHead(list, 1, elem[i + start]);
            if (!result) {
                printf("PriorInsertLinkList:ѭ������ʧ�ܣ�����ֵΪ%d\n", i + start);
                return false;
            }
        }
        return true;
    }
}

// ɾ��
element_type *DeleteLinkListWithHead(LinkList &list, int index, int length) {
    auto *elem = (element_type *) malloc(length * sizeof(element_type));
    if (index < 1) {
        printf("DeleteLinkListWithHead:ɾ������ֵ%d��С��\n", index);
        return elem;
    }
    if (length < 1) {
        printf("DeleteLinkListWithHead:ɾ������%d��С��\n", length);
    }
    // ����һ�����ָ��startָ��ǰɨ�赽�Ľ�㣬��Ҫɾ����һ��Ԫ�ص�ǰһ��
    LinkListNode *start;
    // ����һ�����ָ��startָ��ǰɨ�赽�Ľ�㣬Ҫɾ������Ԫ��
    LinkListNode *end;
    // ����һ������i��ʾ��ǰɨ�赽�Ľ���������
    int i = 1;
    // ������ͷ����nextָ��start��Ϊ��1�����
    start = list->next;
    // �������û���κ�����
    if (start == nullptr) {
        printf("DeleteLinkListWithHead:����Ϊ�գ�\n");
        return elem;
    }
    // ѭ����������ָ�������ŵĵ�����Ľ��
    // �����ǵ�ǰ������һ����Ϊ���������ŵ��������Ľ��һ�����ǿս��
    while (start->next != nullptr && i < index - 1) {
        start = start->next;
        i++;
    }
    // �����ʱiС��index-1����ʾ�����껹û�е����Ӧ������
    if (i < index - 1) {
        printf("DeleteLinkListWithHead:ɾ������ֵ%d����\n", index);
        return elem;
    }
    // ��ʱi==index-1��start�����end
    end = start;
    for (int i = 0; i < length; i++) {
        elem[i] = end->data;
        end = end->next;
        if (end == nullptr) {
            printf("DeleteLinkListWithHead:ɾ���������ֵ%d���������������%d��\n", index + length - 1, length - 1);
            return elem;
        }
    }
    if (index == 1) {
        list->next = end;
    } else {
        start->next = end->next;
    }
    return elem;
}

element_type *DeleteLinkListWithoutHead(LinkList &list, int index, int length) {
    auto *elem = (element_type *) malloc(length * sizeof(element_type));
    if (index < 0) {
        printf("DeleteLinkListWithoutHead:ɾ������ֵ��С��\n");
        return elem;
    }
    if (length < 1) {
        printf("DeleteLinkListWithoutHead:ɾ������%d��С��\n", length);
    }
    // ����һ�����ָ��startָ��ǰɨ�赽�Ľ�㣬��Ҫɾ����һ��Ԫ�ص�ǰһ��
    LinkListNode *start;
    // ����һ�����ָ��startָ��ǰɨ�赽�Ľ�㣬Ҫɾ������Ԫ��
    LinkListNode *end;
    // i��ʾ��ǰָ����ǵڼ������
    int i = 0;
    // ������ͷ����nextָ��start��Ϊ��0�����
    start = list;
    // �������û���κ�����
    if (EmptyLinkList(list)) {
        printf("DeleteLinkListWithoutHead:����Ϊ�գ�\n");
        return elem;
    }
    // ѭ����������ָ�������ŵĵ�����Ľ��
    // �����ǵ�ǰ������һ����Ϊ���������ŵ��������Ľ��һ�����ǿս��
    while (start->next != nullptr && i < index - 1) {
        start = start->next;
        i++;
    }
    // �����ʱiС��index-1����ʾ�����껹û�е����Ӧ������
    if (i < index - 1) {
        printf("DeleteLinkListWithoutHead:ɾ������ֵ%d����\n", index);
        return elem;
    }
    // ����λ��
    end = start;
    for (int i = 0; i < length; i++) {
        end = end->next;
        elem[i] = end->data;
        if (end->next == nullptr) {
            printf("DeleteLinkListWithoutHead:ɾ���������ֵ%d���������������%d��\n", index + length - 1, length - 1);
            return elem;
        }
    }
    // ���ɾ����һ����0�Ž��
    if (index == 0) {
        start->data = end->next->data;
        start->next = end->next->next;
    }
    start->next = end->next;
    return elem;
}

// ���
int GetLengthLinkList(LinkList list) {
    int length = 0;
    LinkListNode *node = list;
    while (node->next != nullptr) {
        length++;
        node = node->next;
    }
    return length;
}

// ��λ����
element_type GetLinkListElem(LinkList list, int index) {
    if (index >= GetLengthLinkList(list) || index < 0) {
        printf("GetLinkListElem:��������%d����������Χ��\n", index);
        return DEFAULTELEM;
    }
    LinkListNode *node = list;
    for (int i = 0; i < index; i++) {
        node = node->next;
    }
    return node->data;
}

// ��ֵ����
int LocateLinkList(LinkList list, element_type elem) {
    LinkListNode *node = list;
    for (int i = 0; i < GetLengthLinkList(list); i++) {
        if (node->data == elem) {
            return i;
        }
    }
    printf("LocateLinkList:δ�ܶ�λ����Ӧֵ%c��Ԫ�أ�\n", elem);
    return -1;
}

// ����
bool DestroyLinkList(LinkList &list) {
    list->data = DEFAULTELEM;
    delete (list);
    return true;
}

