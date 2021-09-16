#include <cstdio>
#include <cstdlib>
#include "head.h"

// 顺序队列
typedef struct {
    // 数据
    element_type* data;
    // 队头指针和队尾指针
    int front, rear;
};