#include "link_list.h"

class LinkListWithoutHead : public LinkList
{
private:
    // 数据
    element_type _data{};

public:
    // 设置数据
    bool SetData(element_type elem);

    // 获取数据
    element_type GetData() const;

    element_type GetData(int index);

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

    // 获取最大值
    int Max();

    // 获取最小值
    int Min();
};

bool LinkListWithoutHead::SetData(element_type elem)
{
    this->_data = elem;
    return true;
}

element_type LinkListWithoutHead::GetData() const
{
    return this->_data;
}

element_type LinkListWithoutHead::GetData(int index)
{
    if (index < 0 || index >= this->GetLength() || this->GetLength() == 0)
    {
        cout << "GetData:Can't get the element by index of " << index << " !" << endl;
        return DEFAULTELEM;
    }
    if (index == 0)
        return this->GetData();
    LinkListNode *node = this->GetNext();
    for (int i = 1; i < index; i++)
    {
        node = node->GetNext();
    }
    return node->GetData();
}

LinkListWithoutHead::LinkListWithoutHead()
{
    this->SetType(false);
    this->SetData(DEFAULTELEM);
}

bool LinkListWithoutHead::Print()
{
    int i = 0;
    if (this->GetLength() == 0)
    {
        return true;
    }
    // cout << "第" << i << "个元素值为" << this->GetData() << endl;
    cout << "index: " << i << " -> value: " << this->GetData() << endl;
    // 当前遍历指针
    LinkListNode *node = this->GetNext();
    while (node != nullptr)
    {
        i++;
        // cout << "第" << i << "个元素值为" << node->GetData() << endl;
        cout << "index: " << i << " -> value: " << node->GetData() << endl;
        node = node->GetNext();
    }
    return true;
}

bool LinkListWithoutHead::Insert(int index, element_type elem)
{
    if (index < 0)
    {
        // cout << "Insert:插入索引值" << index << "过小！" << endl;
        cout << "Insert:Insert index value " << index << " is too small!" << endl;
        return false;
    }
    if (index == 0)
    {
        if (this->GetLength() == 0)
        {
            this->SetData(elem);
            this->SetLength();
        }
        else
        {
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
    if (node == nullptr)
    {
        this->SetLength();
        this->SetNext(new_node);
        return true;
    }
    // 循环遍历到达指定索引号的单链表的结点
    // 条件是当前结点的下一个不为空且索引号到达，所到达的结点一定不是空结点
    while (node->GetNext() != nullptr && i < index - 1)
    {
        node = node->GetNext();
        i++;
    }
    // 如果此时i小于index-1，表示遍历完还没有到达对应的索引
    if (i < index - 1)
    {
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

element_type *LinkListWithoutHead::Delete(int index, int length)
{
    auto *data = new element_type[length];
    if (index < 0)
    {
        // cout << "Delete:删除索引值" << index << "过小！" << endl;
        cout << "Delete:Delete index value " << index << " is too small!";
        return data;
    }
    if (length < 1)
    {
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
    if (this->GetData() == DEFAULTELEM)
    {
        // cout << "Delete:链表为空！" << endl;
        cout << "Delete:Link list is empty!" << endl;
        return data;
    }
    data[0] = this->GetData();
    // 循环遍历到达指定索引号的单链表的结点
    // 条件是当前结点的下一个不为空且索引号到达，所到达的结点一定不是空结点
    while (start->GetNext() != nullptr && i < index - 1)
    {
        start = start->GetNext();
        i++;
    }
    // 如果此时i小于index-1，表示遍历完还没有到达对应的索引
    if (i < index - 1)
    {
        // cout << "Delete:删除索引值" << index << "过大！" << endl;
        cout << "Delete:Delete index value " << index << " is too large!";
        return data;
    }
    // 从1开始遍历
    end = this->GetNext();
    for (int i = 1; i < index + length - 1; i++)
    {
        if (i >= index)
        {
            data[i - index] = end->GetData();
        }
        end = end->GetNext();
        if (end == nullptr)
        {
            // cout << "Delete:删除索引最大值" << index + length - 1 << "大于链表最大索引" << length - 1 << "！" << endl;
            cout << "Delete:Delete index value" << index + length - 1 << "is larger than link list's biggest index " << length - 1 << "!" << endl;
            return data;
        }
    }
    data[length - 1] = end->GetData();
    if (index == 0)
    {
        this->SetData(end->GetNext()->GetData());
        this->SetNext(end->GetNext()->GetNext());
    }
    if (index == 1)
    {
        this->SetNext(end->GetNext());
    }
    else
    {
        start->SetNext(end->GetNext());
    }
    this->SetLength(this->GetLength() - length);
    return data;
}

element_type LinkListWithoutHead::GetElem(int index)
{
    return index == 0 ? this->GetData() : LinkList::GetElem(index);
}

int LinkListWithoutHead::Locate(element_type elem)
{
    return this->GetData() == elem ? 0 : LinkList::Locate(elem);
}

bool LinkListWithoutHead::Destroy()
{
    this->SetData(DEFAULTELEM);
    return LinkList::Destroy();
}

int LinkListWithoutHead::Max()
{
    if (this->GetLength() == 0)
    {
        cout << "Max:The list is empty!" << endl;
        return -1;
    }
    element_type temp = this->GetData(0);
    int index = 0;
    for (int i = 1; i < this->GetLength(); i++)
    {
        if (this->GetData(i) > temp)
        {
            temp = this->GetData(i);
            index = i;
        }
    }
    return index;
}

int LinkListWithoutHead::Min()
{
    if (this->GetLength() == 0)
    {
        cout << "Min:The list is empty!" << endl;
        return -1;
    }
    element_type temp = this->GetData(0);
    int index = 0;
    for (int i = 1; i < this->GetLength(); i++)
    {
        if (this->GetData(i) < temp)
        {
            temp = this->GetData(i);
            index = i;
        }
    }
    return index;
}
