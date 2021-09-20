#include "head.h"

// 块链串结点
class LinkStringNode {
private:
    // 数据
    char *_data{};
    // 指针
    LinkStringNode *_next{};
public:
    // 初始化数据
    bool SetData();

    bool SetData(int data_size);

    // 设置数据
    bool SetData(char *character);

    bool SetData(int index, char character);

    // 获取数据
    char *GetData();

    char GetData(int index);

    // 设置指针
    bool SetNext();

    bool SetNext(LinkStringNode *next);

    // 获取指针
    LinkStringNode *GetNext();

    // 初始化
    LinkStringNode();

    explicit LinkStringNode(int max_size);

    LinkStringNode(int max_size, LinkStringNode *next);

    LinkStringNode(int max_size, char *character, LinkStringNode *next);

    LinkStringNode(int max_size, char *character);
};

bool LinkStringNode::SetData() {
    this->_data = new char[1];
    return true;
}

bool LinkStringNode::SetData(int data_size) {
    this->_data = new char[data_size];
    return true;
}

bool LinkStringNode::SetData(char *character) {
    this->_data = character;
    return true;
}

bool LinkStringNode::SetData(int index, char character) {
    this->_data[index] = character;
    return true;
}

char *LinkStringNode::GetData() {
    return this->_data;
}

char LinkStringNode::GetData(int index) {
    return this->_data[index];
}

bool LinkStringNode::SetNext() {
    this->_next = nullptr;
    return true;
}

bool LinkStringNode::SetNext(LinkStringNode *next) {
    this->_next = next;
    return true;
}

LinkStringNode *LinkStringNode::GetNext() {
    return this->_next;
}

LinkStringNode::LinkStringNode() {
    this->SetData();
    this->SetNext();
}

LinkStringNode::LinkStringNode(int max_size) {
    this->SetData(max_size);
    this->SetNext();
}

LinkStringNode::LinkStringNode(int max_size, LinkStringNode *next) {
    this->SetData(max_size);
    this->SetNext(next);
}

LinkStringNode::LinkStringNode(int max_size, char *character, LinkStringNode *next) {
    this->SetData(max_size);
    for (int i = 0; i < max_size; i++) {
        if (character[i] != '\0') {
            this->SetData(i, character[i]);
        }
    }
    this->SetNext(next);
}

LinkStringNode::LinkStringNode(int max_size, char *character) {
    this->SetData(max_size);
    for (int i = 0; i < max_size; i++) {
        if (character[i] != '\0') {
            this->SetData(i, character[i]);
        }
    }
    this->SetNext();
}

class LinkString {
private:
    // 头尾指针
    LinkStringNode *_front{}, *_rear{};
    // 块链长度
    int _data_size{};
    // 长度
    int _length{};
public:
    // 设置头指针
    bool SetFront();
    bool SetFront(LinkStringNode *front);

    // 获取头指针
    LinkStringNode *GetFront();

    // 设置尾指针
    bool SetRear();
    bool SetRear(LinkStringNode *rear);

    // 获取尾指针
    LinkStringNode *GetRear();

    // 设置总体块链单元长度
    bool SetDataSize();

    bool SetDataSize(int data_size);

    // 获取数据长度
    int GetDataSize() const;

    // 数据长度自加
    bool SetLength();

    // 设置数据长度
    bool SetLength(int length);

    // 获取数据长度
    int GetLength() const;

    // 初始化
    LinkString();

    explicit LinkString(int data_size);
};

bool LinkString::SetFront() {
    this->_front = nullptr;
    return true;
}

bool LinkString::SetFront(LinkStringNode *front) {
    this->_front = front;
    return true;
}

LinkStringNode *LinkString::GetFront() {
    return this->_front;
}

bool LinkString::SetRear() {
    this->_rear = nullptr;
    return true;
}

bool LinkString::SetRear(LinkStringNode *rear) {
    this->_rear = rear;
    return true;
}

LinkStringNode *LinkString::GetRear() {
    return this->_rear;
}

bool LinkString::SetDataSize() {
    this->_data_size = 1;
    return true;
}

bool LinkString::SetDataSize(int data_size) {
    this->_data_size = data_size;
    return true;
}

int LinkString::GetDataSize() const {
    return this->_data_size;
}

bool LinkString::SetLength() {
    this->_length++;
    return true;
}

bool LinkString::SetLength(int length) {
    this->_length = length;
    return true;
}

int LinkString::GetLength() const {
    return this->_length;
}

LinkString::LinkString() {
    this->SetFront();
    this->SetRear();
    this->SetLength(0);
    this->SetDataSize(1);
}

LinkString::LinkString(int data_size) {
    this->SetFront();
    this->SetRear();
    this->SetLength(0);
    this->SetDataSize(data_size);
}
