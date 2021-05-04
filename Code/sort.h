#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// ֱ�Ӳ�������
int DirectInsertSort(element_type data[], int length) {
	int i, j;
	element_type temp;
	// ѭ����������
	for (i = 1; i < length; i++) {
		// ��data[i]�ؼ���С��ǰһ��
		if (data[i] < data[i - 1]) {
			// ��temp�ݴ�data[i]
			temp = data[i];
			// �������ǰ���Ѿ��ź����Ԫ��
			for (j = i - 1; j >= 0 && data[j] > temp; --j) {
				// ��Ԫ�ش���temp�����һλ
				data[j + 1] = data[j];
			}
			// ��ֵ������λ��
			data[j + 1] = temp;
		}
	}
	return 0;
}

// �۰��������
int BinaryInsertSort(element_type data[], int length) {
	int i, j, low, high, mid;
	// ���ν�data[2]��data[n-1]���뵽ǰ���Ѿ������������
	for (i = 2; i <= length; i++) {
		// ��data[i]�ݴ浽data[0]
		data[0] = data[i];
		// �����۰���ҵķ�Χ
		low = 1;
		high = i - 1;
		while (low <= high) {
			// ȡ�м��
			mid = (low + high) / 2;
			if (data[mid] > data[0]) {
				// ��������ӱ�
				high = mid - 1;
			}
			else {
				// �����Ұ��ӱ�
				low = mid + 1;
			}
		}
		// ͳһ����Ԫ�أ��ճ�����λ��
		for (j = 1; j >= high + 1; --j) {
			data[j + 1] = data[j];
		}
		// ����Ԫ��
		data[high + 1] = data[0];
	}
	return 0;
}

// ϣ������
int ShellSort(element_type data[], int length) {
	// d����ǰ���������ֵ
	int d, i, j;
	// data[0]ֻ���ݴ����ݣ���j<=0ʱ�͵��˲���λ��
	for (d = length / 2; d >= 1; d = d / 2) {
		for (i = d + 1; i <= length; ++i) {
			// ��Ҫ��data[i]���뵽���������ӱ�
			if (data[i] < data[i - d]) {
				// �ݴ浽data[0]��
				data[0] = data[i];
				for (j = i - d; j > 0 && data[0] < data[j]; j -= d) {
					// ��¼���ƣ�Ѱ�Ҳ����λ��
					data[j + d] = data[j];
				}
				// ��������
				data[j + d] = data[0];
			}
		}
	}
}