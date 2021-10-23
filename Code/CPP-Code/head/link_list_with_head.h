#include "link_list.h"

class LinkListWithHead : public LinkList
{
public:
    // 构造函数
    LinkListWithHead();

    // 获取数据
    element_type GetData(int index);

    // 打印
    bool Print() override;

    // 插入
    bool Insert(int index, element_type elem) override;

    // 删除
    element_type *Delete(int index, int length) override;

    // 获取最大值
    int Max();

    // 获取最小值
    int Min();
};

LinkListWithHead::LinkListWithHead()
{
    this->SetType(true);
};

element_type LinkListWithHead::GetData(int index)
{
    if (index <= 0 || index >= this->GetLength() || this->GetLength() == 0)
    {
        cout << "GetData:Can't get the element by index of " << index << " !" << endl;
        return DEFAULTELEM;
    }
    LinkListNode *node = this->GetNext();
    for (int i = 1; i < index; i++)
    {
        node = node->GetNext();
    }
    return node->GetData();
}

bool LinkListWithHead::Print()
{
    int i = 1;
    // cout << "第0个元素值为空" << endl;
    cout << "index: 0 -> value: NULL" << endl;
    if (this->GetLength() == 0)
    {
        return true;
    }
    // 当前遍历指针
    LinkListNode *node = this->GetNext();
    while (node != nullptr)
    {
        //        cout << "第" << i << "个元素值为" << node->GetData() << endl;
        cout << "index: " << i << " -> value: " << node->GetData() << endl;
        i++;
        node = node->GetNext();
    }
    return true;
}

bool LinkListWithHead::Insert(int index, element_type elem)
{
    if (index < 1)
    {
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
    if (node == nullptr)
    {
        this->SetNext(new_node);
        this->SetLength();
        return true;
    }
    // 当插入的是第一个节点
    if (index == 1)
    {
        new_node->SetNext(node);
        this->SetNext(new_node);
        this->SetLength();
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
    // 将node原来的后继给新的结点
    new_node->SetNext(node->GetNext());
    node->SetNext(new_node);
    this->SetLength();
    return true;
}

element_type *LinkListWithHead::Delete(int index, int length)
{
    auto *data = new element_type[length];
    if (index < 1)
    {
        // cout << "Delete:删除索引值" << index << "过小！" << endl;
        cout << "Delete:Delete index value " << index << " is too small!" << endl;
        return data;
    }
    if (length < 1)
    {
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
    if (start == nullptr)
    {
        // cout << "Delete:链表为空！" << endl;
        cout << "Delete:Link list is empty!" << endl;
        return data;
    }
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
        cout << "Delete:Delete index value " << index << " is too large!" << endl;
        return data;
    }
    // 此时i==index-1，start到达，求end
    end = start;
    for (int i = 0; i < length; i++)
    {
        data[i] = end->GetData();
        end = end->GetNext();
        if (end == nullptr)
        {
            // cout << "Delete:删除索引最大值" << index + length - 1 << "大于链表最大索引" << length - 1 << "！" << endl;
            cout << "Delete:Delete index value" << index + length - 1 << "is larger than link list's biggest index " << length - 1 << "!" << endl;
            return data;
        }
    }
    if (index == 1)
    {
        this->SetNext(end);
    }
    else
    {
        start->SetNext(end->GetNext());
    }
    this->SetLength(this->GetLength() - length);
    return data;
}

int LinkListWithHead::Max()
{
    if (this->GetLength() == 0)
    {
        cout << "Max:The list is empty!" << endl;
        return -1;
    }
    element_type temp = this->GetData(1);
    int index = 1;
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

int LinkListWithHead::Min()
{
    if (this->GetLength() == 0)
    {
        cout << "Min:The list is empty!" << endl;
        return -1;
    }
    element_type temp = this->GetData(1);
    int index = 1;
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