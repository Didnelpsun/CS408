#include "head.h"

// 共享栈
class ShareStack{
private:
    // 栈内元素
    element_type *_data{};
    // 栈顶指针，left从-1开始，right从MAXSIZE开始
    int _top_left{}, _top_right{};
    // 最大容量
    int _max_size{};
public:
    // 设置数据
    bool SetData();

    bool SetData(element_type *data);

    bool SetData(int max_size);

    bool SetData(int index, element_type elem);

    // 获取数据
    element_type * GetData();

    element_type GetData(int index);

    // 左栈顶指针自加
    bool SetTopLeft();

    // 左设置栈顶指针
    bool SetTopLeft(int top);

    // 左获取栈顶指针
    int GetTopLeft() const;

    // 右栈顶指针自减
    bool SetTopRight();

    // 右设置栈顶指针
    bool SetTopRight(int top);

    // 右获取栈顶指针
    int GetTopRight() const;

    // 设置最大容量
    bool SetMaxSize();

    bool SetMaxSize(int max_size);

    // 获取最大容量
    int GetMaxSize() const;

    // 构造函数
    ShareStack();

    explicit ShareStack(int max_size);

    // 判左栈空
    bool EmptyLeft() const;

    // 判右栈空
    bool EmptyRight() const;

    // 判栈满
    bool Full() const;

    // 左栈长
    int LengthLeft() const;

    // 右栈长
    int LengthRight() const;

    // 进左栈
    bool PushLeft(element_type elem);

    // 进右栈
    bool PushRight(element_type elem);

    // 出左栈
    element_type PopLeft();

    // 出右栈
    element_type PopRight();

    // 读左栈顶
    element_type TopLeft();

    // 读右栈顶
    element_type TopRight();
};

bool ShareStack::SetData() {
    this->_data = new element_type[MAXSIZE];
    return true;
}

bool ShareStack::SetData(element_type *data) {
    this->_data = data;
    return true;
}

bool ShareStack::SetData(int max_size) {
    this->_data =  new element_type [max_size];
    return true;
}

bool ShareStack::SetData(int index, element_type elem) {
    this->_data[index] = elem;
    return true;
}

element_type *ShareStack::GetData() {
    return this->_data;
}

element_type ShareStack::GetData(int index) {
    return this->_data[index];
}

bool ShareStack::SetTopLeft() {
    this->_top_left++;
    return true;
}

bool ShareStack::SetTopRight() {
    this->_top_right--;
    return true;
}

bool ShareStack::SetTopLeft(int top) {
    this->_top_left = top;
    return true;
}

bool ShareStack::SetTopRight(int top) {
    this->_top_right = top;
    return true;
}

int ShareStack::GetTopLeft() const {
    return this->_top_left;
}

int ShareStack::GetTopRight() const {
    return this->_top_right;
}

bool ShareStack::SetMaxSize() {
    this->_max_size = MAXSIZE;
    return true;
}

bool ShareStack::SetMaxSize(int max_size) {
    this->_max_size = max_size;
    return true;
}

int ShareStack::GetMaxSize() const {
    return this->_max_size;
}

ShareStack::ShareStack() {
    this->SetData();
    this->SetMaxSize();
    this->SetTopLeft(-1);
    this->SetTopRight(MAXSIZE);
}

ShareStack::ShareStack(int max_size) {
    this->SetData(max_size);
    this->SetMaxSize(max_size);
    this->SetTopLeft(-1);
    this->SetTopRight(max_size);
}

bool ShareStack::EmptyLeft() const {
    return this->GetTopLeft() == -1;
}

bool ShareStack::EmptyRight() const {
    return this->GetTopRight() == this->GetMaxSize();
}

bool ShareStack::Full() const {
    return this->GetTopRight() - this->GetTopLeft() == 1;
}

int ShareStack::LengthLeft() const {
    return this->GetTopLeft() + 1;
}

int ShareStack::LengthRight() const {
    return this->GetMaxSize() - this->GetTopRight();
}

bool ShareStack::PushLeft(element_type elem) {
    if (this->Full()) {
        // cout << "PushLeft:栈满无法进栈！" << endl;
        cout << "PushLeft:The stack is full!";
        return false;
    }
    this->SetTopLeft();
    this->SetData(this->GetTopLeft(), elem);
    return true;
}

bool ShareStack::PushRight(element_type elem) {
    if(this->Full()){
        // cout << "PushRight:栈满无法进栈！" << endl;
        cout << "PushRight:The stack is full!" << endl;
        return false;
    }this->SetTopRight();
    this->SetData(this->GetTopRight(), elem);
    return true;
}

element_type ShareStack::PopLeft() {
    if (this->EmptyLeft()) {
        // cout << "PopLeft:栈空无法出栈！" << endl;
        cout << "PopLeft:The stack is empty!" << endl;
        return DEFAULTELEM;
    }
    element_type temp = this->GetData(this->GetTopLeft());
    this->SetTopLeft(this->GetTopLeft() - 1);
    return temp;
}

element_type ShareStack::PopRight() {
    if (this->EmptyRight()) {
        // cout << "PopRight:栈空无法出栈！" << endl;
        cout << "PopRight:The stack is empty!" << endl;
        return DEFAULTELEM;
    }
    element_type temp = this->GetData(this->GetTopRight());
    this->SetTopRight(this->GetTopRight() + 1);
    return temp;
}

element_type ShareStack::TopLeft() {
    if (this->EmptyLeft()) {
        // cout << "TopLeft:栈空无法读栈顶元素！" << endl;
        cout << "TopLeft:The stack is empty!" << endl;
        return DEFAULTELEM;
    }
    return this->GetData(this->GetTopLeft());
}

element_type ShareStack::TopRight() {
    if (this->EmptyRight()) {
        // cout << "TopRight:栈空无法读栈顶元素！" << endl;
        cout << "TopRight:The stack is empty!" << endl;
        return DEFAULTELEM;
    }
    return this->GetData(this->GetTopRight());
}