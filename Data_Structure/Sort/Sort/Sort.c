#define _CRT_SECURE_NO_WARNINGS 1

#include "Sort.h"

void printArr(int* a, int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

void Swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

// ��������
// �� ������� ����ĵ�һ��λ����ǰ�Աȣ���ǰһλС���ͽ���λ��
void insertSort(int* a, int size) {
	for (int i = 0; i < size - 1; i++) {
		int end = i;
		int tmp = a[end + 1];
		while (end >= 0) {
			if (tmp < a[end]) {
				a[end + 1] = a[end];
				end--;
			}
			else {
				// a[end - 1] = tmp;
				break;
			}
		}

		a[end + 1] = tmp;
	}
}

// ð������
void bubbleSort(int* a, int size) {
	for (int i = 0; i < size - 1; i++) {
		int flag = 0;
		for (int j = 1; j < size - i; j++) {
			if (a[j - 1] > a[j]) {
				Swap(&a[j - 1], &a[j]);
				flag = 1;
			}
		}
		if (flag == 0)
			break;
	}
}

// ϣ������
// ϣ�������˼·��
// �Լ����ͬ�����ݽ��з��飬�ȶԸ�������ֱ�ʹ�ò����������Ԥ����
// ÿһ��Ԥ�������֮�� ���������С��Ȼ���ٴη������Ԥ����
// ֱ�����Ϊ 1 ʱ�����еľ���ֱ�Ӳ�������
void shellSort(int* a, int size) {
	int gap = size;

	// ��ѭ��Ԥ����д��
	/*gap = gap / 3 + 1;
	for (int i = 0; i < gap; i++)
	{
		for (int j = i; j < size - gap; j += gap)
		{
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0)
			{
				if (a[end] < tmp)
				{
					a[end + gap] = a[end];
					end -= gap;
				}
				else
				{
					break;
				}
			}
			a[end + gap] = tmp;
		}
	}*/

	// �Ż�д��
	// Size > 1 �ͼ���ѭ��
	while (gap > 1) {
		// �� gap = gap / 3 + 1   �������ݽ��з���ļ������
		gap = gap / 3 + 1; // ÿ�ν����ѭ���� gap �����С	�� gap �� >= 1��������Ϊ 1 �������һ�ζ�����Ĳ�������
		//��η��飿
		/*  һ������		14��   14 / 3 + 1 ---> 5
		0	1	2	3	4	5	6	7	8	9	10	11	12	13
		67	34	29	91	65	98	56	67	86	34	89	53	80	13
		67					98					89					----��һ��
			34					56					53				----�ڶ���
				29					67					80			----������
					91					86					13		----������
						65					34						----������
		gap ���Ƿ����׼ ��ǰ���� + 5 �ķ�Ϊһ��
		*/

		for (int i = 0; i < size - gap; i++) {
			// �������� ���������˼�� ���Ƕ��Ѿ��ֹ���ÿһ��ֱ���в�������
			// ������������ û�� gap ���飨�� gap Ϊ 1����������Ϊһ�飩
			//
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0) {
				if (a[end] < tmp) {
					a[end + gap] = a[end];
					end -= gap;
				}
				else {
					break;
				}
			}
			a[end + gap] = tmp;
		}
	}
}

// ѡ������
void selectSort(int* a, int size) {
	// �Ż���ѡ������һ��ѡ�������������ֵ����Сֵ
	int left = 0;
	int right = size - 1;
	while (left < right) {
		int mini = left; // ��¼��Сֵλ��
		int maxi = left; // ��¼���ֵλ��
		for (int i = left + 1; i < right + 1; i++) {
			if (a[i] > a[maxi]) {
				maxi = i;
			}
			if (a[i] < a[mini]) {
				mini = i;
			}
		}
		Swap(&a[maxi], &a[left]);
		if (left == mini) {
			// ��������Ϊ�˷�ֹһ�����������
			// �� left λ�� �պ��� ��Сֵ��λ��
			// �������������������У�left λ�õ�ֵ �������ˣ��������� maxi λ��
			// right Ҳ����ͬ�ĵ���
			// ������� left �� right λ�� �Ѿ�����¼�� ���Ǿ�����������Ӧλ�õ������ֱ�������
			// ����Ҫ�����ж�
			mini = maxi;
		}
		Swap(&a[mini], &a[right]);
		left++;
		right--;
	}
}

