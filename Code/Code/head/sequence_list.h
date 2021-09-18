#include "head.h"

// 静态顺序表
typedef struct {
    element_type *data;
    int length;
} StaticSequenceList;

// 动态顺序表
typedef struct {
    element_type *data;
    int max_size, length;
} DynamicSequenceList;

// 初始化
bool InitSequenceList(StaticSequenceList &list) {
    list.data = (element_type *) malloc(sizeof(element_type) * MAXSIZE);
    list.length = 0;
    return true;
}

bool InitSequenceList(StaticSequenceList &list, int max_size) {
    list.data = (element_type *) malloc(sizeof(element_type) * max_size);
    list.length = 0;
    return true;
}

StaticSequenceList InitStaticSequenceList() {
    auto *list = (StaticSequenceList *) malloc(sizeof(StaticSequenceList));
    list->data = (element_type *) malloc(sizeof(element_type) * MAXSIZE);
    list->length = 0;
    return (StaticSequenceList &) list;
}

StaticSequenceList InitStaticSequenceList(int max_size) {
    auto *list = (StaticSequenceList *) malloc(sizeof(StaticSequenceList));
    list->data = (element_type *) malloc(sizeof(element_type) * max_size);
    list->length = 0;
    return (StaticSequenceList &) list;
}

bool InitSequenceList(DynamicSequenceList &list) {
    list.length = 0;
    list.data = (element_type *) malloc(sizeof(element_type) * MAXSIZE);
    list.max_size = MAXSIZE;
    return true;
}

bool InitSequenceList(DynamicSequenceList &list, int max_size) {
    list.length = 0;
    list.data = (element_type *) malloc(sizeof(element_type) * max_size);
    list.max_size = max_size;
    return true;
}

DynamicSequenceList InitDynamicSequenceList() {
    auto *list = (DynamicSequenceList *) malloc(sizeof(DynamicSequenceList));
    list->data = (element_type *) malloc(sizeof(element_type) * MAXSIZE);
    list->length = 0;
    list->max_size = MAXSIZE;
    return (DynamicSequenceList &) list;
}

DynamicSequenceList InitDynamicSequenceList(int max_size) {
    auto *list = (DynamicSequenceList *) malloc(sizeof(DynamicSequenceList));
    list->data = (element_type *) malloc(sizeof(element_type) * max_size);
    list->length = 0;
    list->max_size = MAXSIZE;
    return (DynamicSequenceList &) list;
}

// 打印
template<class List>
bool PrintSequenceList(List list) {
    for (int i = 0; i < list.length; i++) {
        printf("第%d个元素值为%c\n", i + 1, list.data[i]);
    }
    return true;
}

// 增长数组长度
bool IncreaseSequenceList(DynamicSequenceList &list, int length) {
    if (length <= 0) {
        printf("IncreaseSequenceList:申请空间应该大于0！\n");
        return false;
    }
    // 申请一片连续的存储空间
    int new_length = list.max_size + length;
    void *pointer = realloc(list.data, new_length * sizeof(element_type));
    if (pointer == nullptr) {
        printf("IncreaseSequenceList:申请失败！\n");
        return false;
    }
    return true;
}

// 判空
template<class List>
bool EmptySequenceList(List list) {
    return list.length == 0;
}

// 插入
bool InsertSequenceList(StaticSequenceList &list, int index, element_type elem) {
    // 当静态顺序表已经满了就不能插入任何元素
    if (list.length >= MAXSIZE) {
        printf("InsertSequenceList:静态顺序表空间不足，插入失败！\n");
        return false;
    }
    // 索引位置从0开始，所以可以插入的范围是0到list->length
    if (index > list.length || index < 0) {
        printf("InsertSequenceList:插入索引%d超过索引范围！\n", index);
        return false;
    }
    // 从最后一个元素开始交换后移，list->length是空的
    for (int i = list.length; i > index; i--) {
        list.data[i] = list.data[i - 1];
    }
    list.data[index] = elem;
    list.length++;
    return true;
}

bool InsertSequenceList(DynamicSequenceList &list, int index, element_type elem) {
    if (index > list.length || index < 0) {
        printf("InsertDynamicSequenceList:插入索引%d超过索引范围！\n", index);
        return false;
    }
    // 当动态顺序表已经满了，需要新增一个位置
    // 为了避免索引无效而多增加一个空间，所以放在检查索引值的后面
    if (list.length >= MAXSIZE) {
        bool result = IncreaseSequenceList(list, 1);
        if (!result) {
            printf("InsertDynamicSequenceList:申请空间失败！\n");
            return false;
        }
    }
    for (int i = list.length; i > index; i--) {
        list.data[i] = list.data[i - 1];
    }
    list.data[index] = elem;
    list.length++;
    return true;
}

// 循环插入
template<class List>
bool LoopInsertSequenceList(List &list, element_type *elem, int start, int end) {
    for (int i = 0; i < end; i++) {
        bool result = InsertSequenceList(list, i, elem[i + start]);
        if (!result) {
            printf("LoopInsertSequenceList:循环插入失败！\n");
            return false;
        }
    }
    return true;
}

// 删除
template<class List>
element_type DeleteSequenceList(List &list, int index) {
    if (index >= list.length || index < 0) {
        printf("DeleteStaticSequenceList:删除索引超过索引范围！\n");
        return false;
    }
    element_type elem = list.data[index];
    for (int i = index; i < list.length; i++) {
        list.data[i] = list.data[i + 1];
    }
    list.length--;
    return elem;
}

// 删除多个元素
template<class List>
element_type* MultiDeleteSequenceList(List &list, int index, int length) {
    if (index + length >= list.length || index < 0) {
        printf("MultiDeleteSequenceList:删除索引超过索引范围！\n");
        return nullptr;
    }
    auto elem = new element_type[length];
    for (int i = index; i < list.length - length; i++) {
        if (i < index + length) {
            elem[i - index] = list.data[i];
        }
        list.data[i] = list.data[i + length];
    }
    list.length -= length;
    return elem;
}

// 按位查找顺序表元素
template<class List>
element_type GetSequenceListElem(List list, int index) {
    if (index >= list.length || index < 0) {
        printf("GetSequenceListElement:查找索引%d超过索引范围！\n", index);
        return DEFAULTELEM;
    }
    return list.data[index];
}

// 按值查找顺序表索引
template<class List>
int LocateSequenceList(List list, element_type elem) {
    for (int i = 0; i < list.length; i++) {
        if (list.data[i] == elem) {
            return i;
        }
    }
    printf("LocateSequenceListElement:未能定位到对应值%c的元素！\n", elem);
    return -1;
}

// 销毁动态顺序表
int DestroyDynamicSequenceList(DynamicSequenceList &list) {
    delete (list.data);
    return 0;
}



