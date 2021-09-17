#include "head.h"

// ˫������
typedef struct DoubleLinkListNode{
    // ����
    element_type data;
    // ͷβָ��
    struct DoubleLinkListNode *prior, *next;
} DoubleLinkListNode, *DoubleLinkList;

// ��ʼ��
DoubleLinkList InitDoubleLinkList(){
    auto list = (DoubleLinkList) malloc(sizeof(DoubleLinkList));
    list->data = DEFAULTELEM;
    list->prior = nullptr;
    list->next = nullptr;
    return list;
}

// ����
bool DestroyDoubleLinkList(DoubleLinkList &list){
    list->data = DEFAULTELEM;
    delete(list->prior);
    delete(list->next);
    list->prior = nullptr;
    list->next = nullptr;
    return true;
}
