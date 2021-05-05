#include <stdio.h>
#include <stdlib.h>
#include "head.h"

// 直接插入排序
int DirectInsertSort(element_type data[], int length) {
	int i, j;
	element_type temp;
	// 循环遍历数组
	for (i = 1; i < length; i++) {
		// 若data[i]关键字小于前一个
		if (data[i] < data[i - 1]) {
			// 用temp暂存data[i]
			temp = data[i];
			// 检查所有前面已经排好序的元素
			for (j = i - 1; j >= 0 && data[j] > temp; --j) {
				// 若元素大于temp则后移一位
				data[j + 1] = data[j];
			}
			// 赋值到插入位置
			data[j + 1] = temp;
		}
	}
	return 0;
}

// 折半查找排序
int BinaryInsertSort(element_type data[], int length) {
	int i, j, low, high, mid;
	// 依次将data[2]到data[n-1]插入到前面已经排序的序列中
	for (i = 2; i <= length; i++) {
		// 将data[i]暂存到data[0]
		data[0] = data[i];
		// 设置折半查找的范围
		low = 1;
		high = i - 1;
		while (low <= high) {
			// 取中间点
			mid = (low + high) / 2;
			if (data[mid] > data[0]) {
				// 查找左半子表
				high = mid - 1;
			}
			else {
				// 查找右半子表
				low = mid + 1;
			}
		}
		// 统一后移元素，空出插入位置
		for (j = 1; j >= high + 1; --j) {
			data[j + 1] = data[j];
		}
		// 插入元素
		data[high + 1] = data[0];
	}
	return 0;
}

// 希尔排序
int ShellSort(element_type data[], int length) {
	// d代表当前处理的增量值
	int d, i, j;
	// data[0]只是暂存数据，等j<=0时就到了插入位置
	for (d = length / 2; d >= 1; d = d / 2) {
		for (i = d + 1; i <= length; ++i) {
			// 需要将data[i]插入到有序增量子表
			if (data[i] < data[i - d]) {
				// 暂存到data[0]中
				data[0] = data[i];
				for (j = i - d; j > 0 && data[0] < data[j]; j -= d) {
					// 记录后移，寻找插入的位置
					data[j + d] = data[j];
				}
				// 插入数据
				data[j + d] = data[0];
			}
		}
	}
	return 0;
}

// 冒泡排序
int BubbleSort(element_type data[], int length) {
	for (int i = 0; i < length - 1; i++) {
		// 设置一个标志表示本趟冒泡排序是否发生交换
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
		// 如果本次遍历后没有发生交换，就代表已经有序
		if (flag == 0) {
			return 0;
		}
	}
	return 0;
}

// 快速排序划分
int QuickPart(element_type data[], int low, int high) {
	// 选择data[low]作为基准
	int pivot = data[low];
	// 用low和high搜索基准的最终位置
	while (low < high) {
		// 如果当前high指向的元素大于基准就移动high指针
		while (low < high && data[high] >= pivot) {
			--high;
		}
		// 比标准小的元素移动到low指向的元素
		data[low] = data[high];
		// 交换移动指针
		// 如果当前low指向的元素小于基准就移动low指针
		while (low < high && data[low] <= pivot) {
			++low;
		}
		// 比标准大的元素移动到high指向的元素
		data[high] = data[low];
	}
	// 当low和high指向同一个元素时就把基准放到这个位置
	data[low] = pivot;
	// 返回存放基准元素的位置
	return low;
}

// 快速排序
int QuickSort(element_type data[], int low, int high) {
	// 递归跳出条件,即low=high，表中只有一个元素
	if (low < high) {
		// 进行划分
		int pivot = QuickPart(data, low, high);
		// 对划分的左子表进行处理
		QuickSort(data, low, pivot - 1);
		// 对划分的右子表进行处理
		QuickSort(data, pivot + 1, high);
	}
	return 0;
}

// 简单选择排序
int SimpleSelectSort(element_type data[], int length) {
	element_type temp;
	// 一共进行n-1趟
	for (int i = 0; i < length - 1; i++) {
		// 记录最小元素的位置
		int min = i;
		// 在data[i,length-1]中选择最小的元素
		for (int j = i + 1; j < length; j++) {
			// 更新最小元素位置
			if (data[j] < data[min]) {
				min = j;
			}
		}
		// 如果当前最小元素的值不等于当前指向位置就交换
		if (min != i) {
			temp = i;
			i = min;
			min = i;
		}
	}
}

// 建立大根堆
int BuildMaxHeap(element_type data[], int length) {
	for (int i = length / 2; i > 0; i--) {
		MaxHeadAdjust(data, i, length);
	}
	return 0;
}

// 以node为根的子树调整为大根堆
int MaxHeadAdjust(element_type data[], int node, int length) {
	// 使用data[0]暂存子树根结点
	data[0] = data[node];
	// 沿key较大的子结点向下筛选
	for (int i = 2 * node; i <= length; i *= 2) {
		// 取key较大的子节点的下标
		if (i < length && data[i] < data[i + 1]) {
			i++;
		}
		// 如果根大于左右子结点则代表不用调整
		if (data[0] >= data[i]) {
			break;
		}
		else {
			// 将data[i]放到父结点上
			data[node] = data[i];
			// 修改node值，以继续向下筛选
			node = i;
		}
	}
	// 被筛选结点的值最后放到最后的位置
	data[node] = data[0];
	return 0;
}

// 大根堆的堆排序
int MaxHeapSort(element_type data[], int length) {
	// 初始化建立一个大根堆
	BuildMaxHeap(data, length);
	// 建立一个交换变量
	element_type temp;
	// n-1趟交换和建立的过程
	for (int i = length; i > 1; i--) {
		// 堆顶元素与堆底元素互换
		temp = data[i];
		data[i] = data[1];
		data[1] = temp;
		// 把剩余的待排序元素调整为堆
		MaxHeadAdjust(data, i, i - 1);
	}
	return 0;
}

// 归并排序辅助数组
element_type* aid = (element_type*)malloc(MAXSIZE * sizeof(element_type));

// data[low,mid]和data[mid+1,high]各自有序，将两个部分归并
int Merge(element_type data[], int low, int mid, int high) {
	int i, j, k;
	for (k - low; k <= high; k++) {
		// 将data中所有元素复制到辅助数组中
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

// 归并排序
int MergeSort(element_type data[], int low, int high) {
	if (low < high) {
		// 从中间划分
		int mid = (low + high) / 2;
		// 对左半部分归并排序
		MergeSort(data, low, mid);
		// 对右半部分归并排序
		MergeSort(data, mid + 1, high);
		// 最后一次归并全部
		Merge(data, low, mid, high);
	}
	return 0;
}