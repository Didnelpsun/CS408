#include "head.h"

typedef struct {
    // 数据
    element_type *data;
    // 栈顶指针
    int top_left, top_right;
    // 最大容量
    int max_size;
} ShareStack;

// 初始化
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

// 判左空
bool EmptyLeftShareStack(ShareStack stack){
    return stack.top_left == -1;
}

// 判右空
bool EmptyRightShareStack(ShareStack stack){
    return stack.top_right == stack.max_size;
}

// 判满
bool FullShareStack(ShareStack stack){
    return stack.top_right - stack.top_left == 1;
}

// 左栈长
int LengthLeftShareStack(ShareStack stack){
    return stack.top_left + 1;
}

// 右栈长
int LengthRightShareStack(ShareStack stack){
    return stack.max_size - stack.top_right;
}

// 左进栈
bool PushLeftShareStack(ShareStack &stack, element_type elem){
    if(FullShareStack(stack)){
        printf("PushLeftShareStack:栈满无法进栈！\n");
        return false;
    }
    stack.data[++stack.top_left] = elem;
    return true;
}

// 右进栈
bool PushRightShareStack(ShareStack &stack, element_type elem){
    if(FullShareStack(stack)){
        printf("PushRightShareStack:栈满无法进栈！\n");
        return false;
    }
    stack.data[--stack.top_right] = elem;
    return true;
}

// 左出栈
element_type PopLeftShareStack(ShareStack &stack){
    if(EmptyLeftShareStack(stack)){
        printf("PopLeftShareStack:栈空无法出栈！\n");
        return DEFAULTELEM;
    }
    element_type elem = stack.data[stack.top_left];
    stack.top_left--;
    return elem;
}

// 右出栈
element_type PopRightShareStack(ShareStack &stack){
    if(EmptyLeftShareStack(stack)){
        printf("PopRightShareStack:栈空无法出栈！\n");
        return DEFAULTELEM;
    }
    element_type elem = stack.data[stack.top_right];
    stack.top_left++;
    return elem;
}

// 读取左首部
element_type TopLeftShareStack(ShareStack stack){
    if(EmptyLeftShareStack(stack)){
        printf("PopLeftShareStack:栈空无法出栈！\n");
        return DEFAULTELEM;
    }
    return stack.data[stack.top_left];
}

// 读取右首部
element_type TopRightShareStack(ShareStack stack){
    if(EmptyLeftShareStack(stack)){
        printf("TopRightShareStack:栈空无法出栈！\n");
        return DEFAULTELEM;
    }
    return stack.data[stack.top_right];
}