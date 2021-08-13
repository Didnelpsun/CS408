#include <stdio.h>
#include <stdlib.h>
#include "head.h"

#pragma warning(disable:6385)
#pragma warning(disable:6386)

// 静态顺序表
typedef struct {
    element_type data[MAXSIZE];
    // 长度
    int length;
} StaticSequenceList;

// 动态顺序表
typedef struct {
    // 给一个指针来分配动态数组
    element_type *data;
    // 已分配的最大容量
    int max_size;
    // 长度
    int length;
} DynamicSequenceList;

// 初始化静态顺序表
int InitStaticSequenceList(StaticSequenceList* list) {
    if (list) {
        // 初初始化静态顺序表长度为0
        list->length = 0;
        return 0;
    }
    else {
        printf("InitStaticSequenceList:指针指向为NULL！\n");
        return 1;
    }
}

// 初始化动态顺序表
int InitDynamicSequenceList(DynamicSequenceList* list) {
    if (list) {
        // 初初始化动态顺序表长度为0
        list->length = 0;
        list->max_size = 0;
        // 申请一片连续的存储空间
        element_type* space = (element_type*)malloc(MAXSIZE * sizeof(element_type));
        if (space) {
            list->data = space;
            list->max_size = MAXSIZE;
            return 0;
        }
        else {
            printf("InitDynamicSequenceList:分配空间失败！\n");
            return 1;
        }
    }
    else {
        printf("InitDynamicSequenceList:指针指向为NULL！\n");
        return 1;
    }
}

// 打印静态顺序表
int PrintfStaticSequenceList(StaticSequenceList list) {
    for (int i = 0; i < list.length; i++) {
        printf("第%d个元素值为%c\n", i + 1, list.data[i]);
    }
    return 0;
}

// 打印动态顺序表
int PrintfDynamicSequenceList(DynamicSequenceList list) {
    for (int i = 0; i < list.length; i++) {
        printf("第%d个元素值为%c\n", i + 1, list.data[i]);
    }
    return 0;
}

// 分配其他地址增长动态顺序表的数据空间长度
int OtherIncreaseDynamicSequenceList(DynamicSequenceList* list, int len) {
    if (len <= 0) {
        printf("OtherIncreaseDynamicSequenceList:申请空间应该大于0！\n");
        return 1;
    }
    // 申请一片连续的存储空间
    int new_length = list->max_size + len;
    element_type* space = (element_type*)malloc(new_length * sizeof(element_type));
    if (space) {
        // 建立中间变量
        list->data = space;
        element_type* temp = list->data;
        for (int i = 0; i < list->length; i++) {
            list->data[i] = temp[i];
        }
        list->max_size = new_length;
        free(temp);
        return 0;
    }
    else {
        printf("OtherIncreaseDynamicSequenceList:重新分配空间失败！\n");
        return 1;
    }
}

// 重新分配地址增长动态顺序表的数据空间长度
int ReIncreaseDynamicSequenceList(DynamicSequenceList* list, int len) {
    if (len <= 0) {
        printf("ReIncreaseDynamicSequenceList:申请空间应该大于0！\n");
        return 1;
    }
    // 申请一片连续的存储空间
    int new_length = list->max_size + len;
    element_type* space = (element_type*)realloc(list->data, new_length * sizeof(element_type));
    if (space) {
        list->data = space;
        list->max_size += len;
        return 0;
    }
    else {
        list->max_size = 0;
        list->length = 0;
        printf("ReIncreaseDynamicSequenceList:分配其他地址空间失败！\n");
        return 1;
    }
}

// 插入静态顺序表
int InsertStaticSequenceList(StaticSequenceList* list, int index, element_type elem) {
    // 当静态顺序表已经满了就不能插入任何元素
    if (list->length >= MAXSIZE) {
        printf("InsertStaticSequenceList:静态顺序表空间不足，插入失败！\n");
        return 1;
    }
    // 索引位置从0开始，所以可以插入的范围是0到list->length
    if (index > list->length || index < 0) {
        printf("InsertStaticSequenceList:插入索引%d超过索引范围！\n", index);
        return 1;
    }
    // 从最后一个元素开始交换后移，list->length是空的
    for (int i = list->length; i > index; i--) {
        list->data[i] = list->data[i - 1];
    }
    list->data[index] = elem;
    list->length++;
    return 0;
}

// 插入动态顺序表
int InsertDynamicSequenceList(DynamicSequenceList* list, int index, element_type elem) {
    if (index > list->length || index < 0) {
        printf("InsertDynamicSequenceList:插入索引%d超过索引范围！\n", index);
        return 1;
    }
    // 当动态顺序表已经满了，需要新增一个位置
    // 为了避免索引无效而多增加一个空间，所以放在检查索引值的后面
    if (list->length >= MAXSIZE) {
        int result = ReIncreaseDynamicSequenceList(list, 1);
        if (result == 1) {
            printf("InsertDynamicSequenceList:申请空间失败！\n");
            return 1;
        }
    }
    for (int i = list->length; i > index; i--) {
        list->data[i] = list->data[i - 1];
    }
    list->data[index] = elem;
    list->length++;
    return 0;
}

