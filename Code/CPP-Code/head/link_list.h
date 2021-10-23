#ifndef _LINK_LIST_
#define _LINK_LIST_

#include <iostream>
#include "head.h"

using namespace std;

// 单链表结点
class LinkListNode {
private:
    // 数据
    element_type _data{};
    // 指针
    LinkListNode *_next{};
public:
    // 设置数据
    bool SetData(element_type elem);

    // 获取数据
    element_type GetData() const;

    // 设置next
    bool SetNext(LinkListNode *next);

    // 获取next
    LinkListNode *GetNext();

    // 构造函数
    LinkListNode();

    explicit LinkListNode(element_type elem);

    LinkListNode(element_type elem, LinkListNode *next);

    // 销毁
    bool Destory();
};

bool LinkListNode::SetData(element_type elem) {
    this->_data = elem;
    return true;
}

element_type LinkListNode::GetData() const {
    return this->_data;
}

bool LinkListNode::SetNext(LinkListNode *next) {
    this->_next = next;
    return true;
}

LinkListNode *LinkListNode::GetNext() {
    return this->_next;
}

LinkListNode::LinkListNode() {
    this->SetData(DEFAULTELEM);
    this->SetNext(nullptr);
}

LinkListNode::LinkListNode(element_type elem) {
    this->SetData(elem);
    this->SetNext(nullptr);
}

LinkListNode::LinkListNode(element_type elem, LinkListNode *next) {
    this->SetData(elem);
    this->SetNext(next);
}

bool LinkListNode::Destory() {
    if (this->GetNext() != nullptr) {
        free(this->GetNext());
    }
    this->SetData(DEFAULTELEM);
    this->SetNext(nullptr);
    return true;
}

class LinkList {
private:
    // 指针
    LinkListNode *_next{};
    // 链表长度
    int _length{};
    // 类型，真有头节点，假无头节点
    bool _type{};
protected:
    // 设置链表类型
    bool SetType(bool type);

public:
    // 设置next
    bool SetNext(LinkListNode *next);

    // 获取next
    LinkListNode *GetNext();

    // 长度自加1
    bool SetLength();

    // 设置长度
    bool SetLength(int length);

    // 获取长度
    int GetLength() const;

    // 获取链表类型
    bool GetType() const;

    // 构造函数
    LinkList();

    // 打印
    virtual bool Print() = 0;

    // 判空
    bool Empty() const;

    // 插入
    virtual bool Insert(int index, element_type elem) = 0;

    // 前插入
    bool PriorInsert(element_type *elem, int start, int length);

    // 后插入
    bool NextInsert(element_type *elem, int start, int length);

    // 删除
    element_type Delete(int index);

    virtual element_type *Delete(int index, int length) = 0;

    //按位查找
    virtual element_type GetElem(int index);

    // 按值查找
    virtual int Locate(element_type elem);

    // 销毁
    virtual bool Destroy();
};

bool LinkList::SetNext(LinkListNode *next) {
    this->_next = next;
    return true;
}

LinkListNode *LinkList::GetNext() {
    return this->_next;
}

bool LinkList::SetLength() {
    this->_length++;
    return true;
}

bool LinkList::SetLength(int length) {
    this->_length = length;
    return true;
}

int LinkList::GetLength() const {
    return this->_length;
}

bool LinkList::SetType(bool type) {
    this->_type = type;
    return true;
}

bool LinkList::GetType() const {
    return this->_type;
}

LinkList::LinkList() {
    this->SetNext(nullptr);
    this->SetLength(0);
}

element_type LinkList::GetElem(int index) {
    if (index >= this->GetLength() || index < 0) {
        // cout << "GetElem:查找索引" << index << "超过索引范围！" << endl;
        cout << "GetElem:The index " << index << " is out of range!" << endl;
        return DEFAULTELEM;
    }
    LinkListNode *node = this->GetNext();
    for (int i = 1; i < index; i++) {
        node = node->GetNext();
    }
    return node->GetData();
}

int LinkList::Locate(element_type elem) {
    LinkListNode *node = this->GetNext();
    for (int i = 1; i < this->GetLength(); i++) {
        if (node->GetData() == elem) {
            return i;
        }
    }
    // cout << "Locate:未能定位到值为" << elem << "的元素！" << endl;
    cout << "Locate:Can't locate the element with value " << elem << " !" << endl;
    return -1;
}

bool LinkList::Empty() const {
    return this->GetLength() == 0;
}

bool LinkList::PriorInsert(element_type *elem, int start, int length) {
    if (this->GetType()) {
        for (int i = 0; i < length; i++) {
            bool result = this->Insert(1, elem[i + start]);
            if (!result) {
                // cout << "PriorInsert:循环插入失败！索引值为" << i + start << endl;
                cout << "PriorInsert:Loop Insert of element with index value of " << i + start << " failed!" << endl;
                return false;
            }
        }
        return true;
    } else {
        for (int i = 0; i < length; i++) {
            bool result = this->Insert(0, elem[i + start]);
            if (!result) {
                // cout << "PriorInsert:循环插入失败！索引值为" << i + start << endl;
                cout << "PriorInsert:Loop Insert of element with index value of " << i + start << "failed!" << endl;
                return false;
            }
        }
        return true;
    }
}

bool LinkList::NextInsert(element_type *elem, int start, int length) {
    if (this->GetType()) {
        for (int i = 0; i < length; i++) {
            bool result = this->Insert(i + 1, elem[i + start]);
            if (!result) {
                // cout << "NextInsert:循环插入失败！索引值为" << i + start << endl;
                cout << "NextInsert:Loop insert of element with index value of " << i + start << "failed!" << endl;
                return false;
            }
        }
        return true;
    } else {
        for (int i = 0; i < length; i++) {
            bool result = this->Insert(i, elem[i + start]);
            if (!result) {
                // cout << "NextInsert:循环插入失败！索引值为" << i + start << endl;
                cout << "NextInsert:Loop insert of element with index value of " << i + start << "failed!" << endl;
                return false;
            }
        }
        return true;
    }
}

element_type LinkList::Delete(int index) {
    return *(this->Delete(index, 1));
}

bool LinkList::Destroy() {
    this->SetLength(0);
    free(this->GetNext());
    this->SetNext(nullptr);
    this->SetType(true);
    return true;
}

#endif