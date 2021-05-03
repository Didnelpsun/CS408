#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// 分块查找
// 分块索引表
typedef struct {
	// 块中最大元素
	element_type max;
	// 存储区间的最低索引和最高索引
	int low, high;
} BlockSearchIndex;

