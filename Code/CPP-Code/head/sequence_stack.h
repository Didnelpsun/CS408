#include "head.h"

using namespace std;

// 顺序栈
class SequenceStack {
private:
    // 栈内元素
    element_type *_data{};
    // 栈顶指针
    int _top{};
    // 最大容量
    int _max_size{};

    // 设置数据
    bool SetData(element_type *data);

    // 栈顶指针自加
    bool SetTop();

    // 设置栈顶指针
    bool SetTop(int top);

    // 获取栈顶指针
    int GetTop() const;

    // 设置最大容量
    bool SetMaxSize(int max_size);

public:

    // 获取最大容量
    int GetMaxSize() const;

    // 构造函数
    SequenceStack();

    explicit SequenceStack(int max_size);

    // 判空
    bool Empty() const;

    // 判满
    bool Full() const;

    // 栈长
    int Length() const;

    // 进栈
    bool Push(element_type elem);

    // 出栈
    element_type Pop();

    // 读栈顶
    element_type Top();
};

bool SequenceStack::SetData(element_type *data) {
    this->_data = data;
    return true;
}

bool SequenceStack::SetTop() {
    this->_top++;
    return true;
}

bool SequenceStack::SetTop(int top) {
    this->_top = top;
    return true;
}

int SequenceStack::GetTop() const {
    return this->_top;
}

bool SequenceStack::SetMaxSize(int max_size) {
    this->_max_size = max_size;
    return true;
}

int SequenceStack::GetMaxSize() const {
    return this->_max_size;
}

SequenceStack::SequenceStack() {
    this->SetData(new element_type[MAXSIZE]);
    this->SetTop(-1);
    this->SetMaxSize(MAXSIZE);
}

SequenceStack::SequenceStack(int max_size) {
    this->SetData(new element_type[max_size]);
    this->SetTop(-1);
    this->SetMaxSize(max_size);
}

bool SequenceStack::Empty() const {
    return this->GetTop() == -1;
}

bool SequenceStack::Full() const {
    return this->GetTop() == this->GetMaxSize() - 1;
}

int SequenceStack::Length() const {
    return this->GetTop() + 1;
}

bool SequenceStack::Push(element_type elem) {
    if (this->Full()) {
        cout << "Push:栈满无法进栈！" << endl;
        cout << "Push:The stack is full!" << endl;
        return false;
    }
    this->_data[this->SetTop()] = elem;
    return true;
}

element_type SequenceStack::Pop() {
    if (this->Empty()) {
        cout << "Pop:栈空无法出栈！" << endl;
        cout << "Pop:The stack is empty!" << endl;
        return DEFAULTELEM;
    }
    return this->_data[this->SetTop(this->GetTop() - 1)];
}

element_type SequenceStack::Top() {
    if (this->Empty()) {
        cout << "Top:栈空无法读栈顶元素！" << endl;
        cout << "Top:The stack is empty!" << endl;
        return DEFAULTELEM;
    }
    return this->_data[this->GetTop() - 1];
}
