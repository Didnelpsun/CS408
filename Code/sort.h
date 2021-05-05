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
	return 0;
}

// ð������
int BubbleSort(element_type data[], int length) {
	for (int i = 0; i < length - 1; i++) {
		// ����һ����־��ʾ����ð�������Ƿ�������
		int flag = 0;
		element_type temp;
		for (int j = length - 1; j > i; j--) {
			if (data[j - 1] > data[j]) {
				temp = data[j - 1];
				data[j - 1] = data[j];
				data[j] = temp;
				flag = 1;
			}
		}
		// ������α�����û�з����������ʹ����Ѿ�����
		if (flag == 0) {
			return 0;
		}
	}
	return 0;
}

// �������򻮷�
int QuickPart(element_type data[], int low, int high) {
	// ѡ��data[low]��Ϊ��׼
	int pivot = data[low];
	// ��low��high������׼������λ��
	while (low < high) {
		// �����ǰhighָ���Ԫ�ش��ڻ�׼���ƶ�highָ��
		while (low < high && data[high] >= pivot) {
			--high;
		}
		// �ȱ�׼С��Ԫ���ƶ���lowָ���Ԫ��
		data[low] = data[high];
		// �����ƶ�ָ��
		// �����ǰlowָ���Ԫ��С�ڻ�׼���ƶ�lowָ��
		while (low < high && data[low] <= pivot) {
			++low;
		}
		// �ȱ�׼���Ԫ���ƶ���highָ���Ԫ��
		data[high] = data[low];
	}
	// ��low��highָ��ͬһ��Ԫ��ʱ�Ͱѻ�׼�ŵ����λ��
	data[low] = pivot;
	// ���ش�Ż�׼Ԫ�ص�λ��
	return low;
}

// ��������
int QuickSort(element_type data[], int low, int high) {
	// �ݹ���������,��low=high������ֻ��һ��Ԫ��
	if (low < high) {
		// ���л���
		int pivot = QuickPart(data, low, high);
		// �Ի��ֵ����ӱ���д���
		QuickSort(data, low, pivot - 1);
		// �Ի��ֵ����ӱ���д���
		QuickSort(data, pivot + 1, high);
	}
	return 0;
}

// ��ѡ������
int SimpleSelectSort(element_type data[], int length) {
	element_type temp;
	// һ������n-1��
	for (int i = 0; i < length - 1; i++) {
		// ��¼��СԪ�ص�λ��
		int min = i;
		// ��data[i,length-1]��ѡ����С��Ԫ��
		for (int j = i + 1; j < length; j++) {
			// ������СԪ��λ��
			if (data[j] < data[min]) {
				min = j;
			}
		}
		// �����ǰ��СԪ�ص�ֵ�����ڵ�ǰָ��λ�þͽ���
		if (min != i) {
			temp = i;
			i = min;
			min = i;
		}
	}
}

// ���������
int BuildMaxHeap(element_type data[], int length) {
	for (int i = length / 2; i > 0; i--) {
		MaxHeadAdjust(data, i, length);
	}
	return 0;
}

// ��nodeΪ������������Ϊ�����
int MaxHeadAdjust(element_type data[], int node, int length) {
	// ʹ��data[0]�ݴ����������
	data[0] = data[node];
	// ��key�ϴ���ӽ������ɸѡ
	for (int i = 2 * node; i <= length; i *= 2) {
		// ȡkey�ϴ���ӽڵ���±�
		if (i < length && data[i] < data[i + 1]) {
			i++;
		}
		// ��������������ӽ��������õ���
		if (data[0] >= data[i]) {
			break;
		}
		else {
			// ��data[i]�ŵ��������
			data[node] = data[i];
			// �޸�nodeֵ���Լ�������ɸѡ
			node = i;
		}
	}
	// ��ɸѡ����ֵ���ŵ�����λ��
	data[node] = data[0];
	return 0;
}

// ����ѵĶ�����
int MaxHeapSort(element_type data[], int length) {
	// ��ʼ������һ�������
	BuildMaxHeap(data, length);
	// ����һ����������
	element_type temp;
	// n-1�˽����ͽ����Ĺ���
	for (int i = length; i > 1; i--) {
		// �Ѷ�Ԫ����ѵ�Ԫ�ػ���
		temp = data[i];
		data[i] = data[1];
		data[1] = temp;
		// ��ʣ��Ĵ�����Ԫ�ص���Ϊ��
		MaxHeadAdjust(data, i, i - 1);
	}
	return 0;
}

// �鲢����������
element_type* aid = (element_type*)malloc(MAXSIZE * sizeof(element_type));

// data[low,mid]��data[mid+1,high]�������򣬽��������ֹ鲢
int Merge(element_type data[], int low, int mid, int high) {
	int i, j, k;
	for (k - low; k <= high; k++) {
		// ��data������Ԫ�ظ��Ƶ�����������
		aid[k] = data[k];
	}
	for (i = low, j = mid + 1, k = i; i <= mid && j <= high; k++) {
		if (aid[i] <= aid[j]) {
			data[k] = aid[i++];
		}
		else {
			data[k] = aid[j++];
		}
	}
	while (i <= mid) {
		data[k++] = aid[i++];
	}
	while (j <= high) {
		data[k++] = aid[j++];
	}
	return 0;
}

// �鲢����
int MergeSort(element_type data[], int low, int high) {
	if (low < high) {
		// ���м仮��
		int mid = (low + high) / 2;
		// ����벿�ֹ鲢����
		MergeSort(data, low, mid);
		// ���Ұ벿�ֹ鲢����
		MergeSort(data, mid + 1, high);
		// ���һ�ι鲢ȫ��
		Merge(data, low, mid, high);
	}
	return 0;
}