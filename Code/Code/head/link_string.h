#include "head.h"

// ���������
typedef struct LinkStringNode {
    // ����
    char *data;
    // ָ��
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



