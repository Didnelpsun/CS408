#include "head.h"

// 双链表结点
typedef struct DoubleLinkListNode{
    // 数据
    element_type data;
    // 头尾指针
    struct DoubleLinkListNode *prior, *next;
} DoubleLinkListNode, *DoubleLinkList;

// 初始化
DoubleLinkList InitDoubleLinkList(){
    auto list = (DoubleLinkList) malloc(sizeof(DoubleLinkList));
    list->data = DEFAULTELEM;
    list->prior = nullptr;
    list->next = nullptr;
    return list;
}

// 销毁
bool DestroyDoubleLinkList(DoubleLinkList &list){
    list->data = DEFAULTELEM;
    delete(list->prior);
    delete(list->next);
    list->prior = nullptr;
    list->next = nullptr;
    return true;
}
