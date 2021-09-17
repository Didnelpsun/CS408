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

class LinkListWithHead : public LinkList {
public:
    // 构造函数
    LinkListWithHead();

    // 打印
    bool Print() override;

    // 插入
    bool Insert(int index, element_type elem) override;

    // 删除
    element_type *Delete(int index, int length) override;
};

LinkListWithHead::LinkListWithHead() {
    this->SetType(true);
};

bool LinkListWithHead::Print() {
    int i = 1;
    // cout << "第0个元素值为空" << endl;
    cout << "index: 0 -> value: NULL"  << endl;
    if (this->GetLength() == 0) {
        return true;
    }
    // 当前遍历指针
    LinkListNode *node = this->GetNext();
    while (node != nullptr) {
//        cout << "第" << i << "个元素值为" << node->GetData() << endl;
        cout << "index: " << i << " -> value: " << node->GetData() << endl;
        i++;
        node = node->GetNext();
    }
    return true;
}

bool LinkListWithHead::Insert(int index, element_type elem) {
    if (index < 1) {
        // cout << "Insert:插入索引值" << index << "过小！" << endl;
        cout << "Insert:Insert index value " << index << " is too small!" << endl;
        return false;
    }
    // 定义一个结点指针p指向当前扫描到的结点
    LinkListNode *node;
    // 定义一个变量i表示当前扫描到的结点的索引号
    int i = 1;
    // 将链表头结点的next指向node，为第1个结点
    node = this->GetNext();
    // 设置一个新结点进行插入
    auto *new_node = new LinkListNode(elem);
    // 如果该链表为空链表
    if (node == nullptr) {
        this->SetNext(new_node);
        this->SetLength();
        return true;
    }
    // 当插入的是第一个节点
    if (index == 1) {
        new_node->SetNext(node);
        this->SetNext(new_node);
        this->SetLength();
        return true;
    }
    // 循环遍历到达指定索引号的单链表的结点
    // 条件是当前结点的下一个不为空且索引号到达，所到达的结点一定不是空结点
    while (node->GetNext() != nullptr && i < index - 1) {
        node = node->GetNext();
        i++;
    }
    // 如果此时i小于index-1，表示遍历完还没有到达对应的索引
    if (i < index - 1) {
        // cout << "Insert:插入索引值" << index << "过大！" << endl;
        cout << "Insert:Insert index value" << index << " is too large!";
        return false;
    }
    // 此时i==index-1
    // 将node原来的后继给新的结点
    new_node->SetNext(node->GetNext());
    node->SetNext(new_node);
    this->SetLength();
    return true;
}

element_type *LinkListWithHead::Delete(int index, int length) {
    auto *data = new element_type[length];
    if (index < 1) {
        // cout << "Delete:删除索引值" << index << "过小！" << endl;
        cout << "Delete:Delete index value " << index << " is too small!" << endl;
        return data;
    }
    if (length < 1) {
        // cout << "Delete:删除长度" << length << "过小！" << endl;
        cout << "Delete:Delete length value " << length << " is too small!" << endl;
        return data;
    }
    // 定义一个结点指针start指向当前扫描到的结点，即要删除第一的元素的前一个
    LinkListNode *start;
    // 定义一个结点指针start指向当前扫描到的结点，要删除最后的元素
    LinkListNode *end;
    // 定义一个变量i表示当前扫描到的结点的索引号
    int i = 1;
    // 将链表头结点的next指向start，为第1个结点
    start = this->GetNext();
    // 如果链表没有任何数据
    if (start == nullptr) {
        // cout << "Delete:链表为空！" << endl;
        cout << "Delete:Link list is empty!" << endl;
        return data;
    }
    // 循环遍历到达指定索引号的单链表的结点
    // 条件是当前结点的下一个不为空且索引号到达，所到达的结点一定不是空结点
    while (start->GetNext() != nullptr && i < index - 1) {
        start = start->GetNext();
        i++;
    }
    // 如果此时i小于index-1，表示遍历完还没有到达对应的索引
    if (i < index - 1) {
        // cout << "Delete:删除索引值" << index << "过大！" << endl;
        cout << "Delete:Delete index value " << index << " is too large!" << endl;
        return data;
    }
    // 此时i==index-1，start到达，求end
    end = start;
    for (int i = 0; i < length; i++) {
        data[i] = end->GetData();
        end = end->GetNext();
        if (end == nullptr) {
            // cout << "Delete:删除索引最大值" << index + length - 1 << "大于链表最大索引" << length - 1 << "！" << endl;
            cout << "Delete:Delete index value" << index + length -1 << "is larger than link list's biggest index " << length - 1 << "!" << endl;
            return data;
        }
    }
    if (index == 1) {
        this->SetNext(end);
    } else {
        start->SetNext(end->GetNext());
    }
    this->SetLength(this->GetLength() - length);
    return data;
}

class LinkListWithoutHead : public LinkList {
private:
    // 数据
    element_type _data{};
public:
    // 设置数据
    bool SetData(element_type elem);

    // 获取数据
    element_type GetData() const;

    // 构造函数
    LinkListWithoutHead();

    // 打印
    bool Print() override;

    // 插入
    bool Insert(int index, element_type elem) override;

    // 删除
    element_type *Delete(int index, int length) override;

    // 按位查找
    element_type GetElem(int index) override;

    // 按值查找
    int Locate(element_type elem) override;

    // 销毁
    bool Destroy() override;
};

bool LinkListWithoutHead::SetData(element_type elem) {
    this->_data = elem;
    return true;
}

