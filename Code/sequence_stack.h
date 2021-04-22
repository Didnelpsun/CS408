#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// 顺序栈
typedef struct {
	// 静态数组存储栈元素
	element_type data[MAXSIZE];
	// 栈顶指针
	int top;
} SequenceStack;

// 初始化顺序栈
int InitSequenceStack(SequenceStack* stack) {
	stack->top = -1;
	return 0;
}

// 判断顺序栈是否为空
int IsSequenceStackEmpty(SequenceStack stack) {
	if (stack.top == -1) {
		return 1;
	}
	else {
		return 0;
	}
}

// 将元素推入顺序栈
int PushSequenceStack(SequenceStack* stack, element_type elem) {
	// 栈满无法添加元素
	if (stack->top == MAXSIZE - 1) {
		printf("PushSequenceStack:栈满无法继续推入元素！");
		return 1;
	}
	//// 指针加一
	//stack->top += 1;
	//// 新元素入栈
	//stack->data[stack->top] = elem;
	// 加一并入栈
	stack->data[++stack->top] = elem;
	return 0;
}

// 将元素弹出顺序栈
int PopSequenceStack(SequenceStack* stack, element_type* elem) {
	// 栈空无法删除元素
	if (stack->top == -1) {
		printf("PopSequenceStack:栈空无法继续弹出元素！");
		return 1;
	}
	// 弹出后再出栈
	*elem = stack->data[stack->top--];
	return 0;
}

// 读取顺序栈栈顶元素
int GetSequenceStackTop(SequenceStack* stack, element_type* elem) {
	// 栈空无法获取元素
	if (stack->top == -1) {
		printf("PopSequenceStack:栈空无法读取元素！");
		return 1;
	}
	// 弹出后再出栈
	*elem = stack->data[stack->top];
	return 0;
}

// 顺序栈实现括号匹配
int BracketCheck(char str[], int length) {
	SequenceStack s;
	// 初始化栈
	InitSequenceStack(&s);
	for (int i = 0; i < length; i++) {
		// 扫描到左括号
		if (str[i] == '{' || str[i] == '[' || str[i] == '(') {
			PushSequenceStack(&s, str[i]);
		}
		else {
			// 如果栈空
			if (IsSequenceStackEmpty(s)==1) {
				return 1;
			}
		}
		// 定义一个栈顶元素变量
		char t;
		PopSequenceStack(&s, &t);
		if (str[i] == ')' && t != '(') {
			return 1;
		}
		if (str[i] == ']' && t != '[') {
			return 1;
		}
		if (str[i] == '}' && t != '{') {
			return 1;
		}
	}
	return 0;
}