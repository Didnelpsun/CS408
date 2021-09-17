#include "head.h"

// 单链表结点
class DoubleLinkListNode {
private:
    // 数据
    element_type _data{};
    // 指针
    DoubleLinkListNode *_prior{}, *_next{};
public:
    // 设置数据
    bool SetData(element_type elem);

    // 获取数据
    element_type GetData() const;

    // 设置prior
    bool SetPrior(DoubleLinkListNode *prior);

    // 获取prior
    DoubleLinkListNode *GetPrior();

    // 设置next
    bool SetNext(DoubleLinkListNode *next);

    // 获取next
    DoubleLinkListNode *GetNext();

    // 构造函数
    DoubleLinkListNode();

    explicit DoubleLinkListNode(element_type elem);

    DoubleLinkListNode(element_type elem, DoubleLinkListNode *next);

    DoubleLinkListNode(element_type elem, DoubleLinkListNode *prior, DoubleLinkListNode *next);

    // 销毁
    bool Destory();
};

bool DoubleLinkListNode::SetData(element_type elem) {
    this->_data = elem;
    return true;
}

element_type DoubleLinkListNode::GetData() const {
    return this->_data;
}

bool DoubleLinkListNode::SetPrior(DoubleLinkListNode *prior) {
    this->_prior = prior;
    return true;
}

DoubleLinkListNode *DoubleLinkListNode::GetPrior() {
    return this->_prior;
}

bool DoubleLinkListNode::SetNext(DoubleLinkListNode *next) {
    this->_next=next;
    return true;
}

DoubleLinkListNode *DoubleLinkListNode::GetNext() {
    return this->_next;
}

DoubleLinkListNode::DoubleLinkListNode() {
    this->SetPrior(nullptr);
    this->SetNext(nullptr);
    this->SetData(DEFAULTELEM);
}

DoubleLinkListNode::DoubleLinkListNode(element_type elem) {
    this->SetPrior(nullptr);
    this->SetNext(nullptr);
    this->SetData(elem);
}

DoubleLinkListNode::DoubleLinkListNode(element_type elem, DoubleLinkListNode *next) {
    this->SetPrior(nullptr);
    this->SetNext(next);
    this->SetData(elem);
}

DoubleLinkListNode::DoubleLinkListNode(element_type elem, DoubleLinkListNode *prior, DoubleLinkListNode *next) {
    this->SetPrior(prior);
    this->SetNext(next);
    this->SetData(elem);
}

bool DoubleLinkListNode::Destory() {
    free(this->GetPrior());
    free(this->GetNext());
    this->SetPrior(nullptr);
    this->SetNext(nullptr);
    this->SetData(DEFAULTELEM);
    return true;
}