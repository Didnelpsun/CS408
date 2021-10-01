#include "head.h"

// 直接插入排序
bool StraightInsertSort(LinearTable table) {
    // 循环从第二个开始
    for (int i = 1; i < table.length; i++) {
        // 若当前元素小于前面一个，即小于已排序序列的最大值，则要对当前元素排序
        if (table.data[i] < table.data[i - 1]) {
            // 向前遍历是否有比当前元素大的，若有则插到当前元素后面
            int temp = table.data[i];
            // 不断后移元素
            int j;
            for (j = i - 1; j >= 0 && table.data[j] > temp; j--) {
                table.data[j + 1] = table.data[j];
            }
            // 将temp插入这个空处
            table.data[j + 1] = temp;
        }
    }
    return true;
}

// 折半插入排序
bool BinaryInsertSort(LinearTable table) {
    // 定义指针
    int i, j, low, high, mid;
    elem_type temp;
    // 依次将元素插入到前面的排序序列
    for (i = 1; i < table.length; i++) {
        temp = table.data[i];
        // 设置折半查找的范围，即从0到当前元素前一个元素
        low = 0;
        high = i - 1;
        while (low <= high) {
            // 取中间点
            mid = (low + high) / 2;
            // 查左子表
            if (table.data[mid] > table.data[0])
                high = mid - 1;
                // 查右子表
            else
                low = mid + 1;
        }
        for (j = i - 1; j > high; j--) {
            // 后移一位，空出插入位置
            table.data[j + 1] = table.data[j];
        }
        table.data[j + 1] = temp;
    }
}

// 希尔排序
bool ShellSort(LinearTable table) {
    int j;
    // 设置步长
    for (int group = table.length / 2; group > 0; group /= 2) {
        for (int i = group; i < table.length; i++) {
            elem_type temp = table.data[i];
            for (j = i; j >= group && temp < table.data[j - group]; j -= group) {
                table.data[j] = table.data[j - group];
            }
            table.data[j] = temp;
        }
    }
    return true;
}

// 冒泡排序
bool BubbleSort(LinearTable table){
    elem_type temp;
    // 外循环为排序趟数，一共需要length-1趟
    for(int i=0;i<table.length-1;i++){
        // 内循环为排序趟数，i趟比较次数为length-i
        // 排序完成的序列在后面
        for(int j=0;j<table.length-1-i;j++){
            if(table.data[j]>table.data[j+1]){
                temp = table.data[j];
                table.data[j] = table.data[j+1];
                table.data[j+1] = temp;
            }
        }
    }
    return true;
}