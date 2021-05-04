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
}