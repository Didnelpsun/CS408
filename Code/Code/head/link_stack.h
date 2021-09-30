#include "head.h"

// 链栈
typedef struct LinkStackNode{
    // 数据
    element_type data;
    // 指针
    LinkStackNode *next;
} *LinkStack;

// 初始化
LinkStack InitLinkStack(){
    auto stack = (LinkStack) malloc(sizeof(LinkStack));
    stack->data = DEFAULTELEM;
    stack->next = nullptr;
    return stack;
}

bool InitLinkStack(LinkStack &stack){
    stack->data = DEFAULTELEM;
    stack->next = nullptr;
    return true;
}

// 判空
bool EmptyLinkStack(LinkStack stack){
    return stack->data == DEFAULTELEM;
};