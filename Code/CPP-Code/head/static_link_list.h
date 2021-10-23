#include "head.h"

class StaticLinkListNode {
private:
    // 数据元素
    element_type _data{};
    // 下一个元素的数组下标
    int _next{};
public:
    // 设置元素
    bool SetData(element_type elem);
    // 获取元素
    element_type GetData() const;
    // 设置下标
    bool SetNext(int index);
    // 获取下标
    int GetNext() const;

    // 构造函数
    StaticLinkListNode();

    explicit StaticLinkListNode(element_type elem);

    StaticLinkListNode(element_type elem, int next);

    // 销毁
    bool Destroy();
};

bool StaticLinkListNode::SetData(element_type elem) {
    this->_data = elem;
    return true;
}

element_type StaticLinkListNode::GetData() const {
    return this->_data;
}

bool StaticLinkListNode::SetNext(int index) {
    this->_next = index;
    return true;
}

int StaticLinkListNode::GetNext() const {
    return this->_next;
}

StaticLinkListNode::StaticLinkListNode() {
    this->SetData(DEFAULTELEM);
    this->SetNext(-1);
}

StaticLinkListNode::StaticLinkListNode(element_type elem) {
    this->SetData(elem);
    this->SetNext(-1);
}

StaticLinkListNode::StaticLinkListNode(element_type elem, int next) {
    this->SetData(elem);
    this->SetNext(next);
}

bool StaticLinkListNode::Destroy() {
    this->SetData(DEFAULTELEM);
    this->SetNext(0);
    return true;
}

class StaticLinkList {
private:
    // 首元素地址
    int _first{};
    // 数据长度
    int _length{};
    // 数据当前最大长度
    int _max_size{};
public:
    // 数据
    StaticLinkListNode *data;

    // 设置首元素地址
    bool SetFirst(int first);

    // 获取首元素地址
    int GetFirst() const;

    // 数据长度自加
    bool SetLength();

    // 设置数据长度
    bool SetLength(int length);

    // 获取数据长度
    int GetLength() const;

    // 设置数据当前最大长度
    bool SetMaxSize(int max_size);

    // 获取数据当前最大长度
    int GetMaxSize() const;

    // 构造函数
    StaticLinkList();

    StaticLinkList(int first, element_type elem);
};

bool StaticLinkList::SetFirst(int first) {
    this->_first = first;
    return true;
}

int StaticLinkList::GetFirst() const {
    return this->_first;
}

bool StaticLinkList::SetLength() {
    this->_length++;
    return true;
}

bool StaticLinkList::SetLength(int length) {
    this->_length = length;
    return true;
}

int StaticLinkList::GetLength() const {
    return this->_length;
}

bool StaticLinkList::SetMaxSize(int max_size) {
    this->_max_size = max_size;
    return true;
}

int StaticLinkList::GetMaxSize() const {
    return this->_max_size;
}

StaticLinkList::StaticLinkList() {
    this->SetFirst(DEFAULTELEM);
    this->SetLength(0);
    this->SetMaxSize(MAXSIZE);
    this->data = new StaticLinkListNode[MAXSIZE];
}

StaticLinkList::StaticLinkList(int first, element_type elem) {
    this->SetFirst(first);
    this->SetLength(1);
    this->SetMaxSize(MAXSIZE);
    this->data = new StaticLinkListNode[MAXSIZE];
    this->data[first].SetData(elem);
    this->data[first].SetNext(-1);
}
