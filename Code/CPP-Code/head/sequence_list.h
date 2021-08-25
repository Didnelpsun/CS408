#include <cstdlib>
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
public:
    // 设置数据
    bool SetData(element_type* elem);
    bool SetData(int index, element_type elem);
    // 获取数据
    element_type* GetData() const;
    element_type GetData(int index) const;
    // 长度自加1
    bool SetLength();
    // 设置长度
    bool SetLength(int length);
    // 设置长度
    int GetLength() const;
    // 构造函数
    SequenceList();
    // 插入函数
    virtual bool Insert(int index, element_type elem) = 0;
    // 打印函数
    bool Print() const;
    // 循环插入函数
    bool LoopInsert(element_type *elem, int index, int length);
    // 删除函数
    element_type Delete(int index);
    // 多个删除函数
    element_type* LoopDelete(int index, int length);
    // 按位获取元素
    element_type GetElem(int index) const;
    // 按值获取元素
    int Locate(element_type elem) const;
    // 判空
    bool Empty() const;
    // 销毁
    bool Destroy() const;
};

// 静态顺序表
class StaticSequenceList: public SequenceList{
public:
    // 构造函数
    StaticSequenceList();
    // 插入函数
    bool Insert(int index, element_type elem) override;
};

// 动态顺序表
class DynamicSequenceList: public SequenceList{
private:
    // 已分配的最大容量
    int _max_size{};
public:
    // 设置最大容量
    bool SetMaxSize(int length);
    // 获取最大容量
    int GetMaxSize();
    // 构造函数
    DynamicSequenceList();
    // 插入函数
    bool Insert(int index, element_type elem) override;

private:
    // 分配其他地址增长动态顺序表的数据空间长度
    bool OtherIncrease(int len);
    // 重新分配地址增长动态顺序表的数据空间长度
    bool ReIncrease(int len);
};

bool SequenceList::SetData(element_type* elem) {
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
    this->_length ++;
    return true;
}

bool SequenceList::SetLength(int length) {
    this->_length = length;
    return true;
}

int SequenceList::GetLength() const {
    return this->_length;
}

SequenceList::SequenceList() {
    this->SetLength(0);
}

StaticSequenceList::StaticSequenceList() : SequenceList() {
    this->SetData((element_type*)malloc(MAXSIZE * sizeof(element_type)));
}

bool DynamicSequenceList::SetMaxSize(int length) {
    this->_max_size = length;
    return true;
}

int DynamicSequenceList::GetMaxSize() {
    return this->_max_size;
}

DynamicSequenceList::DynamicSequenceList() : SequenceList() {
    // 初初始化动态顺序表长度为0
    this->SetMaxSize(0);
    // 申请一片连续的存储空间
    auto* space = (element_type*)malloc(MAXSIZE * sizeof(element_type));
    if (space) {
        this->SetData(space);
        this->SetMaxSize(MAXSIZE);
    }
    else {
        cout << "InitSequenceList:分配空间失败！" << endl;
    }
}

bool SequenceList::Print() const {
    for (int i = 0; i < this->GetLength(); i++) {
        cout << "第" << i + 1 << "个元素值为" << this->GetData(i) << endl;
    }
    return true;
}

bool DynamicSequenceList::OtherIncrease(int len) {
    if (len <= 0) {
        cout << "OtherIncrease:申请空间应该大于0！" << endl;
        return false;
    }
    // 申请一片连续的存储空间
    int new_length = this->GetMaxSize() + len;
    auto* space = (element_type*)malloc(new_length * sizeof(element_type));
    if (space) {
        // 建立中间变量
        this->SetData(space);
        element_type* temp = this->GetData();
        for (int i = 0; i < this->GetLength(); i++) {
            this->SetData(i, temp[i]);
        }
        this->SetMaxSize(new_length);
        free(temp);
        return true;
    }
    else {
        cout << "OtherIncrease:重新分配空间失败！" << endl;
        return false;
    }
}

