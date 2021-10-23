#include "sequence_list.h"

// 静态顺序表
class StaticSequenceList : public SequenceList {
public:
    // 构造函数
    StaticSequenceList();

    explicit StaticSequenceList(int max_size);

    // 插入函数
    bool Insert(int index, element_type elem) override;
};

StaticSequenceList::StaticSequenceList() :SequenceList() {

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