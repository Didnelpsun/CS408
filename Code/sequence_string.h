#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// 静态顺序串
typedef struct {
    char data[MAXSIZE];
    // 串长
    int length;
} StaticSequenceString;

// 动态顺序串
typedef struct {
    char* data;
    int length;
} DynamicSequenceString;

// 求静态顺序子串
int SubStaticSequenceString(StaticSequenceString string, StaticSequenceString *substring, int index, int length) {
    // 如果子串越界
    if (index + length > string.length) {
        printf("StaticSequenceString:子串范围越界！");
        return 1;
    }
    for (int i = 0; i < length; i++) {
        substring->data[i] = string.data[index + i];
    }
    substring->length = length;
    return 0;
}

// 对比静态顺序字符串
int CompareStaticSequenceString(StaticSequenceString string1, StaticSequenceString string2) {
    for (int i = 0; i <= string1.length && i <= string2.length; i++) {
        if (string1.data[i] != string2.data[i]) {
            return string1.data[i] - string2.data[i];
        }
    }
    // 如果扫描过的所有字符都相同，则长度长的字符串更长
    return string1.length - string2.length;
}

// 在静态顺序字符串中定位子串
// 如果主串中存在与子串相同的子串，则返回在主串中第一次出现的位置，否则返回-1
int LocateStaticSequenceString(StaticSequenceString mainstring, StaticSequenceString substring) {
    int i = 0;
    // 用于暂存子串
    StaticSequenceString temp;
    while (i < mainstring.length - substring.length + 1) {
        // 从主串切割下来与子串相同长度的子串
        SubStaticSequenceString(mainstring, &temp, i, substring.length);
        // 如果切割下来的子串与子串不相等就后移一位再切割子串
        if (CompareStaticSequenceString(substring, temp) != 0) {
            i++;
        }
        // 否则返回当前的索引
        else {
            return i;
        }
    }
    return -1;
}