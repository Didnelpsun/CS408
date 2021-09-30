#include "head.h"

typedef struct {
    // ����
    element_type *data;
    // ջ��ָ��
    int top_left, top_right;
    // �������
    int max_size;
} ShareStack;

// ��ʼ��
bool InitShareStack(ShareStack &stack) {
    stack.data = (element_type *) malloc(sizeof(element_type) * MAXSIZE);
    stack.top_left = -1;
    stack.top_right = MAXSIZE;
    stack.max_size = MAXSIZE;
    return true;
}

bool InitShareStack(ShareStack &stack, int max_size) {
    stack.data = (element_type *) malloc(sizeof(element_type) * max_size);
    stack.top_left = -1;
    stack.top_right = max_size;
    stack.max_size = max_size;
    return true;
}

ShareStack InitShareStack() {
    auto *stack = (ShareStack *) malloc(sizeof(ShareStack));
    stack->data = (element_type *) malloc(sizeof(element_type) * MAXSIZE);
    stack->top_left = -1;
    stack->top_right = MAXSIZE;
    stack->max_size = MAXSIZE;
    return (ShareStack &) stack;
}

ShareStack InitShareStack(int max_size) {
    auto *stack = (ShareStack *) malloc(sizeof(ShareStack));
    stack->data = (element_type *) malloc(sizeof(element_type) * max_size);
    stack->top_left = -1;
    stack->top_right = max_size;
    stack->max_size = max_size;
    return (ShareStack &) stack;
}

// �����
bool EmptyLeftShareStack(ShareStack stack){
    return stack.top_left == -1;
}

// ���ҿ�
bool EmptyRightShareStack(ShareStack stack){
    return stack.top_right == stack.max_size;
}

// ����
bool FullShareStack(ShareStack stack){
    return stack.top_right - stack.top_left == 1;
}

// ��ջ��
int LengthLeftShareStack(ShareStack stack){
    return stack.top_left + 1;
}

// ��ջ��
int LengthRightShareStack(ShareStack stack){
    return stack.max_size - stack.top_right;
}

// ���ջ
bool PushLeftShareStack(ShareStack &stack, element_type elem){
    if(FullShareStack(stack)){
        printf("PushLeftShareStack:ջ���޷���ջ��\n");
        return false;
    }
    stack.data[++stack.top_left] = elem;
    return true;
}

// �ҽ�ջ
bool PushRightShareStack(ShareStack &stack, element_type elem){
    if(FullShareStack(stack)){
        printf("PushRightShareStack:ջ���޷���ջ��\n");
        return false;
    }
    stack.data[--stack.top_right] = elem;
    return true;
}

// ���ջ
element_type PopLeftShareStack(ShareStack &stack){
    if(EmptyLeftShareStack(stack)){
        printf("PopLeftShareStack:ջ���޷���ջ��\n");
        return DEFAULTELEM;
    }
    element_type elem = stack.data[stack.top_left];
    stack.top_left--;
    return elem;
}

// �ҳ�ջ
element_type PopRightShareStack(ShareStack &stack){
    if(EmptyLeftShareStack(stack)){
        printf("PopRightShareStack:ջ���޷���ջ��\n");
        return DEFAULTELEM;
    }
    element_type elem = stack.data[stack.top_right];
    stack.top_left++;
    return elem;
}

// ��ȡ���ײ�
element_type TopLeftShareStack(ShareStack stack){
    if(EmptyLeftShareStack(stack)){
        printf("PopLeftShareStack:ջ���޷���ջ��\n");
        return DEFAULTELEM;
    }
    return stack.data[stack.top_left];
}

// ��ȡ���ײ�
element_type TopRightShareStack(ShareStack stack){
    if(EmptyLeftShareStack(stack)){
        printf("TopRightShareStack:ջ���޷���ջ��\n");
        return DEFAULTELEM;
    }
    return stack.data[stack.top_right];
}