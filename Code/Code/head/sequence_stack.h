#include "head.h"

// 顺序栈
typedef struct SequenceStack {
    // 栈内元素
    element_type *data;
    // 栈顶指针
    int top;
    // 最大容量
    int max_size;
} SequenceStack;

// 初始化
bool InitSequenceStack(SequenceStack &stack) {
    stack.data = (element_type *) malloc(sizeof(element_type) * MAXSIZE);
    stack.top = -1;
    stack.max_size = MAXSIZE;
    return true;
}

bool InitSequenceStack(SequenceStack &stack, int max_size) {
    stack.data = (element_type *) malloc(sizeof(element_type) * max_size);
    stack.top = -1;
    stack.max_size = max_size;
    return true;
}

SequenceStack InitSequenceStack(){
    auto* stack = (SequenceStack*) malloc(sizeof(SequenceStack));
    stack->data = (element_type *) malloc(sizeof(element_type) * MAXSIZE);
    stack->top = -1;
    stack->max_size = MAXSIZE;
    return (SequenceStack &) stack;
}

SequenceStack InitSequenceStack(int max_size){
    auto* stack = (SequenceStack*) malloc(sizeof(SequenceStack));
    stack->data = (element_type *) malloc(sizeof(element_type) * max_size);
    stack->top = -1;
    stack->max_size = max_size;
    return (SequenceStack &) stack;
}

// 判空
bool EmptySequenceStack(SequenceStack stack) {
    return stack.top == -1;
}

// 判满
bool FullSequenceStack(SequenceStack stack) {
    return stack.top == stack.max_size - 1;
}

// 栈长
int LengthSequenceStack(SequenceStack stack) {
    return stack.top + 1;
}

// 进栈
bool PushSequenceStack(SequenceStack &stack, element_type elem){
    if(FullSequenceStack(stack)){
        printf("PushSequenceStack:栈满无法进栈！\n");
        return false;
    }
    // 先自加再进栈
    stack.data[++stack.top] = elem;
    return true;
}

// 出栈
element_type PopSequenceStack(SequenceStack &stack){
    if(EmptySequenceStack(stack)){
        printf("PopSequenceStack:栈空无法出栈！\n");
        return DEFAULTELEM;
    }
    // 先出栈再自减
    return stack.data[stack.top--];
}

// 读栈顶
element_type TopSequenceStack(SequenceStack stack){
    if(EmptySequenceStack(stack)){
        printf("TopSequenceStack:栈空无法读栈顶元素！\n");
        return DEFAULTELEM;
    }
    return stack.data[stack.top];
}