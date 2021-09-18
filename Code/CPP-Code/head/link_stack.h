#include "head.h"

using namespace std;

// 链栈
class LinkStackNode {
private:
    // 数据
    element_type _data{};
    // 指针
    LinkStackNode *_next{};

    // 设置数据
    bool SetData(element_type data);

    // 取数据
    element_type GetData() const;

    // 设置指针
    bool SetNext(LinkStackNode *next);

    // 获取指针
    LinkStackNode *GetNext();

public:

    // 构造函数
    LinkStackNode();

    explicit LinkStackNode(element_type data);

    LinkStackNode(element_type data, LinkStackNode *next);

    // 销毁
    bool Destroy();
};

bool LinkStackNode::SetData(element_type data) {
    this->_data = data;
    return true;
}

element_type LinkStackNode::GetData() const {
    return this->_data;
}

bool LinkStackNode::SetNext(LinkStackNode *next) {
    this->_next = next;
    return true;
}

LinkStackNode *LinkStackNode::GetNext() {
    return this->_next;
}

LinkStackNode::LinkStackNode() {
    this->SetData(DEFAULTELEM);
    this->SetNext(nullptr);
}

LinkStackNode::LinkStackNode(element_type data) {
    this->SetData(data);
    this->SetNext(nullptr);
}

LinkStackNode::LinkStackNode(element_type data, LinkStackNode *next) {
    this->SetData(data);
    this->SetNext(next);
}

bool LinkStackNode::Destroy() {
    this->SetData(DEFAULTELEM);
    delete (this->GetNext());
    this->SetNext(nullptr);
    return true;
}
