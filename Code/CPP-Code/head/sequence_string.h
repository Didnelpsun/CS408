#include "head.h"

// 顺序串
class SequenceString {
private:
    // 数据
    char *_data{};
    // 长度
    int _length{};
    // 最大容量
    int _max_size{};
public:
    // 设置数据
    bool SetData();

    bool SetData(int max_size);

    bool SetData(char *character);

    bool SetData(int index, char character);

    // 获取数据
    char *GetData();

    char GetData(int index);

    // 长度自加
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
    SequenceString();

    explicit SequenceString(int max_size);

    // 暴力模式匹配
    int LocateSimple(SequenceString string);

    // 销毁
    bool Destroy();
};

bool SequenceString::SetData() {
    this->_data = new char[MAXSIZE];
    return true;
}

bool SequenceString::SetData(int max_size) {
    this->_data = new char[max_size];
    return true;
}

bool SequenceString::SetData(char *character) {
    this->_data = character;
    return true;
}

bool SequenceString::SetData(int index, char character) {
    this->_data[index] = character;
    return true;
}

char *SequenceString::GetData() {
    return this->_data;
}

char SequenceString::GetData(int index) {
    return this->_data[index];
}

bool SequenceString::SetLength() {
    this->_length++;
    return true;
}

bool SequenceString::SetLength(int length) {
    this->_length = length;
    return true;
}

int SequenceString::GetLength() const {
    return this->_length;
}

bool SequenceString::SetMaxSize() {
    this->_max_size = MAXSIZE;
    return true;
}

bool SequenceString::SetMaxSize(int max_size) {
    this->_max_size = max_size;
    return true;
}

int SequenceString::GetMaxSize() const {
    return this->_max_size;
}

SequenceString::SequenceString() {
    this->SetData();
    this->SetMaxSize();
    this->SetLength(0);
}

SequenceString::SequenceString(int max_size) {
    this->SetData(max_size);
    this->SetMaxSize();
    this->SetLength(0);
}

int SequenceString::LocateSimple(SequenceString string) {
    int i = 0, j = 0;
    while (i < this->GetLength() && j < string.GetLength()) {
        // 匹配就继续后移
        if (this->GetData(i) == string.GetData(j)) {
            i++;
            j++;
        }
            // 不匹配就退回
        else {
            i = i - j + 1;
            j = 0;
        }
    }
    if (j >= string.GetLength()) {
        return i - string.GetLength();
    }
    return -1;
}

bool SequenceString::Destroy() {
    delete (this->GetData());
    this->SetLength(0);
    this->SetMaxSize(0);
    this->SetData(nullptr);
    return true;
}


