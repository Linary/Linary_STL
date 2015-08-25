#include "stdafx.h"

/**	交换数组指定下标的元素
 *
 */
void swap (int * data, int left, int rigt){
	int temp = data[left];
	data[left] = data[rigt];
	data[rigt] = temp;
}

/**	快速排序
 */
void quick_sort(int * data, int len) {
	if (len <= 1)
		return ;
	int left = 0, rigt = len - 1;
	int pivot = data[left];
	while (left < rigt) {
		for (; left < rigt; rigt--) {
			if (data[rigt] < pivot) {
				data[left++] = data[rigt];
				break;
			}
		}
		for (; left < rigt; left++) {
			if (data[left] > pivot) {
				data[rigt--] = data[left];
				break;
			}
		}
	}
	data[left] = pivot;
	quick_sort(data, left);
	quick_sort(data + left + 1, len - left - 1);
}

/**	堆排序
 */
void heap_adjust(int * data, int start, int end);
void heap_sort(int * data, int len) {
	if (data == NULL || len <= 1)
		return ;

	for (int i = len / 2 - 1; i >= 0; i--)
		heap_adjust(data, i, len - 1);
	for (int i = len - 1; i > 0; i--) {
		swap(data, 0, i);
		heap_adjust(data, 0, i - 1);
	}
}

void heap_adjust(int * data, int start, int end) {
	int temp = data[start];
	for (int i = start * 2 + 1; i <= end; i = i * 2 + 1) {
		// 这里的 i < end 千万别忘记了
		if (i < end && data[i] < data[i + 1])
			i++;
		if (temp > data[i])
			break;
		data[start] = data[i];
		start = i;
	}
	data[start] = temp;
}


/**	归并排序
 */
void divide(int * coll, int * data, int left, int rigt);
void merge(int * data, int * coll, int left, int mid, int rigt);
void merge_sort(int * data, int len) {
	if (data == NULL)
		return ;
	int * coll = new int[len];
	divide(coll, data, 0, len - 1);
	delete [] coll;
}

void divide(int * coll, int * data, int left, int rigt) {
	if (left == rigt)
		return ;
	int mid = (left + rigt) / 2;
	divide(coll, data, left, mid);
	divide(coll, data, mid + 1, rigt);
	merge(data, coll, left, mid, rigt);
}

void merge(int * data, int * coll, int left, int mid, int rigt) {
	int i = left, j = mid + 1, k = left;
	for (; i <= mid && j <= rigt; k++) {
		if (data[i] < data[j])
			coll[k] = data[i++];
		else
			coll[k] = data[j++];
	}
	while (i <= mid)
		coll[k++] = data[i++];
	while (j <= rigt)
		coll[k++] = data[j++];
	// 拷贝回至原始数据集
	for (i = left; i <= rigt; i++)
		data[i] = coll[i];
}