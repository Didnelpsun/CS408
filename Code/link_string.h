#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// 链串
typedef struct LinkStringNode {
	// 每个结点存储一位数据
	char data;
	// 每个结点存储四位数据
	//char data[4];
	struct  LinkStringNode* next;
} LinkStringNode, *LinkString;