#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// ��̬˳��
typedef struct {
    char data[MAXSIZE];
    // ����
    int length;
} StaticSequenceString;

// ��̬˳��
typedef struct {
    char* data;
    int length;
} DynamicSequenceString;

// ��̬˳���Ӵ�
int SubStaticSequenceString(StaticSequenceString string, StaticSequenceString *substring, int index, int length) {
    // ����Ӵ�Խ��
    if (index + length > string.length) {
        printf("StaticSequenceString:�Ӵ���ΧԽ�磡");
        return 1;
    }
    for (int i = 0; i < length; i++) {
        substring->data[i] = string.data[index + i];
    }
    substring->length = length;
    return 0;
}

// �ԱȾ�̬˳���ַ���
int CompareStaticSequenceString(StaticSequenceString string1, StaticSequenceString string2) {
    for (int i = 0; i <= string1.length && i <= string2.length; i++) {
        if (string1.data[i] != string2.data[i]) {
            return string1.data[i] - string2.data[i];
        }
    }
    // ���ɨ����������ַ�����ͬ���򳤶ȳ����ַ�������
    return string1.length - string2.length;
}

// �ھ�̬˳���ַ����ж�λ�Ӵ�
// ��������д������Ӵ���ͬ���Ӵ����򷵻��������е�һ�γ��ֵ�λ�ã����򷵻�-1
int LocateStaticSequenceString(StaticSequenceString mainstring, StaticSequenceString substring) {
    int i = 0;
    // �����ݴ��Ӵ�
    StaticSequenceString temp;
    while (i < mainstring.length - substring.length + 1) {
        // �������и��������Ӵ���ͬ���ȵ��Ӵ�
        SubStaticSequenceString(mainstring, &temp, i, substring.length);
        // ����и��������Ӵ����Ӵ�����Ⱦͺ���һλ���и��Ӵ�
        if (CompareStaticSequenceString(substring, temp) != 0) {
            i++;
        }
        // ���򷵻ص�ǰ������
        else {
            return i;
        }
    }
    return -1;
}

// ��ģʽ����next����
// ����0����������ֵ
int GetNext(StaticSequenceString string, int *next[]) {
    int i = 1, j = 0;
    next[i] = 0;
    while (i < string.length) {
        if (j == 0 || string.data[i] == string.data[j]) {
            ++i, ++j;
            *next[i] = j;
        }
        else {
            if (next[j]) {
                // ģʽ������
                j = *next[j];
            }
        }
    }
    return 0;
}

// KMP�㷨
int KMP(StaticSequenceString string1, StaticSequenceString string2) {
    int i = 1, j = 1;
    int length = string2.length + 1;
    int* next = (int*)malloc(length*sizeof(int));
    GetNext(string2, &next);
    while (i <= string1.length && j <= string2.length) {
        if (j == 0 || string1.data[i] == string2.data[j]) {
            i++, j++;
        }
        else {
            // ģʽ�ַ�������
            j = next[i];
        }
    }
    if (j > string2.length) {
        return i - string2.length;
    }
    return -1;
    free(next);
}