#include "head.h"

// 静态链表
typedef struct {
    // 数据元素
    element_type data;
    // 下标
    int next;
} StaticLinkList[MAXSIZE];