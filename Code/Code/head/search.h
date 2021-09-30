#include "head.h"

// 线性表
typedef struct {
    elem_type *data;
    int length;
} LinearTable;

// 顺序查找
int SequenceSearch(LinearTable table, elem_type key) {
    for (int i = 0; i < table.length; i++) {
        if (table.data[i] == key)
            return i;
    }
    return -1;
}

// 折半查找
int BinarySearch(LinearTable table, elem_type key) {
    int low = 0, high = table.length - 1, mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (table.data[mid] == key)
            return mid;
        else if (table.data[mid] > key)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

