#include "head.h"

// ֱ�Ӳ�������
bool StraightInsertSort(LinearTable table) {
    // ѭ���ӵڶ�����ʼ
    for (int i = 1; i < table.length; i++) {
        // ����ǰԪ��С��ǰ��һ������С�����������е����ֵ����Ҫ�Ե�ǰԪ������
        if (table.data[i] < table.data[i - 1]) {
            // ��ǰ�����Ƿ��бȵ�ǰԪ�ش�ģ�������嵽��ǰԪ�غ���
            int temp = table.data[i];
            // ���Ϻ���Ԫ��
            int j;
            for (j = i - 1; j >= 0 && table.data[j] > temp; j--) {
                table.data[j + 1] = table.data[j];
            }
            // ��temp��������մ�
            table.data[j + 1] = temp;
        }
    }
    return true;
}

// �۰��������
bool BinaryInsertSort(LinearTable table) {
    // ����ָ��
    int i, j, low, high, mid;
    elem_type temp;
    // ���ν�Ԫ�ز��뵽ǰ�����������
    for (i = 1; i < table.length; i++) {
        temp = table.data[i];
        // �����۰���ҵķ�Χ������0����ǰԪ��ǰһ��Ԫ��
        low = 0;
        high = i - 1;
        while (low <= high) {
            // ȡ�м��
            mid = (low + high) / 2;
            // �����ӱ�
            if (table.data[mid] > table.data[0])
                high = mid - 1;
                // �����ӱ�
            else
                low = mid + 1;
        }
        for (j = i - 1; j > high; j--) {
            // ����һλ���ճ�����λ��
            table.data[j + 1] = table.data[j];
        }
        table.data[j + 1] = temp;
    }
    return true;
}

// ϣ������
bool ShellSort(LinearTable table) {
    int j;
    // ���ò���
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

// ð������
bool BubbleSort(LinearTable table) {
    elem_type temp;
    // ��ѭ��Ϊ����������һ����Ҫlength-1��
    for (int i = 0; i < table.length - 1; i++) {
        // ��ѭ��Ϊ����������i�˱Ƚϴ���Ϊlength-i
        // ������ɵ������ں���
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

// ��������һ�˻���
int PartQuickSort(LinearTable table, int low, int high) {
    // ������е�һ��Ԫ��Ϊ��Ŧ�Ա���л���
    elem_type pivot = table.data[low];
    // ����ѭ������
    while (low < high) {
        // ��Ԫ�ش���������һֱ����
        while (low < high && table.data[high] >= pivot)
            --high;
        // ��������С��Ԫ���ƶ������
        table.data[low] = table.data[high];
        while (low < high && table.data[low] <= pivot)
            ++low;
        // ��������Ԫ���ƶ����Ҷ�
        table.data[high] = table.data[low];
    }
    // ����Ԫ�طŵ�����λ��
    table.data[low] = pivot;
    return low;
}

// ��������
bool QuickSort(LinearTable table, int low, int high) {
    // �ݹ���������
    if (low < high) {
        // ����
        int pivot = PartQuickSort(table, low, high);
        // �ݹ�
        PartQuickSort(table, low, pivot - 1);
        PartQuickSort(table, pivot + 1, high);
    }
    return true;
}

// ��ѡ������
bool SimpleSelectSort(LinearTable table) {
    int min;
    for (int i = 0; i < table.length - 1; i++) {
        // ��¼��СԪ��
        min = i;
        // ѡ����СԪ��
        for (int j = i + 1; j < table.length; j++) {
            // ������СԪ��λ��
            if (table.data[j] < table.data[min])
                min = j;
            // ����Ԫ��
            if (min != i) {
                elem_type temp = table.data[min];
                table.data[min] = table.data[i];
                table.data[i] = temp;
            }
        }
    }
    return true;
}

// ��������
bool BuildHeap(LinearTable table, bool HeadAdjust(LinearTable table, int index)) {
    // ��i=[n/2]~1��ʼ����������
    for (int i = table.length / 2; i > 0; i--) {
        bool result = HeadAdjust(table, i);
        if (!result)
            return false;
    }
    return true;
}

// ���������
bool HeadMaxAdjust(LinearTable table, int index) {
    // ����Ԫ��Ϊ����ֵindex���������е�����֮���Ԫ���Ѿ�����
    // 0�������ݴ����������
    table.data[0] = table.data[index];
    // ��������ֵ�ϴ���ӽ������ɸѡ
    for (int i = 2 * index; i <= table.length; i *= 2) {
        // ����Ѱ�ҽϴ���ӽ����±�
        if (i < table.length && table.data[i] < table.data[i + 1])
            i++;
        // ɸѡ��������ΪҪ�ҵ�Ԫ�ر���ȸ�����
        if (table.data[0] >= table.data[i])
            break;
        else {
            // ��index��Ԫ�ص�����˫�׽����
            table.data[index] = table.data[i];
            // �޸�indexֵ���Ա��������ɸѡ
            index = i;
        }
    }
    // ����ɸѡ����������λ��
    table.data[index] = table.data[0];
    return true;
}

// ������
bool HeapSort(LinearTable table, bool mode){
    bool result;
    // modeΪtrue��������ѣ�false����С����
    if(mode)
        result = BuildHeap(table, HeadMaxAdjust);
    if(!result)
        return false;
    for(int i=table.length;i>1;i--){
        // ջ��Ԫ�غ�ջ��Ԫ�ؽ���
        elem_type temp = table.data[0];
        table.data[0] = table.data[i];
        table.data[i] = temp;
        if(mode)
            HeadMaxAdjust(table,i);
    }
    return true;
}