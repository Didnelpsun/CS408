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