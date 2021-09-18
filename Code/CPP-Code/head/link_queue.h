#include <iostream>
#include "head.h"

// 链队结点
class LinkQueueNode {
private:
    // 数据
    element_type _data;
    // 指针
    LinkQueueNode *_next;
public:
    // 设置数据
    bool SetData(element_type elem);

    // 获取数据
    element_type GetData() const;

    // 设置指针
    bool SetNext(LinkQueueNode *next);

    // 获取指针
    LinkQueueNode *GetNext();

    // 构造函数
    LinkQueueNode() {
        this->SetData(DEFAULTELEM);
        this->SetNext(nullptr);
    }

    LinkQueueNode(element_type elem) {
        this->SetData(elem);
        this->SetNext(nullptr);
    }

    LinkQueueNode(element_type elem, LinkQueueNode *next) {
        this->SetData(elem);
        this->SetNext(next);
    }
};

bool LinkQueueNode::SetData(element_type elem) {
    this->_data = elem;
    return true;
}

element_type LinkQueueNode::GetData() const {
    return this->_data;
}

bool LinkQueueNode::SetNext(LinkQueueNode *next) {
    this->_next = next;
    return true;
}

LinkQueueNode *LinkQueueNode::GetNext() {
    return this->_next;
}

// 链队
class LinkQueue {
private:
    // 队头指针和队尾指针
    LinkQueueNode *_front{}, *_rear{};
    // 长度
    int _length{};
public:
    // 设置队首指针
    bool SetFront(LinkQueueNode *front);

    // 获取对首指针
    LinkQueueNode *GetFront();

    // 设置队尾指针
    bool SetRear(LinkQueueNode *rear);

    // 获取队尾指针
    LinkQueueNode *GetRear();

    // 队长自加
    bool SetLength();

    // 设置队长
    bool SetLength(int length);

    // 获取队长
    int GetLength() const;

    // 构造函数
    LinkQueue();

    // 判空
    bool Empty() const;

    // 入队
    bool Enter(element_type elem);

    // 出队
    element_type Depart();
};

bool LinkQueue::SetFront(LinkQueueNode *front) {
    this->_front = front;
    return true;
}

LinkQueueNode *LinkQueue::GetFront() {
    return this->_front;
}

bool LinkQueue::SetRear(LinkQueueNode *rear) {
    this->_rear = rear;
    return true;
}

LinkQueueNode *LinkQueue::GetRear() {
    return this->_rear;
}

bool LinkQueue::SetLength() {
    this->_length++;
    return true;
}

bool LinkQueue::SetLength(int length) {
    this->_length = length;
    return true;
}

int LinkQueue::GetLength() const {
    return this->_length;
}

LinkQueue::LinkQueue() {
    auto *node = new LinkQueueNode();
    this->SetFront(node);
    this->SetRear(node);
    this->SetLength(0);
}

bool LinkQueue::Empty() const {
    return this->GetLength() == 0;
}

bool LinkQueue::Enter(element_type elem) {
    // 创建新结点
    auto *node = new LinkQueueNode(elem);
    // 把最后一个元素的next连接到node
    this->GetRear()->SetNext(node);
    // 移动尾指针
    this->SetRear(node);
    return true;
}

element_type LinkQueue::Depart() {
    if(this->Empty()){
        cout << "Depart:The queue is empty!" << endl;
        return DEFAULTELEM;
    }
    // 获取对首元素下一个元素的数据
    element_type elem = this->GetFront()->GetNext()->GetData();
    // 后移移位
    this->GetFront()->SetNext(this->GetFront()->GetNext()->GetNext());
    return true;
}