//// hoare���ŵ�������
//int hoarePartSort(int* a, int left, int right)
//{
//	int keyi = left;
//	while (left < right)
//	{
//		// right �ұ� key С��	Ҫ���� right > left ��ֹԽ��
//		// right λ�ñ� key ��ͽ�ѭ�������Կ��Ƶ� right �� key С��ʱ��rightֹͣ�����ƶ�
//		while (a[right] >= a[keyi] && left < right)
//			right--;
//
//		// left �ұ� key ���		Ҫ���� left < right ��ֹԽ��
//		// left λ�ñ� key С�ͽ�ѭ�������Կ��Ƶ� left �� key ���ʱ��leftֹͣ�����ƶ�
//		while (a[left] <= a[keyi] && left < right)
//			left++;
//
//		Swap(&a[left], &a[right]);
//	}
//	// ����ʱ������λ�õ�ֵ �� key ����
//	Swap(&a[left], &a[keyi]);
//	// Ϊ�˱�֤����λ�õ�ֵ ��С�� key�����Կ��� right ���ƶ�����Ϊ right ��С���ҵ� ���� ��left���� �Ż�ֹͣ
//	// �Ž���ͬ��
//
//	return left;		// Ϊ���Ŵ����������������
//}
//
//int pitPartSort(int* a, int left, int right)
//{
//	int key = a[left];
//	int pit = left;
//	while (left < right)
//	{
//		while (left < right && a[right] >= key)
//		{// right ��С
//			--right;
//		}
//		//���Ӳ���
//		a[pit] = a[right];		// �ҵ�С�������ֵ�ŵ�����
//		pit = right;			// Ȼ��Ѹո��Ǹ�ֵ��λ����Ϊ��
//
//		while (left < right && a[left] <= key)
//		{// left �Ҵ�
//			++left;
//		}
//		//���Ӳ���
//		a[pit] = a[left];		// �ҵ��󣬰����ֵ�ŵ�����
//		pit = left;			// Ȼ��Ѹո��Ǹ�ֵ��λ����Ϊ��
//	}
//
//	a[pit] = key;		//�˳�ѭ��������������λ��ʵ��Ϊ�ӣ�key�������
//
//	return pit;			//Ϊ���ŷ��� ��ǰkeyλ��
//}
//
//// ǰ��ָ��
//int PartSort3(int* a, int left, int right)
//{
//	int key = left;
//	int prev = left;
//	int cur = prev + 1;
//	while (cur <= right)
//	{
//		while (a[cur] < a[key] && a[cur] != a[++prev])
//			Swap(&a[cur], &a[prev]);
//
//		++cur;
//	}
//	Swap(&a[prev], &a[key]);
//
//	return prev;
//}
//
//// ��������
//void quickSort(int* a, int begin, int end)
//{
//	if (begin >= end)
//		return;
//
//	//int keyi = hoarePartSort(a, begin, end);		//hoare ��
//	//int keyi = pikPartSort(a, begin, end);			//�ڿ� ��
//	int keyi = PartSort3(a, begin, end);
//	quickSort(a, begin, keyi - 1);
//	quickSort(a, keyi + 1, end);
//}

