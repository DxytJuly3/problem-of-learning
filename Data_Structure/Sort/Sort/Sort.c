#define _CRT_SECURE_NO_WARNINGS 1

#include "Sort.h"


void printArr(int *a, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

void Swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

// 插入排序
void insertSort(int* a, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		int end = i;
		int tmp = a[end + 1];
		while (end >= 0)
		{
			if (tmp < a[end])
			{
				a[end + 1] = a[end];
				end--;
			}
			else
			{
				// a[end - 1] = tmp;
				break;
			}
		}

		a[end + 1] = tmp;
	}
}

// 冒泡排序
void bubbleSort(int* a, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		int flag = 0;
		for (int j = 1; j < size - i; j++)
		{
			if (a[j - 1] > a[j])
			{
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
void shellSort(int* a, int size)
{
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
	while (gap > 1)
	{
		// 用 gap = gap / 3 + 1   来对数据进行分组的间隔设置
		gap = gap / 3 + 1;			// 每次进入大循环， gap 都会减小	且 gap 恒 >= 1，进入后变为 1 就是最后一次对整体的插入排序
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
		
		for (int i = 0; i < size - gap; i++)
		{
			// 以下类似 插入排序的思想 就是对已经分过的每一组分别进行插入排序
			// 不过插入排序 没用 gap 分组（即 gap 为 1，所有数据为一组）
			// 
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
	}
}

// 选择排序
void selectSort(int* a, int size)
{
	// 优化版选择排序，一次选出两个数：最大值和最小值
	int left = 0;
	int right = size - 1;
	while (left < right)
	{
		int mini = left;		// 记录最小值位置
		int maxi = left;		// 记录最大值位置
		for (int i = left + 1; i < right + 1; i++)
		{
			if (a[i] > a[maxi])
			{
				maxi = i;
			}
			if (a[i] < a[mini])
			{
				mini = i;
			}
		}
		Swap(&a[maxi], &a[left]);
		if (left == mini)
		{
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

// hoare快排单趟排序
int hoarePartSort(int* a, int left, int right)
{
	int keyi = left;
	while (left < right)
	{
		// right 找比 key 小的	要控制 right > left 防止越界
		// right 位置比 key 大就进循环，可以控制当 right 比 key 小的时候，right停止不再移动
		while (a[right] >= a[keyi] && left < right)
			right--;

		// left 找比 key 大的		要控制 left < right 防止越界
		// left 位置比 key 小就进循环，可以控制当 left 比 key 大的时候，left停止不再移动
		while (a[left] <= a[keyi] && left < right)
			left++;

		Swap(&a[left], &a[right]);
	}
	// 相遇时，相遇位置的值 与 key 交换
	Swap(&a[left], &a[keyi]);
	// 为了保证相遇位置的值 恒小于 key，所以控制 right 先移动，因为 right 找小，找到 或者 与left相遇 才会停止 
	// 排降序同理

	return left;		// 为快排打基础，返回相遇点
}

// hoare快速排序
void hoareQuickSort(int* a, int begin, int end)
{
	if (begin >= end)
		return;

	int keyi = hoarePartSort(a, begin, end);
	hoareQuickSort(a, begin, keyi - 1);
	hoareQuickSort(a, keyi + 1, end);
}

void AdjustDown(HPDataType* data, size_t size, size_t root)
{
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
	while (child < size)
	{
		// 判断 大的孩子节点是否正确
		// 首先有 右孩子，然后才能判断左右孩子的大小，所以得先判断 child + 1 < size
		if (child + 1 < size && data[child] > data[child + 1])
		{
			++child;
		}

		// 父亲节点大 就 交换
		if (data[parent] > data[child])
		{
			Swap(&data[parent], &data[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void HeapSort(int *data, size_t size)
{// 直接对 数组建堆
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
	for (j; j >= 0; j--)
	{
		AdjustDown(data, size, j);
	}


	// 大根堆建好，排序
	// 可以用 堆删除数据的思想
	// 将大根堆的 根 与 最后一个节点 交换位置
	// 然后从根向下调整
	// 然后 再将根 与 倒数第二个节点 交换位置
	// 然后从根向下调整  以此类推
	size_t end = size - 1;   // end 先从最后一个节点位置开始
	while (end > 0)
	{
		Swap(&data[0], &data[end]); // 根节点 与 end节点 交换位置
		AdjustDown(data, end, 0);   // 从根节点向下调整 调整到 最后结束
		--end;                      // end 位置 减一
	}

}