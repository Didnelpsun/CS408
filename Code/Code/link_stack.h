#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// ��ջ���
typedef struct LinkStackNode {
	element_type data;
	struct LinkStackNode* next;
} LinkStackNode, * LinkStack;
