#include "head.h"

// ��ջ
typedef struct LinkStackNode{
    // ����
    element_type data;
    // ָ��
    LinkStackNode *next;
} *LinkStack;

// ��ʼ��
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

// �п�
bool EmptyLinkStack(LinkStack stack){
    return stack->data == DEFAULTELEM;
};