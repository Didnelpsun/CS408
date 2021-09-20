#include "head.h"

// 单链表结点
typedef struct LinkListNode {
    element_type data;
    struct LinkListNode *next;
} LinkListNode, *LinkList;

// 初始化
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

// 判空
bool EmptyLinkList(LinkList list) {
    return list->next == nullptr && list->data == DEFAULTELEM;
}

// 判断链表类型
bool TypeLinkList(LinkList list) {
    if (EmptyLinkList(list)) {
        return NULL;
    } else {
        // 如果第一数据为空就代表有头节点
        if (list->data == DEFAULTELEM) {
            return true;
        } else {
            return false;
        }
    }
}

// 打印
bool PrintLinkList(LinkList list) {
    int i = 0;
    if (EmptyLinkList(list)) {
        return true;
    }
    // 当前遍历指针
    LinkListNode *node = list;
    while (!TypeLinkList(list) && node != nullptr && node->data != DEFAULTELEM ||
           TypeLinkList(list) && node != nullptr) {
        printf("第%d个元素值为%c\n", i, node->data);
        node = node->next;
        i++;
    }
    return true;
}

// 有头节点插入
bool InsertLinkListWithHead(LinkList &list, int index, element_type elem) {
    //if (!TypeLinkList(list)) {
    //	printf("InsertLinkListWithHead:链表不应该是无头节点类型！\n");
    //	return false;
    //}
    if (index < 1) {
        printf("InsertLinkListWithHead:插入索引值%d过小！\n", index);
        return false;
    }
    // 定义一个结点指针p指向当前扫描到的结点
    LinkListNode *p;
    // 定义一个变量i表示当前扫描到的结点的索引号
    int i = 0;
    // 将链表头结点指向p，为第0个结点
    p = list;
    // 循环遍历到达指定索引号的单链表的结点
    // 条件是当前结点的下一个不为空且索引号到达，所到达的结点一定不是空结点
    while (p->next != nullptr && i < index - 1) {
        p = p->next;
        i++;
    }
    // 如果此时i小于index-1，表示遍历完还没有到达对应的索引
    if (i < index - 1) {
        printf("InsertLinkListWithHead:插入索引值过大！\n");
        return false;
    }
    // 此时i==index-1
    auto *s = (LinkListNode *) malloc(sizeof(LinkListNode));
    s->data = elem;
    // 将p原来的后继给新的结点
    s->next = p->next;
    p->next = s;
    return true;
}

// 无头节点插入
bool InsertLinkListWithoutHead(LinkList &list, int index, element_type elem) {
    //if (TypeLinkList(list)) {
    //	printf("InsertLinkListWithoutHead:链表不应该是有头节点类型！\n");
    //	return false;
    //}
    if (index < 0) {
        printf("InsertLinkListWithoutHead:插入索引值%d过小！\n", index);
        return false;
    }
    auto *s = (LinkListNode *) malloc(sizeof(LinkListNode));
    if (index == 0) {
        s->data = elem;
        // 将s的后继设为list指针
        s->next = list;
        // 将list指针设置为s指针
        list = s;
        return true;
    }
    // 定义一个结点指针p指向当前扫描到的结点
    LinkListNode *p;
    // 定义一个变量i表示当前扫描到的结点的索引号
    int i = 0;
    // 将链表头结点指向p，为第0个结点
    p = list;
    // 循环遍历到达指定索引号的单链表的结点
    // 条件是当前结点的下一个不为空且索引号到达，所到达的结点一定不是空结点
    while (p->next != nullptr && i < index - 1) {
        p = p->next;
        i++;
    }
    // 如果此时i小于index-1，表示遍历完还没有到达对应的索引
    if (i < index - 1) {
        printf("InsertLinkListWithoutHead:插入索引值过大！\n");
        return false;
    }
    // 此时i==index-1
    s->data = elem;
    // 将p原来的后继给新的结点
    s->next = p->next;
    p->next = s;
    return true;
}

// 后插
bool NextInsertLinkList(LinkList &list, element_type *elem, int start, int length) {
    if (!TypeLinkList(list)) {
        for (int i = 0; i < length; i++) {
            bool result = InsertLinkListWithoutHead(list, i, elem[i + start]);
            if (!result) {
                printf("NextInsertLinkList:循环插入失败！索引值为%d\n", i + start);
                return false;
            }
        }
    } else {
        for (int i = 0; i < length; i++) {
            bool result = InsertLinkListWithHead(list, i + 1, elem[i + start]);
            if (!result) {
                printf("NextInsertLinkList:循环插入失败！索引值为%d\n", i + start);
                return false;
            }
        }
    }
    return true;
}

