#include "head.h"

// 顺序串
typedef struct {
    // 数据
    char *data;
    // 长度
    int length;
    // 最大容量
    int max_size;
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

// 简单字符串匹配
int LocateSimple(SequenceString string, SequenceString pattern) {
    int i = 0, j = 0;
    while (i < string.length && j < pattern.length) {
        // 匹配就继续后移
        if (string.data[i] == pattern.data[j]) {
            i++;
            j++;
        }
            // 不匹配就撤回
        else {
            i = i - j + 1;
            j = 0;
        }
    }
    if (j >= pattern.length) {
        return i - pattern.length;
    }
    return -1;
}

// 获取KMP的next数组
int *GetNext(SequenceString string) {
    auto *next = (int *) malloc(sizeof(int) * string.length);
    next[0] = 0;
    // i为当前主串正在匹配的字符位置，也就是next数组的索引
    int i = 0, j = 0;
    while (i < string.length) {
        if (j == 0 || string.data[i] == string.data[j]) {
            next[++i] = ++j;
        } else {
            j = next[j];
        }
    }
    return next;
}

// 获取KMP的nextval数组
int *GetNextVal(SequenceString string) {
    auto *nextval = (int *) malloc(sizeof(int) * string.length);
    nextval[0] = 0;
    // i为当前主串正在匹配的字符位置，也就是next数组的索引
    int i = 0, j = 0;
    while (i < string.length) {
        if (j == 0 || string.data[i] == string.data[j]) {
            ++i;
            ++j;
            if (string.data[i] != string.data[j])
                nextval[i] = j;
            else
                nextval[i] = nextval[j];
        } else {
            j = nextval[j];
        }
    }
    return nextval;
}

int LocateKMP(SequenceString string, SequenceString pattern, const int *next) {
    int i = 0, j = 0;
    while (i < string.length && j < pattern.length) {
        if (j == 0 || string.data[i] == pattern.data[j]) {
            // 匹配则继续比较
            ++i;
            ++j;
        } else {
            // 模式串右移
            j = next[j];
        }
    }
    if (j >= pattern.length) {
        // 匹配成功
        return i - pattern.length;
    } else {
        return -1;
    }
}

int LocateKMP(SequenceString string, SequenceString pattern) {
    int *next = GetNext(pattern);
    int i = 0, j = 0;
    while (i < string.length && j < pattern.length) {
        if (j == 0 || string.data[i] == pattern.data[j]) {
            // 匹配则继续比较
            ++i;
            ++j;
        } else {
            // 模式串右移
            j = next[j];
        }
    }
    if (j >= pattern.length) {
        // 匹配成功
        return i - pattern.length;
    } else {
        return -1;
    }
}

bool DestroySequenceString(SequenceString &string) {
    free(string.data);
    string.max_size = 0;
    string.length = 0;
    return true;
}