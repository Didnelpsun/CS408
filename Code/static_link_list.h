#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// ��̬������
typedef struct StaticLinkNode {
	element_type data;
	// ��һ��Ԫ�ص������±�
	int next;
} StaticLinkNode;
// ��̬��������
typedef StaticLinkNode StaticLinkList[MAXSIZE];