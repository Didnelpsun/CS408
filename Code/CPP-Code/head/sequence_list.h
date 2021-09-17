#include <iostream>
#include "head.h"

#pragma warning(disable:6385)
#pragma warning(disable:6386)

using namespace std;

// 顺序表
class SequenceList {
private:
    // 数据
    element_type *_data{};
    // 长度
    int _length{};
    // 最大容量
    int _max_size{};
public:
    // 设置数据
    bool SetData();

    bool SetData(int max_size);

    bool SetData(element_type *elem);

    bool SetData(int index, element_type elem);

    // 获取数据
    element_type *GetData() const;

    element_type GetData(int index) const;

    // 长度自加1
    bool SetLength();

    // 设置长度
    bool SetLength(int length);

    // 获取长度
    int GetLength() const;

    // 设置最大容量
    bool SetMaxSize();

    bool SetMaxSize(int max_size);

    // 获取最大容量
    int GetMaxSize() const;

    // 构造函数
    SequenceList();

    explicit SequenceList(int max_size);

    // 插入函数
    virtual bool Insert(int index, element_type elem) = 0;

    // 打印函数
    bool Print() const;

    // 循环插入函数
    bool LoopInsert(element_type *elem, int index, int length);

    // 删除函数
    element_type Delete(int index);

    // 多个删除函数
    element_type *LoopDelete(int index, int length);

    // 按位获取元素
    element_type GetElem(int index) const;

    // 按值获取元素
    int Locate(element_type elem) const;

    // 判空
    bool Empty() const;

    // 销毁
    bool Destroy() const;
};

bool SequenceList::SetData() {
    this->_data = new element_type[MAXSIZE];
    return true;
}

bool SequenceList::SetData(int max_size) {
    this->_data = new element_type[max_size];
    return true;
}

bool SequenceList::SetData(element_type *elem) {
    this->_data = elem;
    return true;
}

bool SequenceList::SetData(int index, element_type elem) {
    this->_data[index] = elem;
    return true;
}

element_type *SequenceList::GetData() const {
    return this->_data;
}

element_type SequenceList::GetData(int index) const {
    return this->_data[index];
}

bool SequenceList::SetLength() {
    this->_length++;
    return true;
}

bool SequenceList::SetLength(int length) {
    this->_length = length;
    return true;
}

int SequenceList::GetLength() const {
    return this->_length;
}

bool SequenceList::SetMaxSize() {
    this->_max_size = MAXSIZE;
    return true;
}

bool SequenceList::SetMaxSize(int max_size) {
    this->_max_size = max_size;
    return true;
}

int SequenceList::GetMaxSize() const {
    return this->_max_size;
}

SequenceList::SequenceList() {
    this->SetData();
    this->SetMaxSize();
    this->SetLength(0);
}

SequenceList::SequenceList(int max_size) {
    this->SetData(max_size);
    this->SetMaxSize(max_size);
    this->SetLength(0);
}

bool SequenceList::Print() const {
    for (int i = 0; i < this->GetLength(); i++) {
        // cout << "第" << i << "个元素值为" << this->GetData(i) << endl;
        cout << "index: " << i << " -> value: " << this->GetData(i) << endl;
    }
    return true;
}

bool SequenceList::LoopInsert(element_type *elem, int index, int length) {
    for (int i = 0; i < length; i++) {
        bool result = this->Insert(i, elem[i + index]);
        if (!result) {
            // cout << "LoopInsert:循环插入失败！" << endl;
            cout << "LoopInsert:Loop insert failed!" << endl;
            return false;
        }
    }
    return true;
}

element_type SequenceList::Delete(int index) {
    if (index >= this->GetLength() || index < 0) {
        // cout << "Delete:删除索引" << index << "超过索引范围！" << endl;
        cout << "Delete:Delete index value " << index << " is out of range!" << endl;
        return false;
    }
    for (int i = index; i < this->GetLength(); i++) {
        this->SetData(i, this->GetData(i + 1));
    }
    this->SetLength(this->GetLength() - 1);
    return this->GetData(index);
}

element_type *SequenceList::LoopDelete(int index, int length) {
    if (index + length > this->GetLength() || index < 0) {
        // cout << "LoopDelete:删除索引" << index + length << "超过索引范围！" << endl;
        cout << "LoopDelete:Loop Delete index value " << index + length << " is out of range!" << endl;
        return nullptr;
    }
    auto *elem = new element_type[length];
    for (int i = index; i <= this->GetLength() - length; i++) {
        if (i < index + length) {
            elem[i - index] = this->GetData(i);
        }
        this->SetData(i, this->GetData(i + length));
    }
    this->SetLength(this->GetLength() - length);
    return elem;
}

