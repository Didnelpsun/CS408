#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// Á´Õ»½áµã
typedef struct LinkStackNode {
	element_type data;
	struct LinkStackNode* next;
} LinkStackNode, * LinkStack;