element_type LinkListWithoutHead::GetData() const {
    return this->_data;
}

LinkListWithoutHead::LinkListWithoutHead() {
    this->SetType(false);
    this->SetData(DEFAULTELEM);
}

bool LinkListWithoutHead::Print() {
    int i = 0;
    if (this->GetLength() == 0) {
        return true;
    }
    // cout << "第" << i << "个元素值为" << this->GetData() << endl;
    cout << "index: " << i << " -> value: " << this->GetData() << endl;
    // 当前遍历指针
    LinkListNode *node = this->GetNext();
    while (node != nullptr) {
        i++;
        // cout << "第" << i << "个元素值为" << node->GetData() << endl;
        cout << "index: " << i << " -> value: " << node->GetData() << endl;
        node = node->GetNext();
    }
    return true;
}

bool LinkListWithoutHead::Insert(int index, element_type elem) {
    if (index < 0) {
        // cout << "Insert:插入索引值" << index << "过小！" << endl;
        cout << "Insert:Insert index value " << index << " is too small!" << endl;
        return false;
    }
    if (index == 0) {
        if (this->GetLength() == 0) {
            this->SetData(elem);
            this->SetLength();
        } else {
            auto *node = new LinkListNode(this->GetData());
            node->SetNext(this->GetNext());
            this->SetData(elem);
            this->SetNext(node);
            this->SetLength();
        }
        return true;
    }
    // 定义一个结点指针node指向当前扫描到的结点
    LinkListNode *node;
    // 定义一个变量i表示当前扫描到的结点的索引号
    int i = 1;
    // 将链表头结点的next指向p，为第1个结点
    node = this->GetNext();
    // 设置一个新结点进行插入
    auto *new_node = new LinkListNode(elem);
    // 如果该链表为空链表
    if (node == nullptr) {
        this->SetLength();
        this->SetNext(new_node);
        return true;
    }
    // 循环遍历到达指定索引号的单链表的结点
    // 条件是当前结点的下一个不为空且索引号到达，所到达的结点一定不是空结点
    while (node->GetNext() != nullptr && i < index - 1) {
        node = node->GetNext();
        i++;
    }
    // 如果此时i小于index-1，表示遍历完还没有到达对应的索引
    if (i < index - 1) {
        // cout << "Insert:插入索引值" << index << "过大！" << endl;
        cout << "Insert:Insert index value" << index << " is too large!";
        return false;
    }
    // 此时i==index-1
    // 将p原来的后继给新的结点
    new_node->SetNext(node->GetNext());
    node->SetNext(new_node);
    this->SetLength();
    return true;
}

element_type *LinkListWithoutHead::Delete(int index, int length) {
    auto *data = new element_type[length];
    if (index < 0) {
        // cout << "Delete:删除索引值" << index << "过小！" << endl;
        cout << "Delete:Delete index value " << index << " is too small!";
        return data;
    }
    if (length < 1) {
        // cout << "Delete:删除长度" << length << "过小！" << endl;
        cout << "Delete:Delete length value " << length << " is too small!";
        return data;
    }
    // 定义一个结点指针start指向当前扫描到的结点，即要删除第一的元素的前一个
    LinkListNode *start;
    // 定义一个结点指针start指向当前扫描到的结点，要删除最后的元素
    LinkListNode *end;
    // 定义一个变量i表示当前扫描到的结点的索引号
    int i = 1;
    // 将链表头结点的next指向start，为第1个结点
    start = this->GetNext();
    // 如果链表没有任何数据
    if (this->GetData() == DEFAULTELEM) {
        // cout << "Delete:链表为空！" << endl;
        cout << "Delete:Link list is empty!" << endl;
        return data;
    }
    data[0] = this->GetData();
    // 循环遍历到达指定索引号的单链表的结点
    // 条件是当前结点的下一个不为空且索引号到达，所到达的结点一定不是空结点
    while (start->GetNext() != nullptr && i < index - 1) {
        start = start->GetNext();
        i++;
    }
    // 如果此时i小于index-1，表示遍历完还没有到达对应的索引
    if (i < index - 1) {
        // cout << "Delete:删除索引值" << index << "过大！" << endl;
        cout << "Delete:Delete index value " << index << " is too large!";
        return data;
    }
    // 从1开始遍历
    end = this->GetNext();
    for (int i = 1; i < index + length - 1; i++) {
        if (i >= index) {
            data[i - index] = end->GetData();
        }
        end = end->GetNext();
        if (end == nullptr) {
            // cout << "Delete:删除索引最大值" << index + length - 1 << "大于链表最大索引" << length - 1 << "！" << endl;
            cout << "Delete:Delete index value" << index + length -1 << "is larger than link list's biggest index " << length - 1 << "!" << endl;
            return data;
        }
    }
    data[length - 1] = end->GetData();
    if (index == 0) {
        this->SetData(end->GetNext()->GetData());
        this->SetNext(end->GetNext()->GetNext());
    }
    if (index == 1) {
        this->SetNext(end->GetNext());
    } else {
        start->SetNext(end->GetNext());
    }
    this->SetLength(this->GetLength() - length);
    return data;
}

element_type LinkListWithoutHead::GetElem(int index) {
    return index == 0 ? this->GetData() : LinkList::GetElem(index);
}

int LinkListWithoutHead::Locate(element_type elem) {
    return this->GetData() == elem ? 0 : LinkList::Locate(elem);
}

bool LinkListWithoutHead::Destroy() {
    this->SetData(DEFAULTELEM);
    return LinkList::Destroy();
}
