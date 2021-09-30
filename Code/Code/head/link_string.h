#include "head.h"

// 块链串结点
typedef struct LinkStringNode {
    // 数据
    char *data;
    // 指针
    LinkStringNode *next;
} LinkStringNode, *LinkString;

bool InitLinkString(LinkString &string) {
    string->data = (char *) malloc(sizeof(char) * DATASIZE);
    string->next = nullptr;
    return true;
}

LinkString InitLinkString() {
    auto* string = (LinkString) malloc(sizeof(LinkString));
    string->data = (char *) malloc(sizeof(char) * DATASIZE);
    string->next = nullptr;
    return (LinkString &)string;
}