element_type SequenceList::GetElem(int index) const {
    if (index >= this->GetLength() || index < 0) {
        // cout << "GetElem:查找索引" << index << "超过索引范围！" << endl;
        cout << "GetElem:The index " << index << " is out of range!" << endl;
        return DEFAULTELEM;
    }
    return this->GetData(index);
}


int SequenceList::Locate(element_type elem) const {
    for (int i = 0; i < this->GetLength(); i++) {
        if (this->GetData(i) == elem) {
            return i;
        }
    }
    // cout << "Locate:未能定位到对应值的元素！" << endl;
    cout << "Locate:Can't locate the element with value " << elem << " !" << endl;
    return -1;
}

bool SequenceList::Empty() const {
    return this->GetLength() == 0;
}

bool SequenceList::Destroy() const {
    if (this->GetData()) {
        free(this->GetData());
    }
    return true;
}

// 静态顺序表
class StaticSequenceList : public SequenceList {
public:
    // 构造函数
    StaticSequenceList();

    explicit StaticSequenceList(int max_size);

    // 插入函数
    bool Insert(int index, element_type elem) override;
};

StaticSequenceList::StaticSequenceList() : SequenceList() {

}

StaticSequenceList::StaticSequenceList(int max_size) : SequenceList(max_size) {
}

bool StaticSequenceList::Insert(int index, element_type elem) {
    // 当静态顺序表已经满了就不能插入任何元素
    if (this->GetLength() >= this->GetMaxSize()) {
        // cout << "Insert:静态顺序表空间不足，插入失败！" << endl;
        cout << "Insert:The space size of " << this->GetMaxSize() << " is not enough!" << endl;
        return false;
    }
    // 索引位置从0开始，所以可以插入的范围是0到list->length
    if (index > this->GetLength() || index < 0) {
        // cout << "Insert:插入索引" << index << "超过索引范围！" << endl;
        cout << "Insert:Insert index value " << index << " is out of range!" << endl;
        return false;
    }
    // 从最后一个元素开始交换后移，list->length是空的
    for (int i = this->GetLength(); i > index; i--) {
        this->SetData(i, this->GetData(i - 1));
    }
    this->SetData(index, elem);
    this->SetLength();
    return true;
}

// 动态顺序表
class DynamicSequenceList : public SequenceList {
public:

    // 构造函数
    DynamicSequenceList();

    explicit DynamicSequenceList(int max_size);

    // 插入函数
    bool Insert(int index, element_type elem) override;

private:
    // 分配其他地址增长动态顺序表的数据空间长度
    bool OtherIncrease(int len);

    // 重新分配地址增长动态顺序表的数据空间长度
    bool ReIncrease(int len);
};

DynamicSequenceList::DynamicSequenceList() : SequenceList() {
}

DynamicSequenceList::DynamicSequenceList(int max_size) : SequenceList(max_size) {
}

bool DynamicSequenceList::OtherIncrease(int length) {
    if (length <= 0) {
        // cout << "OtherIncrease:申请空间应该大于0！" << endl;
        cout << "OtherIncrease:The length " << length << " should larger than 0!" << endl;
        return false;
    }
    // 申请一片连续的存储空间
    int new_length = this->GetMaxSize() + length;
    auto *space = new element_type[new_length];
    // 建立中间变量
    this->SetData(space);
    element_type *temp = this->GetData();
    for (int i = 0; i < this->GetLength(); i++) {
        this->SetData(i, temp[i]);
    }
    this->SetMaxSize(new_length);
    // delete(temp);
    return true;
}

bool DynamicSequenceList::ReIncrease(int length) {
    if (length <= 0) {
        // cout << "ReIncrease:申请空间应该大于0！" << endl;
        cout << "ReIncrease:The length " << length << " should larger than 0!" << endl;
        return false;
    }
    // 申请一片连续的存储空间
    int new_length = this->GetMaxSize() + length;
    auto *space = (element_type *) realloc(this->GetData(), new_length * sizeof(element_type));
    if (space) {
        this->SetData(space);
        this->SetMaxSize(this->GetMaxSize() + length);
        return true;
    } else {
        this->SetMaxSize(0);
        this->SetLength(0);
        cout << "ReIncrease:分配其他地址空间失败！" << endl;
        return false;
    }
}

bool DynamicSequenceList::Insert(int index, element_type elem) {
    if (index > this->GetLength() || index < 0) {
        // cout << "Insert:插入索引" << index << "超过索引范围！" << endl;
        cout << "Insert:Insert index value " << index << " is out of range!" << endl;
        return false;
    }
    // 当动态顺序表已经满了，需要新增一个位置
    // 为了避免索引无效而多增加一个空间，所以放在检查索引值的后面
    if (this->GetLength() >= this->GetMaxSize()) {
        this->ReIncrease(1);
    }
    for (int i = this->GetLength(); i > index; i--) {
        this->SetData(i, this->GetData(i - 1));
    }
    this->SetData(index, elem);
    this->SetLength();
    return true;
}
