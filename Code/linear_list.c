#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// 静态顺序表
typedef struct {
    element_type data[MAXSIZE];
    int length;
} StaticSequenceList;

// 动态顺序表
typedef struct {
    element_type *data;
    // 已分配的最大容量
    int max_size;
    int length;
} DynamicSequenceList;

// 初始化静态顺序表
void InitStaticSequenceList(StaticSequenceList* list) {
    // 初初始化静态顺序表长度为0
    list->length = 0;
}

// 初始化动态顺序表
void InitDynamicSequenceList(DynamicSequenceList* list) {
    // 初初始化动态顺序表长度为0
    list->length = 0;
    // 申请一片连续的存储空间
    list->data = (element_type*)malloc(MAXSIZE * sizeof(element_type));
    list->max_size = MAXSIZE;
}

// 分配其他地址增长动态顺序表的数据空间长度
void OtherIncreaseDynamicSequenceList(DynamicSequenceList* list, int len) {
    // 申请一片连续的存储空间
    int new_length = list->max_size + len;
    element_type* space = (element_type*)realloc(list->data, new_length);
    if (space != NULL) {
        list->data = space;
        list->max_size += len;
    }
    else {
        list->max_size = 0;
        list->length = 0;
        printf("分配空间失败！");
    }
}

// 重新分配地址增长动态顺序表的数据空间长度
void ReIncreaseDynamicSequenceList(DynamicSequenceList* list, int len) {
    // 申请一片连续的存储空间
    int new_length = list->max_size + len;
    element_type* space = (element_type*)realloc(list->data, new_length);
    if (space != NULL) {
        list->data = space;
        list->max_size += len;
    }
    else {
        list->max_size = 0;
        list->length = 0;
        printf("分配空间失败！");
    }
}

int main()
{
    /*StaticSequenceList static_list;
    InitStaticSequenceList(&static_list);*/
    DynamicSequenceList dynamic_list;
    InitDynamicSequenceList(&dynamic_list);
    printf("%d\n", dynamic_list.max_size);
    ReIncreaseDynamicSequenceList(&dynamic_list, 25);
    printf("%d\n", dynamic_list.max_size);
    return 0;
}