bool DynamicSequenceList::ReIncrease(int length) {
    if (length <= 0) {
        cout << "ReIncrease:申请空间应该大于0！" << endl;
        return false;
    }
    // 申请一片连续的存储空间
    int new_length = this->GetMaxSize() + length;
    auto* space = (element_type*)realloc(this->GetData(), new_length * sizeof(element_type));
    if (space) {
        this->SetData(space);
        this->SetMaxSize(this->GetMaxSize()+length);
        return true;
    }
    else {
        this->SetMaxSize(0);
        this->SetLength(0);
        cout << "ReIncrease:分配其他地址空间失败！" << endl;
        return false;
    }
}

bool StaticSequenceList::Insert(int index, element_type elem) {
    // 当静态顺序表已经满了就不能插入任何元素
    if (this->GetLength() >= MAXSIZE) {
        cout << "Insert:静态顺序表空间不足，插入失败！" << endl;
        return false;
    }
    // 索引位置从0开始，所以可以插入的范围是0到list->length
    if (index > this->GetLength() || index < 0) {
        cout << "Insert:插入索引" << index << "超过索引范围！" << endl;
        return false;
    }
    // 从最后一个元素开始交换后移，list->length是空的
    for (int i = this->GetLength(); i > index; i--) {
        this->SetData(i, this->GetData(i-1));
    }
    this->SetData(index, elem);
    this->SetLength();
    return true;
}

bool DynamicSequenceList::Insert(int index, element_type elem) {
    if (index > this->GetLength() || index < 0) {
        cout << "Insert:插入索引" << index << "超过索引范围！" << endl;
        return false;
    }
    // 当动态顺序表已经满了，需要新增一个位置
    // 为了避免索引无效而多增加一个空间，所以放在检查索引值的后面
    if (this->GetLength() >= MAXSIZE) {
        bool result = this->ReIncrease(1);
        if (!result) {
            cout << "Insert:申请空间失败！" << endl;
            return false;
        }
    }
    for (int i = this->GetLength(); i > index; i--) {
        this->SetData(i, this->GetData(i-1));
    }
    this->SetData(index, elem);
    this->SetLength();
    return true;
}

bool SequenceList::LoopInsert(element_type *elem, int index, int length) {
    for (int i = 0; i < length; i++) {
        bool result = this->Insert(i, elem[i + index]);
        if (!result) {
            cout << "LoopInsert:循环插入失败！" << endl;
            return false;
        }
    }
    return true;
}

element_type SequenceList::Delete(int index) {
    if (index >= this->GetLength() || index < 0) {
        cout << "Delete:删除索引" << index << "超过索引范围！" << endl;
        return false;
    }
    for (int i = index; i < this->GetLength(); i++) {
        this->SetData(i, this->GetData(i+1));
    }
    this->SetLength(this->GetLength()-1);
    return this->GetData(index);
}

element_type* SequenceList::LoopDelete(int index, int length) {
    if (index + length > this->GetLength() || index < 0) {
        cout << "LoopDelete:删除索引" << index + length << "超过索引范围！" << endl;
        return false;
    }
    auto* elem = (element_type*)malloc(length * sizeof(element_type));
    if (elem) {
        for (int i = index; i <= this->GetLength() - length; i++) {
            if (i < index + length) {
                elem[i - index] = this->GetData(i);
            }
            this->SetData(i, this->GetData(i + length));
        }
        this->SetLength(this->GetLength() - length);
    }
    else {
        cout << "LoopDelete:申请空间失败！" << endl;
    }
    return elem;
}

element_type SequenceList::GetElem(int index) const {
    if (index >= this->GetLength() || index < 0) {
        cout << "GetElem:查找索引" << index << "超过索引范围！" << endl;
        return DEFAULTDATA;
    }
    return this->GetData(index);
}


int SequenceList::Locate(element_type elem) const {
    for (int i = 0; i < this->GetLength(); i++) {
        if (this->GetData(i) == elem) {
            return i;
        }
    }
    cout << "Locate:未能定位到对应值的元素！" << endl;
    return -1;
}

bool SequenceList::Empty() const {
    if (this->GetLength() == 0) {
        return false;
    }
    else {
        return true;
    }
}

bool SequenceList::Destroy() const {
    if (this->GetData()) {
        free(this->GetData());
    }
    return true;
}