// 前插
bool PriorInsertLinkList(LinkList &list, element_type *elem, int start, int length) {
    if (!TypeLinkList(list)) {
        for (int i = 0; i < length; i++) {
            bool result = InsertLinkListWithoutHead(list, 0, elem[i + start]);
            if (!result) {
                printf("PriorInsertLinkList:循环插入失败！索引值为%d\n", i + start);
                return false;
            }
        }
        return true;
    } else {
        for (int i = 0; i < length; i++) {
            bool result = InsertLinkListWithHead(list, 1, elem[i + start]);
            if (!result) {
                printf("PriorInsertLinkList:循环插入失败！索引值为%d\n", i + start);
                return false;
            }
        }
        return true;
    }
}

// 删除
element_type *DeleteLinkListWithHead(LinkList &list, int index, int length) {
    auto *elem = (element_type *) malloc(length * sizeof(element_type));
    if (index < 1) {
        printf("DeleteLinkListWithHead:删除索引值%d过小！\n", index);
        return elem;
    }
    if (length < 1) {
        printf("DeleteLinkListWithHead:删除长度%d过小！\n", length);
    }
    // 定义一个结点指针start指向当前扫描到的结点，即要删除第一的元素的前一个
    LinkListNode *start;
    // 定义一个结点指针start指向当前扫描到的结点，要删除最后的元素
    LinkListNode *end;
    // 定义一个变量i表示当前扫描到的结点的索引号
    int i = 1;
    // 将链表头结点的next指向start，为第1个结点
    start = list->next;
    // 如果链表没有任何数据
    if (start == nullptr) {
        printf("DeleteLinkListWithHead:链表为空！\n");
        return elem;
    }
    // 循环遍历到达指定索引号的单链表的结点
    // 条件是当前结点的下一个不为空且索引号到达，所到达的结点一定不是空结点
    while (start->next != nullptr && i < index - 1) {
        start = start->next;
        i++;
    }
    // 如果此时i小于index-1，表示遍历完还没有到达对应的索引
    if (i < index - 1) {
        printf("DeleteLinkListWithHead:删除索引值%d过大！\n", index);
        return elem;
    }
    // 此时i==index-1，start到达，求end
    end = start;
    for (int i = 0; i < length; i++) {
        elem[i] = end->data;
        end = end->next;
        if (end == nullptr) {
            printf("DeleteLinkListWithHead:删除索引最大值%d大于链表最大索引%d！\n", index + length - 1, length - 1);
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
        printf("DeleteLinkListWithoutHead:删除索引值过小！\n");
        return elem;
    }
    if (length < 1) {
        printf("DeleteLinkListWithoutHead:删除长度%d过小！\n", length);
    }
    // 定义一个结点指针start指向当前扫描到的结点，即要删除第一的元素的前一个
    LinkListNode *start;
    // 定义一个结点指针start指向当前扫描到的结点，要删除最后的元素
    LinkListNode *end;
    // i表示当前指向的是第几个结点
    int i = 0;
    // 将链表头结点的next指向start，为第0个结点
    start = list;
    // 如果链表没有任何数据
    if (EmptyLinkList(list)) {
        printf("DeleteLinkListWithoutHead:链表为空！\n");
        return elem;
    }
    // 循环遍历到达指定索引号的单链表的结点
    // 条件是当前结点的下一个不为空且索引号到达，所到达的结点一定不是空结点
    while (start->next != nullptr && i < index - 1) {
        start = start->next;
        i++;
    }
    // 如果此时i小于index-1，表示遍历完还没有到达对应的索引
    if (i < index - 1) {
        printf("DeleteLinkListWithoutHead:删除索引值%d过大！\n", index);
        return elem;
    }
    // 到达位置
    end = start;
    for (int i = 0; i < length; i++) {
        end = end->next;
        elem[i] = end->data;
        if (end->next == nullptr) {
            printf("DeleteLinkListWithoutHead:删除索引最大值%d大于链表最大索引%d！\n", index + length - 1, length - 1);
            return elem;
        }
    }
    // 如果删除第一个第0号结点
    if (index == 0) {
        start->data = end->next->data;
        start->next = end->next->next;
    }
    start->next = end->next;
    return elem;
}

// 求表长
int GetLengthLinkList(LinkList list) {
    int length = 0;
    LinkListNode *node = list;
    while (node->next != nullptr) {
        length++;
        node = node->next;
    }
    return length;
}

// 按位查找
element_type GetLinkListElem(LinkList list, int index) {
    if (index >= GetLengthLinkList(list) || index < 0) {
        printf("GetLinkListElem:查找索引%d超过索引范围！\n", index);
        return DEFAULTELEM;
    }
    LinkListNode *node = list;
    for (int i = 0; i < index; i++) {
        node = node->next;
    }
    return node->data;
}

// 按值查找
int LocateLinkList(LinkList list, element_type elem) {
    LinkListNode *node = list;
    for (int i = 0; i < GetLengthLinkList(list); i++) {
        if (node->data == elem) {
            return i;
        }
    }
    printf("LocateLinkList:未能定位到对应值%c的元素！\n", elem);
    return -1;
}

// 销毁
bool DestroyLinkList(LinkList &list) {
    list->data = DEFAULTELEM;
    delete (list);
    return true;
}

