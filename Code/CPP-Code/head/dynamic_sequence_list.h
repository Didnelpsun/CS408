#include "sequence_list.h"

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
