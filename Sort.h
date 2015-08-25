#include "stdafx.h"

/**	交换数组指定下标的元素
 *
 */
void swap (int * data, int left, int rigt){
	int temp = data[left];
	data[left] = data[rigt];
	data[rigt] = temp;
}

/**	选择排序
 *	1.从data[1]~data[n-1]中选择最小的，与data[0]交换
 *	2.data起始地址后移
 */
void select_sort(int * data, int len) {
	for (int i = 0; i < len - 1; i++) {
		int min = i;
		for (int j = i + 1; j < len; j++) {
			if (data[j] < data[min]) {
				min = j;
			}
		}
		// 这里是一个小小的效率提升
		if (min != i) {
			swap(data, i, min);
		}
	}
}


/**	冒泡排序
 *	1.相邻元素比较，如果逆序，就交换，迭代一次把当前最大的放在了数组最后
 *	2.i从0到n-2，j从0到i-1
 */
void bubble_sort(int * data, int len) {
	for (int i = len - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (data[j] > data[j + 1]) {
				swap(data, j, j + 1);
			}
		}
	}
}


/**	梳排序
 *	1.先把相隔一定距离的元素做比较，逆序则交换，距离值等比减小，直到距离小至3时,以1递减
 *	2.再做冒泡排序，加入一个标记，如果某轮没有交换元素，说明已经有序
 */
void comb_sort(int * data, int len) {
	bool swapped = true;
	for (int step = len / 1.25; step >= 1 || swapped; step /= 1.25) {
		swapped = false;
		for (int i = 0; step + i < len; i++) {
			if (data[i] > data[i + step]) {
				swap(data, i, i + step);
				swapped = true;
			}
		}
	}
}


/**	插入排序
 *	1.从第二个元素开始，从已排好序的数组中找到合适的位置
 *	2.把该位置后的元素后移一位，插入到该位置
 */
void insert_sort(int * data, int len) {
	for (int i = 1; i < len; i++) {
		// 探测式检查
		if (data[i - 1] > data[i]) {
			int temp = data[i];
			int j = i - 1;
			// 凡是大于新元素的都后移一位
			for (; j >= 0 && data[j] > temp; j--)
				data[j + 1] = data[j];
			data[j + 1] = temp;
		}
	}
}


/**	希尔排序——分组插入排序
 *	1.先将整个待排元素序列分割成若干个子序列（由相隔某个“增量”的元素组成的）分别进行直接插入排序
 *	2.依次缩减增量再进行排序，
 *	3.待整个序列中的元素基本有序（增量足够小）时，再对全体元素进行一次直接插入排序
 */
void shell_sort(int * data, int len) {
	// 经验公式：step = 3 * idx + 1;
	for (int step = len / 2; step > 0; step /= 2) {
		// 在组内进行插入排序
		for (int i = step; i < len; i++) {
			// 探测式检查
			if (data[i - step] > data[i]) {
				int temp = data[i];
				int j = i - step;
				for (; j >= 0 && data[j] > temp; j -= step)
					data[j + step] = data[j];
				data[j + step] = temp;
			}
		}
	}
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