#include "head.h"

// 顺序队列
class SequenceQueue {
private:
    // 数据
    element_type *_data{};
    // 队头队尾指针
    int _front{}, _rear{};
    // 队列最大容量
    int _max_size{};
public:
    // 设置数据
    bool SetData();

    bool SetData(int max_size);

    bool SetData(element_type *elem);

    bool SetData(int index, element_type elem);

    // 获取数据
    element_type *GetData();

    element_type GetData(int index);

    // 队头自加
    bool SetFront();

    // 设置队头
    bool SetFront(int front);

    // 获取队头
    int GetFront() const;

    // 队尾自加
    bool SetRear();

    // 设置队尾
    bool SetRear(int rear);

    // 获取队尾
    int GetRear() const;

    // 设置最大容量
    bool SetMaxSize();

    bool SetMaxSize(int max_size);

    // 获取最大容量
    int GetMaxSize() const;

    // 构造函数
    SequenceQueue();

    explicit SequenceQueue(int max_size);

    // 判空
    bool Empty() const;

    // 判满
    bool Full() const;

    // 循环队列判满
    bool FullCircular() const;

    // 进队
    bool Enter(element_type elem);

    // 循环队列进队
    bool EnterCircular(element_type elem);

    // 出队
    element_type Depart();

    // 循环队列出队
    element_type DepartCircular();

    // 获取队长
    int Length() const;

    // 读队头
    element_type Head();
};

bool SequenceQueue::SetData() {
    this->_data = new element_type[MAXSIZE];
    return true;
}

bool SequenceQueue::SetData(int max_size) {
    this->_data = new element_type[max_size];
    return true;
}

bool SequenceQueue::SetData(element_type *elem) {
    this->_data = elem;
    return true;
}

bool SequenceQueue::SetData(int index, element_type elem) {
    this->_data[index] = elem;
    return true;
}

element_type *SequenceQueue::GetData() {
    return this->_data;
}

element_type SequenceQueue::GetData(int index) {
    return this->_data[index];
}

bool SequenceQueue::SetFront() {
    this->_front++;
    return true;
}

bool SequenceQueue::SetFront(int front) {
    this->_front = front;
    return true;
}

int SequenceQueue::GetFront() const {
    return this->_front;
}

bool SequenceQueue::SetRear() {
    this->_rear++;
    return true;
}

bool SequenceQueue::SetRear(int rear) {
    this->_rear = rear;
    return true;
}

int SequenceQueue::GetRear() const {
    return this->_rear;
}

bool SequenceQueue::SetMaxSize() {
    this->_max_size = MAXSIZE;
    return true;
}

bool SequenceQueue::SetMaxSize(int max_size) {
    this->_max_size = max_size;
    return true;
}

int SequenceQueue::GetMaxSize() const {
    return this->_max_size;
}

SequenceQueue::SequenceQueue() {
    this->SetData();
    this->SetMaxSize();
    this->SetFront(0);
    this->SetRear(0);
}

SequenceQueue::SequenceQueue(int max_size) {
    this->SetData(max_size);
    this->SetMaxSize(max_size);
    this->SetFront(0);
    this->SetRear(0);
}

bool SequenceQueue::Empty() const {
    return this->GetFront() == this->GetRear();
}

bool SequenceQueue::Full() const {
    return this->GetFront() == this->GetMaxSize();
}

bool SequenceQueue::FullCircular() const {
    return (this->GetRear() + 1) % this->GetMaxSize() == this->GetFront();
}

bool SequenceQueue::Enter(element_type elem) {
    if (this->Full()) {
        cout << "Enter:The queue is full!" << endl;
        return false;
    }
    this->SetData(this->GetRear(), elem);
    this->SetRear();
    return true;
}

bool SequenceQueue::EnterCircular(element_type elem) {
    if (this->FullCircular()) {
        cout << "EnterCircular:The queue is full!" << endl;
        return false;
    }
    this->SetData(this->GetRear(), elem);
    this->SetRear((this->GetRear() + 1) % this->GetMaxSize());
    return true;
}

element_type SequenceQueue::Depart() {
    if (this->Empty()) {
        cout << "Depart:The queue is empty!" << endl;
        return DEFAULTELEM;
    }
    element_type temp = this->GetData(this->GetFront());
    this->SetFront();
    return temp;
}

element_type SequenceQueue::DepartCircular() {
    if (this->Empty()) {
        cout << "DepartCircular:The queue is empty!" << endl;
        return DEFAULTELEM;
    }
    element_type temp = this->GetData(this->GetFront());
    this->SetFront((this->GetFront() + 1) % this->GetMaxSize());
    return temp;
}

int SequenceQueue::Length() const {
    return (this->GetRear() - this->GetFront() + this->GetMaxSize()) % this->GetMaxSize();
}

element_type SequenceQueue::Head() {
    if (this->Empty()) {
        cout << "Head:The queue is empty!" << endl;
        return DEFAULTELEM;
    }
    return this->GetData(this->GetFront());
}