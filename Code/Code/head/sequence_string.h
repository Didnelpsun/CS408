#include "head.h"

// ˳��
typedef struct {
    // ����
    char *data;
    // ����
    int length;
    // �������
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

// ���ַ���ƥ��
int LocateSimple(SequenceString string, SequenceString pattern) {
    int i = 0, j = 0;
    while (i < string.length && j < pattern.length) {
        // ƥ��ͼ�������
        if (string.data[i] == pattern.data[j]) {
            i++;
            j++;
        }
            // ��ƥ��ͳ���
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

// ��ȡKMP��next����
int *GetNext(SequenceString string) {
    auto *next = (int *) malloc(sizeof(int) * string.length);
    next[0] = 0;
    // iΪ��ǰ��������ƥ����ַ�λ�ã�Ҳ����next���������
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

// ��ȡKMP��nextval����
int *GetNextVal(SequenceString string) {
    auto *nextval = (int *) malloc(sizeof(int) * string.length);
    nextval[0] = 0;
    // iΪ��ǰ��������ƥ����ַ�λ�ã�Ҳ����next���������
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
            // ƥ��������Ƚ�
            ++i;
            ++j;
        } else {
            // ģʽ������
            j = next[j];
        }
    }
    if (j >= pattern.length) {
        // ƥ��ɹ�
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
            // ƥ��������Ƚ�
            ++i;
            ++j;
        } else {
            // ģʽ������
            j = next[j];
        }
    }
    if (j >= pattern.length) {
        // ƥ��ɹ�
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