#include <cstdio>
#include <cstdlib>
#include "head.h"

class StaticLinkListNode {
private:
    // 数据元素
    element_type _data;
    // 下一个元素的数组下标
    int _next;
public:
    // 设置元素
    bool SetData(element_type elem);
    // 获取元素
    element_type GetData();
    // 设置下标
    bool SetNext(int index);
    // 获取下标
    int GetNext();

    // 构造函数
    StaticLinkListNode();

    StaticLinkListNode(element_type elem);

    StaticLinkListNode(element_type elem, int next);

    // 销毁
    bool Destroy();
};

class StaticLinkList {
private:
    // 首元素地址
    int _first;
    // 数据长度
    int _length;
    // 数据当前最大长度
    int _max_size;
public:
    // 设置首元素地址
    bool SetFirst(int index);

    // 获取首元素地址
    int GetFirst();

    // 数据长度自加
    bool SetLength();

    // 设置数据长度
    bool SetLength(int length);

    // 获取数据长度
    int GetLength();

    // 设置数据当前最大长度
    bool SetMaxSize(int max_size);

    // 获取数据当前最大长度
    int GetMaxSize();

    // 数据
    StaticLinkListNode *data;
};