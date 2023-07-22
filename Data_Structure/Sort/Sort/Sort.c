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

// 插入排序
// 从 已排序的 后面的第一个位置向前对比，比前一位小，就交换位置
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

// 冒泡排序
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

// 希尔排序
// 希尔排序的思路是
// 对间隔相同的数据进行分组，先对各个分组分别使用插入排序进行预排序
// 每一趟预排序结束之后， 分组间隔会减小，然后再次分组进行预排序
// 直到间隔为 1 时，进行的就是直接插入排序
void shellSort(int* a, int size) {
	int gap = size;

	// 三循环预排序写法
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

	// 优化写法
	// Size > 1 就继续循环
	while (gap > 1) {
		// 用 gap = gap / 3 + 1   来对数据进行分组的间隔设置
		gap = gap / 3 + 1; // 每次进入大循环， gap 都会减小	且 gap 恒 >= 1，进入后变为 1 就是最后一次对整体的插入排序
		//如何分组？
		/*  一组数据		14个   14 / 3 + 1 ---> 5
		0	1	2	3	4	5	6	7	8	9	10	11	12	13
		67	34	29	91	65	98	56	67	86	34	89	53	80	13
		67					98					89					----第一组
			34					56					53				----第二组
				29					67					80			----第三组
					91					86					13		----第四组
						65					34						----第五组
		gap 就是分组标准 当前坐标 + 5 的分为一组
		*/

		for (int i = 0; i < size - gap; i++) {
			// 以下类似 插入排序的思想 就是对已经分过的每一组分别进行插入排序
			// 不过插入排序 没用 gap 分组（即 gap 为 1，所有数据为一组）
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

// 选择排序
void selectSort(int* a, int size) {
	// 优化版选择排序，一次选出两个数：最大值和最小值
	int left = 0;
	int right = size - 1;
	while (left < right) {
		int mini = left; // 记录最小值位置
		int maxi = left; // 记录最大值位置
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
			// 本操作是为了防止一下情况发生：
			// 即 left 位置 刚好是 最小值的位置
			// 但是在上述交换操作中，left 位置的值 被换走了，被换到了 maxi 位置
			// right 也是相同的道理
			// 所以如果 left 或 right 位置 已经被记录了 但是经过操作，相应位置的数据又被换走了
			// 就需要进行判断
			mini = maxi;
		}
		Swap(&a[mini], &a[right]);
		left++;
		right--;
	}
}

//// hoare快排单趟排序
//int hoarePartSort(int* a, int left, int right)
//{
//	int keyi = left;
//	while (left < right)
//	{
//		// right 找比 key 小的	要控制 right > left 防止越界
//		// right 位置比 key 大就进循环，可以控制当 right 比 key 小的时候，right停止不再移动
//		while (a[right] >= a[keyi] && left < right)
//			right--;
//
//		// left 找比 key 大的		要控制 left < right 防止越界
//		// left 位置比 key 小就进循环，可以控制当 left 比 key 大的时候，left停止不再移动
//		while (a[left] <= a[keyi] && left < right)
//			left++;
//
//		Swap(&a[left], &a[right]);
//	}
//	// 相遇时，相遇位置的值 与 key 交换
//	Swap(&a[left], &a[keyi]);
//	// 为了保证相遇位置的值 恒小于 key，所以控制 right 先移动，因为 right 找小，找到 或者 与left相遇 才会停止
//	// 排降序同理
//
//	return left;		// 为快排打基础，返回相遇点
//}
//
//int pitPartSort(int* a, int left, int right)
//{
//	int key = a[left];
//	int pit = left;
//	while (left < right)
//	{
//		while (left < right && a[right] >= key)
//		{// right 找小
//			--right;
//		}
//		//换坑操作
//		a[pit] = a[right];		// 找到小，把这个值放到坑里
//		pit = right;			// 然后把刚刚那个值的位置作为坑
//
//		while (left < right && a[left] <= key)
//		{// left 找大
//			++left;
//		}
//		//换坑操作
//		a[pit] = a[left];		// 找到大，把这个值放到坑里
//		pit = left;			// 然后把刚刚那个值的位置作为坑
//	}
//
//	a[pit] = key;		//退出循环即相遇，相遇位置实际为坑，key放入坑里
//
//	return pit;			//为快排返回 当前key位置
//}
//
//// 前后指针
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
//// 快速排序
//void quickSort(int* a, int begin, int end)
//{
//	if (begin >= end)
//		return;
//
//	//int keyi = hoarePartSort(a, begin, end);		//hoare 法
//	//int keyi = pikPartSort(a, begin, end);			//挖坑 法
//	int keyi = PartSort3(a, begin, end);
//	quickSort(a, begin, keyi - 1);
//	quickSort(a, keyi + 1, end);
//}

void AdjustDown(HPDataType* data, size_t size, size_t root) {
	assert(data);
	// 向下调整，需要对比父亲节点和孩子节点的大小
	// 如果父亲节点小于孩子节点就需要交换位置
	// 但是父亲节点一般情况下会有两个孩子节点  就需要判断出两个孩子节点中 更大的那个孩子节点 与 父亲节点进行交换
	// 为了方便判断 我们直接假设 左孩子节点就是大的孩子节点
	// 如果左孩子节点不是大的孩子节点  再让右孩子结点设置为大的孩子节点
	// 然后再判断 父亲节点和这个大的孩子节点的大小
	// 然后再进行交换

	// 循环结束的条件是 ：child > size   当孩子节点位置大于实际拥有节点数量时停止
	size_t parent = root;
	size_t child = parent * 2 + 1;
	while (child < size) {
		// 判断 大的孩子节点是否正确
		// 首先有 右孩子，然后才能判断左右孩子的大小，所以得先判断 child + 1 < size
		if (child + 1 < size && data[child] > data[child + 1]) {
			++child;
		}

		// 父亲节点大 就 交换
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

void HeapSort(int* data, size_t size) { // 直接对 数组建堆
	assert(data);

	// 向上调整建堆
	/*for (int i = 0; i < size; i++)
	{
	AdjustUp(data, i);
	}*/

	// 向下调整建堆
	// 两种调整方式都有一个共同的前提：除了需要调整的那个节点，二叉树已经是堆
	// 所以向下调整不能从 整个二叉树的root 开始
	// 要从 最后一个非叶子节点开始向下调整 （为什么是最后一个非叶子节点：因为叶子节点没有孩子节点不能再向下调整了）
	// 最后一个非叶子节点的位置是，最后一个节点的父亲节点

	int j = (size - 1 - 1) / 2; //最后一个非叶子结点的位置
	for (j; j >= 0; j--) {
		AdjustDown(data, size, j);
	}

	// 大根堆建好，排序
	// 可以用 堆删除数据的思想
	// 将大根堆的 根 与 最后一个节点 交换位置
	// 然后从根向下调整
	// 然后 再将根 与 倒数第二个节点 交换位置
	// 然后从根向下调整  以此类推
	size_t end = size - 1; // end 先从最后一个节点位置开始
	while (end > 0) {
		Swap(&data[0], &data[end]); // 根节点 与 end节点 交换位置
		AdjustDown(data, end, 0);	// 从根节点向下调整 调整到 最后结束
		--end;						// end 位置 减一
	}
}

// hoare快排单趟排序
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

// 前后指针
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

// 快速排序
void quickSort2(int* a, int begin, int end) {
	if (begin >= end)
		return;

	//int keyi = hoarePartSort(a, begin, end);		//hoare 法
	//int keyi = pikPartSort(a, begin, end);			//挖坑 法
	int keyi = prevcurPartSort(a, begin, end);
	quickSort2(a, begin, keyi - 1);
	quickSort2(a, keyi + 1, end);
}

// 快排的两种优化方法
// 1. 三数取中	（首 尾 中，三个位置取 中间大小的作为 key）
// 不需要在原函数比较三数大小在修改代码什么的
// 只需要 再写一个函数 取中间大小的位置
// 然后在快排函数中将其与left 位置换位就可以了

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

// 三数取中快速排序
void midQuickSort(int* a, int begin, int end) {
	if (begin >= end)
		return;

	int midi = getMidIndex(a, begin, end);
	Swap(&a[midi], &a[begin]);

	//int keyi = hoarePartSort(a, begin, end);		//hoare 法
	//int keyi = pikPartSort(a, begin, end);			//挖坑 法
	int keyi = prevcurPartSort(a, begin, end);
	midQuickSort(a, begin, keyi - 1);
	midQuickSort(a, keyi + 1, end);
}

// 2. 小区间优化(当 left - right 小于一定值的时候，不再使用快排递归，而使用插入排序)
// 当 left - right 小于一定值时，即代表 需要排序的数据没有那么多
// 数据少时，再调用递归的话 浪费资源
// 所以当 left - right 小于一定值时，使用插入排序会更好一些

// 小区间优化 快速排序
void minQuickSort(int* a, int begin, int end) {
	if (begin >= end)
		return;
	if (begin - end >= 30) { //当 需要排序的数据小于 30 就用插入排序
		insertSort(a, begin - end);
	}
	else {
		//int keyi = hoarePartSort(a, begin, end);		//hoare 法
		//int keyi = pikPartSort(a, begin, end);			//挖坑 法
		int keyi = prevcurPartSort(a, begin, end);
		minQuickSort(a, begin, keyi - 1);
		minQuickSort(a, keyi + 1, end);
	}
}

// 非递归快排
// 非递归快排 需要使用栈实现
// 用栈 存入需要排序数据的首位区间
// 每排一次序，就将 keyi 的 左、右区间入栈（区间只有一个数不用入）
//
void non_recursive_QuickSort(int* a, int begin, int end) {
	Stack qSortst;
	StackInit(&qSortst);
	StackPush(&qSortst, begin); // 压入需要排序的区间的 首元素位置
	StackPush(&qSortst, end);	// 压入需要排序的区间的 末元素位置

	while (!StackEmpty(&qSortst)) {		// 栈为空表示排序完成
		int right = StackTop(&qSortst); // 因为后压入末元素位置，所以栈顶为末元素位置，作为 right
		StackPop(&qSortst);				// 取栈顶后 出栈
		int left = StackTop(&qSortst);	// 此时栈顶为首元素位置，作为 left
		StackPop(&qSortst);				// 出栈

		int keyi = prevcurPartSort(a, left, right); // 对 left ~ right 进行单趟排序
		if (left < keyi - 1) {						// keyi的左区间元素数量 不小于 1，再压入左区间的范围
			StackPush(&qSortst, left);
			StackPush(&qSortst, keyi - 1);
		}
		if (right > keyi + 1) { // keyi的右区间元素数量 不小于 1，再压入右区间的范围
			StackPush(&qSortst, keyi + 1);
			StackPush(&qSortst, right);
		}
	}
}

void _margeSort(int* a, int begin, int end, int* tmp) {
	if (begin >= end)
		return;

	// 细分，直到 分为一个一个的数据
	// 然后归并
	int mid = (begin + end) / 2;
	_margeSort(a, begin, mid, tmp);
	_margeSort(a, mid + 1, end, tmp);

	// 归并
	//printf("归并[%d,%d][%d,%d] \n", begin, mid, mid + 1, end);
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
		// 间距为gap是一组，两两归并
		for (int i = 0; i < n; i += 2 * gap) {
			int begin1 = i, end1 = i + gap - 1;
			int begin2 = i + gap, end2 = i + 2 * gap - 1;
			// end1 越界，修正
			if (end1 >= n)
				end1 = n - 1;

			// begin2 越界，第二个区间不存在
			if (begin2 >= n) {
				begin2 = n;
				end2 = n - 1;
			}

			// begin2 ok， end2越界，修正end2即可
			if (begin2 < n && end2 >= n)
				end2 = n - 1;

			// 条件断点
			if (begin1 == 8 && end1 == 9 && begin2 == 9 && end2 == 9) {
				int x = 0;
			}

			printf("归并[%d,%d][%d,%d]\n", begin1, end1, begin2, end2);

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

// 计数排序
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
