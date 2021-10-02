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
    return true;
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
bool BubbleSort(LinearTable table) {
    elem_type temp;
    // 外循环为排序趟数，一共需要length-1趟
    for (int i = 0; i < table.length - 1; i++) {
        // 内循环为排序趟数，i趟比较次数为length-i
        // 排序完成的序列在后面
        for (int j = 0; j < table.length - 1 - i; j++) {
            if (table.data[j] > table.data[j + 1]) {
                temp = table.data[j];
                table.data[j] = table.data[j + 1];
                table.data[j + 1] = temp;
            }
        }
    }
    return true;
}

// 快速排序一趟划分
int PartQuickSort(LinearTable table, int low, int high) {
    // 假设表中第一个元素为枢纽对表进行划分
    elem_type pivot = table.data[low];
    // 跳出循环条件
    while (low < high) {
        // 若元素大于枢轴则一直左移
        while (low < high && table.data[high] >= pivot)
            --high;
        // 将比枢轴小的元素移动到左端
        table.data[low] = table.data[high];
        while (low < high && table.data[low] <= pivot)
            ++low;
        // 比枢轴大的元素移动到右端
        table.data[high] = table.data[low];
    }
    // 枢轴元素放到最终位置
    table.data[low] = pivot;
    return low;
}

// 快速排序
bool QuickSort(LinearTable table, int low, int high) {
    // 递归跳出条件
    if (low < high) {
        // 划分
        int pivot = PartQuickSort(table, low, high);
        // 递归
        PartQuickSort(table, low, pivot - 1);
        PartQuickSort(table, pivot + 1, high);
    }
    return true;
}

// 简单选择排序
bool SimpleSelectSort(LinearTable table) {
    int min;
    for (int i = 0; i < table.length - 1; i++) {
        // 记录最小元素
        min = i;
        // 选择最小元素
        for (int j = i + 1; j < table.length; j++) {
            // 更新最小元素位置
            if (table.data[j] < table.data[min])
                min = j;
            // 交换元素
            if (min != i) {
                elem_type temp = table.data[min];
                table.data[min] = table.data[i];
                table.data[i] = temp;
            }
        }
    }
    return true;
}

// 建立根堆
bool BuildHeap(LinearTable table, bool HeadAdjust(LinearTable table, int index)) {
    // 从i=[n/2]~1开始反复调整堆
    for (int i = table.length / 2; i > 0; i--) {
        bool result = HeadAdjust(table, i);
        if (!result)
            return false;
    }
    return true;
}

// 调整大根堆
bool HeadMaxAdjust(LinearTable table, int index) {
    // 将根元素为索引值index的子树进行调整，之后的元素已经有序
    // 0索引处暂存子树根结点
    table.data[0] = table.data[index];
    // 沿着索引值较大的子结点向下筛选
    for (int i = 2 * index; i <= table.length; i *= 2) {
        // 继续寻找较大的子结点的下标
        if (i < table.length && table.data[i] < table.data[i + 1])
            i++;
        // 筛选结束，因为要找的元素必须比根结点大
        if (table.data[0] >= table.data[i])
            break;
        else {
            // 将index的元素调整到双亲结点上
            table.data[index] = table.data[i];
            // 修改index值，以便继续向下筛选
            index = i;
        }
    }
    // 将被筛选结点放入最终位置
    table.data[index] = table.data[0];
    return true;
}

// 堆排序
bool HeapSort(LinearTable table, bool mode){
    bool result;
    // mode为true建立大根堆，false建立小根堆
    if(mode)
        result = BuildHeap(table, HeadMaxAdjust);
    if(!result)
        return false;
    for(int i=table.length;i>1;i--){
        // 栈顶元素和栈底元素交换
        elem_type temp = table.data[0];
        table.data[0] = table.data[i];
        table.data[i] = temp;
        if(mode)
            HeadMaxAdjust(table,i);
    }
    return true;
}