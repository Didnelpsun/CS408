#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// 静态链表结点
typedef struct StaticLinkNode {
	element_type data;
	// 下一个元素的数组下标
	int next;
} DoubleLinkNode, * DoubleLinkList;