#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// ����
typedef struct LinkStringNode {
	// ÿ�����洢һλ����
	char data;
	// ÿ�����洢��λ����
	//char data[4];
	struct  LinkStringNode* next;
} LinkStringNode, *LinkString;