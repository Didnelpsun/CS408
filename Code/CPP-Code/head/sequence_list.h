#include <cstdio>
#include <cstdlib>
#include "head.h"

#pragma warning(disable:6385)
#pragma warning(disable:6386)

// 顺序表
class SequenceList {
public:
    element_type *data{};
    int length{};
    // 插入函数
    virtual bool Insert(int index, element_type elem);
    // 打印函数
    void Printf();
    // 循环插入函数
    bool LoopInsert(element_type *elem, int start, int end);
    // 删除函数
    bool Delete(int index, element_type &elem);
    // 多个删除函数
    bool MultiDelete(int index, int len, element_type *elem);
    // 按位获取元素
    element_type GetElem(int index);
    // 按值获取元素
    int Locate(element_type elem);
    // 判空
    bool Empty();
    // 销毁
    bool Destroy();
};

// 静态顺序表
class StaticSequenceList: public SequenceList{
public:
    element_type data[MAXSIZE]{};
    int length;
    // 构造函数
    StaticSequenceList();
    // 插入函数
    bool Insert(int index, element_type elem) override;
};

// 动态顺序表
class DynamicSequenceList: public SequenceList{
public:
    // 给一个指针来分配动态数组
    element_type *data;
    int length;
    // 已分配的最大容量
    int max_size;
    // 构造函数
    DynamicSequenceList();
    // 插入函数
    bool Insert(int index, element_type elem) override;

private:
    // 分配其他地址增长动态顺序表的数据空间长度
    bool OtherIncrease(int len);
    // 重新分配地址增长动态顺序表的数据空间长度
    bool ReIncrease(int len);
};

StaticSequenceList::StaticSequenceList() : SequenceList() {
    this->length=0;
}

DynamicSequenceList::DynamicSequenceList() : SequenceList() {
    // 初初始化动态顺序表长度为0
    this->max_size=0;
    this->length = 0;
    // 申请一片连续的存储空间
    auto* space = (element_type*)malloc(MAXSIZE * sizeof(element_type));
    if (space) {
        this->data = space;
        this->max_size = MAXSIZE;
    }
    else {
        printf("InitSequenceList:分配空间失败！\n");
    }
}

void SequenceList::Printf() {
    for (int i = 0; i < this->length; i++) {
        printf("第%d个元素值为%c\n", i + 1, this->data[i]);
    }
}

bool DynamicSequenceList::OtherIncrease(int len) {
    if (len <= 0) {
        printf("OtherIncrease:申请空间应该大于0！\n");
        return false;
    }
    // 申请一片连续的存储空间
    int new_length = this->max_size + len;
    auto* space = (element_type*)malloc(new_length * sizeof(element_type));
    if (space) {
        // 建立中间变量
        this->data = space;
        element_type* temp = this->data;
        for (int i = 0; i < this->length; i++) {
            this->data[i] = temp[i];
        }
        this->max_size = new_length;
        free(temp);
        return true;
    }
    else {
        printf("OtherIncrease:重新分配空间失败！\n");
        return false;
    }
}

bool DynamicSequenceList::ReIncrease(int len) {
    if (len <= 0) {
        printf("ReIncrease:申请空间应该大于0！\n");
        return false;
    }
    // 申请一片连续的存储空间
    int new_length = this->max_size + len;
    auto* space = (element_type*)realloc(this->data, new_length * sizeof(element_type));
    if (space) {
        this->data = space;
        this->max_size += len;
        return true;
    }
    else {
        this->max_size = 0;
        this->length = 0;
        printf("ReIncrease:分配其他地址空间失败！\n");
        return false;
    }
}

bool SequenceList::Insert(int index, element_type elem) {
    return false;
}

bool StaticSequenceList::Insert(int index, element_type elem) {
    // 当静态顺序表已经满了就不能插入任何元素
    if (this->length >= MAXSIZE) {
        printf("Insert:静态顺序表空间不足，插入失败！\n");
        return false;
    }
    // 索引位置从0开始，所以可以插入的范围是0到list->length
    if (index > this->length || index < 0) {
        printf("Insert:插入索引%d超过索引范围！\n", index);
        return false;
    }
    // 从最后一个元素开始交换后移，list->length是空的
    for (int i = this->length; i > index; i--) {
        this->data[i] = this->data[i - 1];
    }
    this->data[index] = elem;
    this->length++;
    return true;
}

bool DynamicSequenceList::Insert(int index, element_type elem) {
    if (index > this->length || index < 0) {
        printf("Insert:插入索引%d超过索引范围！\n", index);
        return false;
    }
    // 当动态顺序表已经满了，需要新增一个位置
    // 为了避免索引无效而多增加一个空间，所以放在检查索引值的后面
    if (this->length >= MAXSIZE) {
        bool result = this->ReIncrease(1);
        if (!result) {
            printf("Insert:申请空间失败！\n");
            return false;
        }
    }
    for (int i = this->length; i > index; i--) {
        this->data[i] = this->data[i - 1];
    }
    this->data[index] = elem;
    this->length++;
    return true;
}

bool SequenceList::LoopInsert(element_type *elem, int start, int end) {
    for (int i = 0; i < end; i++) {
        bool result = this->Insert(i, elem[i + start]);
        if (!result) {
            printf("LoopInsert:循环插入失败！\n");
            return false;
        }
    }
    return true;
}

bool SequenceList::Delete(int index, element_type &elem) {
    if (index >= this->length || index < 0) {
        printf("Delete:删除索引超过索引范围！\n");
        return false;
    }
    elem = this->data[index];
    for (int i = index; i < this->length; i++) {
        this->data[i] = this->data[i + 1];
    }
    this->length--;
    return true;
}

bool SequenceList::MultiDelete(int index, int len, element_type *elem) {
    if (index + len >= this->length || index < 0) {
        printf("MultiDelete:删除索引超过索引范围！\n");
        return false;
    }
    for (int i = index; i < this->length - len; i++) {
        if (i < index + len) {
            elem[i - index] = this->data[i];
        }
        this->data[i] = this->data[i + len];
    }
    this->length -= len;
    return true;
}

element_type SequenceList::GetElem(int index) {
    if (index >= this->length || index < 0) {
        printf("GetElem:查找索引超过索引范围！\n");
        return DEFAULTELEM;
    }
    return this->data[index];
}


int SequenceList::Locate(element_type elem) {
    for (int i = 0; i < this->length; i++) {
        if (this->data[i] == elem) {
            return i;
        }
    }
    printf("Locate:未能定位到对应值的元素！\n");
    return -1;
}

bool SequenceList::Empty() {
    if (this->length == 0) {
        return false;
    }
    else {
        return true;
    }
}

bool SequenceList::Destroy() {
    if (this->data) {
        free(this->data);
    }
    delete this;
    return true;
}