void AdjustDown(HPDataType* data, size_t size, size_t root) {
	assert(data);
	// ���µ�������Ҫ�Աȸ��׽ڵ�ͺ��ӽڵ�Ĵ�С
	// ������׽ڵ�С�ں��ӽڵ����Ҫ����λ��
	// ���Ǹ��׽ڵ�һ������»����������ӽڵ�  ����Ҫ�жϳ��������ӽڵ��� ������Ǹ����ӽڵ� �� ���׽ڵ���н���
	// Ϊ�˷����ж� ����ֱ�Ӽ��� ���ӽڵ���Ǵ�ĺ��ӽڵ�
	// ������ӽڵ㲻�Ǵ�ĺ��ӽڵ�  �����Һ��ӽ������Ϊ��ĺ��ӽڵ�
	// Ȼ�����ж� ���׽ڵ�������ĺ��ӽڵ�Ĵ�С
	// Ȼ���ٽ��н���

	// ѭ�������������� ��child > size   �����ӽڵ�λ�ô���ʵ��ӵ�нڵ�����ʱֹͣ
	size_t parent = root;
	size_t child = parent * 2 + 1;
	while (child < size) {
		// �ж� ��ĺ��ӽڵ��Ƿ���ȷ
		// ������ �Һ��ӣ�Ȼ������ж����Һ��ӵĴ�С�����Ե����ж� child + 1 < size
		if (child + 1 < size && data[child] > data[child + 1]) {
			++child;
		}

		// ���׽ڵ�� �� ����
		if (data[parent] > data[child]) {
			Swap(&data[parent], &data[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else {
			break;
		}
	}
}

void HeapSort(int* data, size_t size) { // ֱ�Ӷ� ���齨��
	assert(data);

	// ���ϵ�������
	/*for (int i = 0; i < size; i++)
	{
	AdjustUp(data, i);
	}*/

	// ���µ�������
	// ���ֵ�����ʽ����һ����ͬ��ǰ�᣺������Ҫ�������Ǹ��ڵ㣬�������Ѿ��Ƕ�
	// �������µ������ܴ� ������������root ��ʼ
	// Ҫ�� ���һ����Ҷ�ӽڵ㿪ʼ���µ��� ��Ϊʲô�����һ����Ҷ�ӽڵ㣺��ΪҶ�ӽڵ�û�к��ӽڵ㲻�������µ����ˣ�
	// ���һ����Ҷ�ӽڵ��λ���ǣ����һ���ڵ�ĸ��׽ڵ�

	int j = (size - 1 - 1) / 2; //���һ����Ҷ�ӽ���λ��
	for (j; j >= 0; j--) {
		AdjustDown(data, size, j);
	}

	// ����ѽ��ã�����
	// ������ ��ɾ�����ݵ�˼��
	// ������ѵ� �� �� ���һ���ڵ� ����λ��
	// Ȼ��Ӹ����µ���
	// Ȼ�� �ٽ��� �� �����ڶ����ڵ� ����λ��
	// Ȼ��Ӹ����µ���  �Դ�����
	size_t end = size - 1; // end �ȴ����һ���ڵ�λ�ÿ�ʼ
	while (end > 0) {
		Swap(&data[0], &data[end]); // ���ڵ� �� end�ڵ� ����λ��
		AdjustDown(data, end, 0);	// �Ӹ��ڵ����µ��� ������ ������
		--end;						// end λ�� ��һ
	}
}

// hoare���ŵ�������
int hoarePartSort2(int* a, int left, int right) {
	int keyi = left;
	while (left < right) {
		while (a[right] >= a[keyi] && left < right)
			--right;
		while (a[left] <= a[keyi] && left < right)
			++left;
		Swap(&a[right], &a[left]);
	}
	Swap(&a[left], &a[keyi]);

	return left;
}

int pitPartSort2(int* a, int left, int right) {
	int key = a[left];
	int pit = left;
	while (left < right) {
		while (a[right] >= key && left < right)
			--right;
		a[pit] = a[right];
		pit = right;
		while (a[left] <= key && left < right)
			++left;
		a[pit] = a[left];
		pit = left;
	}

	a[left] = key; // a[pit] = key;

	return left; // return pit;
}

// ǰ��ָ��
int prevcurPartSort(int* a, int left, int right) {
	int keyi = left;
	int prev = left;
	int cur = left + 1;
	while (cur <= right) {
		if (a[cur] < a[keyi])
			Swap(&a[cur], &a[++prev]);

		++cur;
	}

	Swap(&a[prev], &a[keyi]);

	return prev;
}

// ��������
void quickSort2(int* a, int begin, int end) {
	if (begin >= end)
		return;

	//int keyi = hoarePartSort(a, begin, end);		//hoare ��
	//int keyi = pikPartSort(a, begin, end);			//�ڿ� ��
	int keyi = prevcurPartSort(a, begin, end);
	quickSort2(a, begin, keyi - 1);
	quickSort2(a, keyi + 1, end);
}

// ���ŵ������Ż�����
// 1. ����ȡ��	���� β �У�����λ��ȡ �м��С����Ϊ key��
// ����Ҫ��ԭ�����Ƚ�������С���޸Ĵ���ʲô��
// ֻ��Ҫ ��дһ������ ȡ�м��С��λ��
// Ȼ���ڿ��ź����н�����left λ�û�λ�Ϳ�����

int getMidIndex(int* a, int left, int right) {
	int mid = left + (right - left) / 2;
	if (a[left] < a[mid]) {
		if (a[right] > a[mid])
			return mid;
		else if (a[right] < a[left])
			return left;
		else //(a[mid] > a[right] >  a[left])
			return right;
	}
	else // (a[left] > a[mid])
	{
		if (a[right] < a[mid])
			return mid;
		else if (a[right] > a[left])
			return left;
		else //(a[mid] < a[right] <  a[left])
			return right;
	}
}

// ����ȡ�п�������
void midQuickSort(int* a, int begin, int end) {
	if (begin >= end)
		return;

	int midi = getMidIndex(a, begin, end);
	Swap(&a[midi], &a[begin]);

	//int keyi = hoarePartSort(a, begin, end);		//hoare ��
	//int keyi = pikPartSort(a, begin, end);			//�ڿ� ��
	int keyi = prevcurPartSort(a, begin, end);
	midQuickSort(a, begin, keyi - 1);
	midQuickSort(a, keyi + 1, end);
}

// 2. С�����Ż�(�� left - right С��һ��ֵ��ʱ�򣬲���ʹ�ÿ��ŵݹ飬��ʹ�ò�������)
// �� left - right С��һ��ֵʱ�������� ��Ҫ���������û����ô��
// ������ʱ���ٵ��õݹ�Ļ� �˷���Դ
// ���Ե� left - right С��һ��ֵʱ��ʹ�ò�����������һЩ

// С�����Ż� ��������
void minQuickSort(int* a, int begin, int end) {
	if (begin >= end)
		return;
	if (begin - end >= 30) { //�� ��Ҫ���������С�� 30 ���ò�������
		insertSort(a, begin - end);
	}
	else {
		//int keyi = hoarePartSort(a, begin, end);		//hoare ��
		//int keyi = pikPartSort(a, begin, end);			//�ڿ� ��
		int keyi = prevcurPartSort(a, begin, end);
		minQuickSort(a, begin, keyi - 1);
		minQuickSort(a, keyi + 1, end);
	}
}

// �ǵݹ����
// �ǵݹ���� ��Ҫʹ��ջʵ��
// ��ջ ������Ҫ�������ݵ���λ����
// ÿ��һ���򣬾ͽ� keyi �� ����������ջ������ֻ��һ���������룩
//
void non_recursive_QuickSort(int* a, int begin, int end) {
	Stack qSortst;
	StackInit(&qSortst);
	StackPush(&qSortst, begin); // ѹ����Ҫ���������� ��Ԫ��λ��
	StackPush(&qSortst, end);	// ѹ����Ҫ���������� ĩԪ��λ��

	while (!StackEmpty(&qSortst)) {		// ջΪ�ձ�ʾ�������
		int right = StackTop(&qSortst); // ��Ϊ��ѹ��ĩԪ��λ�ã�����ջ��ΪĩԪ��λ�ã���Ϊ right
		StackPop(&qSortst);				// ȡջ���� ��ջ
		int left = StackTop(&qSortst);	// ��ʱջ��Ϊ��Ԫ��λ�ã���Ϊ left
		StackPop(&qSortst);				// ��ջ

		int keyi = prevcurPartSort(a, left, right); // �� left ~ right ���е�������
		if (left < keyi - 1) {						// keyi��������Ԫ������ ��С�� 1����ѹ��������ķ�Χ
			StackPush(&qSortst, left);
			StackPush(&qSortst, keyi - 1);
		}
		if (right > keyi + 1) { // keyi��������Ԫ������ ��С�� 1����ѹ��������ķ�Χ
			StackPush(&qSortst, keyi + 1);
			StackPush(&qSortst, right);
		}
	}
}

void _margeSort(int* a, int begin, int end, int* tmp) {
	if (begin >= end)
		return;

	// ϸ�֣�ֱ�� ��Ϊһ��һ��������
	// Ȼ��鲢
	int mid = (begin + end) / 2;
	_margeSort(a, begin, mid, tmp);
	_margeSort(a, mid + 1, end, tmp);

	// �鲢
	//printf("�鲢[%d,%d][%d,%d] \n", begin, mid, mid + 1, end);
	int begin1 = begin, end1 = mid;
	int begin2 = mid + 1, end2 = end;
	int index = begin;
	while (begin1 <= end1 && begin2 <= end2) {
		if (a[begin1] < a[begin2]) {
			tmp[index++] = a[begin1++];
		}
		else {
			tmp[index++] = a[begin2++];
		}
	}

	while (begin1 <= end1) {
		tmp[index++] = a[begin1++];
	}
	while (begin2 <= end2) {
		tmp[index++] = a[begin2++];
	}

	memcpy(a + begin, tmp + begin, sizeof(int) * (end - begin + 1));
}

void margeSort(int* a, int size) {
	int* tmp = (int*)malloc(sizeof(int) * size);
	if (tmp == NULL) {
		printf("margeSort fail\n");
		exit(-1);
	}

	_margeSort(a, 0, size - 1, tmp);

	free(tmp);
}

void MergeSortNonR(int* a, int n) {
	int* tmp = (int*)malloc(sizeof(int) * n);
	int gap = 1;

	while (gap < n) {
		// ���Ϊgap��һ�飬�����鲢
		for (int i = 0; i < n; i += 2 * gap) {
			int begin1 = i, end1 = i + gap - 1;
			int begin2 = i + gap, end2 = i + 2 * gap - 1;
			// end1 Խ�磬����
			if (end1 >= n)
				end1 = n - 1;

			// begin2 Խ�磬�ڶ������䲻����
			if (begin2 >= n) {
				begin2 = n;
				end2 = n - 1;
			}

			// begin2 ok�� end2Խ�磬����end2����
			if (begin2 < n && end2 >= n)
				end2 = n - 1;

			// �����ϵ�
			if (begin1 == 8 && end1 == 9 && begin2 == 9 && end2 == 9) {
				int x = 0;
			}

			printf("�鲢[%d,%d][%d,%d]\n", begin1, end1, begin2, end2);

			int index = i;
			while (begin1 <= end1 && begin2 <= end2) {
				if (a[begin1] < a[begin2])
					tmp[index++] = a[begin1++];
				else
					tmp[index++] = a[begin2++];
			}

			while (begin1 <= end1)
				tmp[index++] = a[begin1++];

			while (begin2 <= end2)
				tmp[index++] = a[begin2++];
		}
		memcpy(a, tmp, n * sizeof(int));
		//PrintArray(a, n);

		gap *= 2;
	}

	free(tmp);
}

// ��������
void CountSort(int* nums, int numsSize) {
	int max = nums[0];
	int min = nums[0];
	for (int i = 0; i < numsSize; i++) {
		if (nums[i] > max) {
			max = nums[i];
		}
		if (nums[i] < min) {
			min = nums[i];
		}
	}

	int* arr = (int*)malloc(sizeof(int) * (max - min + 1));
	assert(arr);
	memset(arr, 0, sizeof(int) * (max - min + 1));

	for (int i = 0; i < numsSize; i++) {
		arr[nums[i] - min]++;
	}

	int j = 0;
	for (int i = 0; i < (max - min + 1); i++) {
		while (arr[i]--) {
			nums[j++] = i + min;
		}
	}
}