// 循环插入静态顺序表
int LoopInsertStaticSequenceList(StaticSequenceList* list, element_type* elem, int start, int end) {
    for (int i = 0; i < end; i++) {
        int result = InsertStaticSequenceList(list, i, elem[i + start]);
        if (result == 1) {
            printf("LoopInsertStaticSequenceList:循环插入失败！\n");
            return 1;
        }
    }
    return 0;
}

// 循环插入动态顺序表
int LoopInsertDynamicSequenceList(DynamicSequenceList* list, element_type* elem, int start, int end) {
    for (int i = 0; i < end; i++) {
        int result = InsertDynamicSequenceList(list, i, elem[i + start]);
        if (result == 1) {
            printf("LoopInsertDynamicSequenceList:循环插入失败！\n");
            return 1;
        }
    }
    return 0;
}

// 删除静态顺序表
int DeleteStaticSequenceList(StaticSequenceList* list, int index, element_type *elem) {
    if (index >= list->length || index < 0) {
        printf("DeleteStaticSequenceList:删除索引超过索引范围！\n");
        return 1;
    }
    *elem = list->data[index];
    for (int i = index; i < list->length; i++) {
        list->data[i] = list->data[i + 1];
    }
    list->length--;
    return 0;
}

// 删除动态顺序表
int DeleteDynamicSequenceList(DynamicSequenceList* list, int index, element_type *elem) {
    if (index >= list->length || index < 0) {
        printf("DeleteDynamicSequenceList:删除索引超过索引范围！\n");
        return 1;
    }
    *elem = list->data[index];
    for (int i = index; i < list->length; i++) {
        list->data[i] = list->data[i + 1];
    }
    list->length--;
    return 0;
}

// 删除多个静态顺序表
int MultiDeleteStaticSequenceList(StaticSequenceList* list, int index, int len, element_type* elem) {
    if (index + len >= list->length || index < 0) {
        printf("MultiDeleteStaticSequenceList:删除索引超过索引范围！\n");
        return 1;
    }
    for (int i = index; i < list->length - len; i++) {
        if (i < index + len) {
            elem[i - index] = list->data[i];
        }
        list->data[i] = list->data[i + len];
    }
    list->length -= len;
    return 0;
}

// 删除多个动态顺序表
int MultiDeleteDynamicSequenceList(DynamicSequenceList* list, int index, int len, element_type* elem) {
    if (index + len >= list->length || index < 0) {
        printf("MultiDeleteDynamicSequenceList:删除索引超过索引范围！\n");
        return 1;
    }
    for (int i = index; i < list->length - len; i++) {
        if (i < index + len) {
            elem[i - index] = list->data[i];
        }
        list->data[i] = list->data[i + len];
    }
    list->length -= len;
    return 0;
}

// 按位查找静态顺序表元素
element_type GetStaticSequenceListElement(StaticSequenceList list, int index) {
    if (index >= list.length || index < 0) {
        printf("GetStaticSequenceListElement:查找索引超过索引范围！\n");
        return DEFAULTELEM;
    }
    return list.data[index];
}

// 按位查找动态顺序表元素
element_type GetDynamicSequenceListElement(DynamicSequenceList list, int index) {
    if (index >= list.length || index < 0) {
        printf("GetDynamicSequenceListElement:查找索引超过索引范围！\n");
        return DEFAULTELEM;
    }
    return list.data[index];
}

// 按值查找静态顺序表索引
int LocateStaticSequenceListElement(StaticSequenceList list, element_type elem) {
    for (int i = 0; i < list.length; i++) {
        if (list.data[i] == elem) {
            return i;
        }
    }
    printf("LocateStaticSequenceListElement:未能定位到对应值的元素！\n");
    return -1;
}

// 按值查找动态顺序表索引
int LocateDynamicSequenceListElement(DynamicSequenceList list, element_type elem) {
    for (int i = 0; i < list.length; i++) {
        if (list.data[i] == elem) {
            return i;
        }
    }
    printf("LocateDynamicSequenceListElement:未能定位到对应值的元素！\n");
    return -1;
}

// 判空静态顺序表
int EmptyStaticSequenceList(StaticSequenceList list) {
    if (list.length == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

// 判空动态顺序表
int EmptyDynamicSequenceList(DynamicSequenceList list) {
    if (list.length == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

// 销毁动态顺序表
int DestroyDynamicSequenceList(DynamicSequenceList* list) {
    if (list != NULL) {
        free(list->data);
    }
    list = NULL;
    return 0;
}

