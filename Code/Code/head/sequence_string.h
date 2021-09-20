#include "head.h"

// 顺序串
typedef struct {
    // 数据
    char *data;
    // 长度
    unsigned int length;
    // 最大容量
    unsigned int max_size;
} SequenceString;

bool InitSequenceString(SequenceString &string) {
    string.data = (char *) malloc(sizeof(char) * MAXSIZE);
    string.max_size = MAXSIZE;
    string.length = 0;
    return true;
}

bool InitSequenceString(SequenceString &string, int max_size) {
    string.data = (char *) malloc(sizeof(char) * max_size);
    string.max_size = max_size;
    string.length = 0;
    return true;
}

SequenceString InitSequenceString() {
    auto *string = (SequenceString *) malloc(sizeof(SequenceString));
    string->data = (char *) malloc(sizeof(char) * MAXSIZE);
    string->max_size = MAXSIZE;
    string->length = 0;
    return (SequenceString &) string;
}

SequenceString InitSequenceString(int max_size) {
    auto *string = (SequenceString *) malloc(sizeof(SequenceString));
    string->data = (char *) malloc(sizeof(char) * max_size);
    string->max_size = max_size;
    string->length = 0;
    return (SequenceString &) string;
}