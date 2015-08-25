#include "stdafx.h"

/**	��������ָ���±��Ԫ��
 *
 */
void swap (int * data, int left, int rigt){
	int temp = data[left];
	data[left] = data[rigt];
	data[rigt] = temp;
}

/**	ѡ������
 *	1.��data[1]~data[n-1]��ѡ����С�ģ���data[0]����
 *	2.data��ʼ��ַ����
 */
void select_sort(int * data, int len) {
	for (int i = 0; i < len - 1; i++) {
		int min = i;
		for (int j = i + 1; j < len; j++) {
			if (data[j] < data[min]) {
				min = j;
			}
		}
		// ������һ��СС��Ч������
		if (min != i) {
			swap(data, i, min);
		}
	}
}


/**	ð������
 *	1.����Ԫ�رȽϣ�������򣬾ͽ���������һ�ΰѵ�ǰ���ķ������������
 *	2.i��0��n-2��j��0��i-1
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


/**	������
 *	1.�Ȱ����һ�������Ԫ�����Ƚϣ������򽻻�������ֵ�ȱȼ�С��ֱ������С��3ʱ,��1�ݼ�
 *	2.����ð�����򣬼���һ����ǣ����ĳ��û�н���Ԫ�أ�˵���Ѿ�����
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


/**	��������
 *	1.�ӵڶ���Ԫ�ؿ�ʼ�������ź�����������ҵ����ʵ�λ��
 *	2.�Ѹ�λ�ú��Ԫ�غ���һλ�����뵽��λ��
 */
void insert_sort(int * data, int len) {
	for (int i = 1; i < len; i++) {
		// ̽��ʽ���
		if (data[i - 1] > data[i]) {
			int temp = data[i];
			int j = i - 1;
			// ���Ǵ�����Ԫ�صĶ�����һλ
			for (; j >= 0 && data[j] > temp; j--)
				data[j + 1] = data[j];
			data[j + 1] = temp;
		}
	}
}


/**	ϣ�����򡪡������������
 *	1.�Ƚ���������Ԫ�����зָ�����ɸ������У������ĳ������������Ԫ����ɵģ��ֱ����ֱ�Ӳ�������
 *	2.�������������ٽ�������
 *	3.�����������е�Ԫ�ػ������������㹻С��ʱ���ٶ�ȫ��Ԫ�ؽ���һ��ֱ�Ӳ�������
 */
void shell_sort(int * data, int len) {
	// ���鹫ʽ��step = 3 * idx + 1;
	for (int step = len / 2; step > 0; step /= 2) {
		// �����ڽ��в�������
		for (int i = step; i < len; i++) {
			// ̽��ʽ���
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


/**	��������
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

/**	������
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
		// ����� i < end ǧ���������
		if (i < end && data[i] < data[i + 1])
			i++;
		if (temp > data[i])
			break;
		data[start] = data[i];
		start = i;
	}
	data[start] = temp;
}


/**	�鲢����
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
	// ��������ԭʼ���ݼ�
	for (i = left; i <= rigt; i++)
		data[i] = coll[i];
}