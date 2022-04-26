/*给你一个整数数组 nums，请你将该数组升序排列。
示例 1：

输入：nums = [5,2,3,1]
输出：[1,2,3,5]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sort-an-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

typedef int StDateType;

typedef struct Stack
{
	StDateType *data;
	int top;				// 栈顶位置
	int capacity;			// 栈的容量
}Stack;

// 栈的初始化
void StackInit(Stack* pSt);
// 栈的销毁
void StackDestroy(Stack* pSt);
// 压栈
void StackPush(Stack* pSt, StDateType x);
// 出栈
void StackPop(Stack* pSt);
// 判空
bool StackEmpty(Stack* pSt);
// 栈顶数据
StDateType StackTop(Stack* pSt);

// 栈的初始化
void StackInit(Stack* pSt)
{
	assert(pSt);

	pSt->data = NULL;
	pSt->top = 0;			// 栈顶初始位置定义 (top = -1, 先++后赋值; top = 0, 先赋值后++)
	pSt->capacity = 0;
}
// 栈的销毁
void StackDestroy(Stack* pSt)
{
	assert(pSt);

	free(pSt->data);
	pSt->data = NULL;
	pSt->top = pSt->capacity = 0;
}
// 压栈
void StackPush(Stack* pSt, StDateType x)
{
	assert(pSt);

	if (pSt->top == pSt->capacity)
	{
		int newCapacity = pSt->capacity == 0 ? 4 : pSt->capacity * 2;
		StDateType* tmp = (StDateType*)realloc(pSt->data, newCapacity * sizeof(StDateType));
		if (tmp == NULL)
		{
			printf("realloc failed\n");
			exit(-1);
		}
		else
			pSt->data = tmp;

		pSt->capacity = newCapacity;
	}

	pSt->data[pSt->top++] = x;
}
// 出栈
void StackPop(Stack* pSt)
{
	assert(pSt);
	assert(pSt->top > 0);

	--pSt->top;
}
// 判空
bool StackEmpty(Stack* pSt)
{
	assert(pSt);

	return pSt->top == 0;			// top 等于 0 栈为空，返回 true; 不等于 0 ，返回 false
}
// 栈顶数据
StDateType StackTop(Stack* pSt)
{
	assert(pSt);

	return pSt->data[pSt->top - 1];
}

void Swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
// 插入排序
void InsertSort(int* nums, int numsSize)
{
    for(int i = 0; i < numsSize - 1; i++)
    {
        int end = i;
        int tmp = nums[end + 1];
        while(end >= 0)
        {
            if(tmp < nums[end])
            {
                nums[end + 1] = nums[end];
                end--;
            }
            else
            {
                break;
            }
        }
        nums[end + 1] = tmp;
    }
}
// 冒泡排序
void BubbleSort(int* nums, int numsSize)
{
	for (int i = 0; i < numsSize - 1; i++)
	{
		int flag = 0;
		for (int j = 1; j < numsSize - i; j++)
		{
			if (nums[j - 1] > nums[j])
			{
				Swap(&nums[j - 1], &nums[j]);
				flag = 1;
			}
		}
		if (flag == 0)
			break;
	}
}

// 选择排序(一趟选出两个值：最大和最小)
void SelectSort(int *nums, int numsSize)
{
    int left = 0;
    int right = numsSize - 1;
    while(left < right)
    {
        int maxi = left;
        int mini = left;
        for(int i = left+1; i < right+1; i++)
        {
            if(nums[i] > nums[maxi])
            {
                maxi = i;
            }
            if (nums[i] < nums[mini])
			{
				mini = i;
			}
        }
        Swap(&nums[maxi], &nums[right]);
        if(right == mini)
        {// 防止right 是 mini的位置
            mini = maxi;
        }
        Swap(&nums[mini], &nums[left]);
        ++left;
        --right;
    }
}
// 希尔排序
void ShellSort(int *nums, int numsSize)
{
    int gap = numsSize;
    while(gap > 1)
    {
        gap = gap / 3 + 1;
        for(int i = 0; i < numsSize - gap; i++)
        {
            int end = i;
            int tmp = nums[end + gap];
            while(end >= 0)
            {
                if(nums[end] > tmp)
                {
                    nums[end + gap] = nums[end];
                    end -= gap;
                }
                else
                {
                    break;
                }
            }
            nums[end + gap] = tmp;
        }
    }
}
typedef int HPDataType;

typedef struct Heap
{
	HPDataType* data;
	size_t size;
	size_t capacity;
}Heap;

void AdjustDown(HPDataType* data, size_t size, size_t root)
{
	assert(data);
	size_t parent = root;
	size_t child = parent * 2 + 1;
	while (child < size)
	{
		if (child + 1 < size && data[child] < data[child + 1])
		{
			++child;
		}

		if (data[parent] < data[child])
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

void HeapSort(int *nums, int numsSize)
{
    // 从最后一个非叶子节点向下建堆
	int j = (numsSize - 1 - 1) / 2;     
	for (j; j >= 0; j--)
	{
		AdjustDown(nums, numsSize, j);
	}

	int end = numsSize - 1;
	while (end > 0)
	{
		Swap(&nums[0], &nums[end]);
		AdjustDown(nums, end, 0);
		--end;
	}

}


// hoare 快排系列
int hoarePartSort(int *nums, int left, int right)
{
    int keyi = left;
    while(left < right)
    {
        while( (left < right) && (nums[right] >= nums[keyi]) )
        {
            --right;
        }
        while( (left < right) && (nums[left] <= nums[keyi]) )
        {
            ++left;
        }
        Swap(&nums[left], &nums[right]);
    }
    Swap(&nums[keyi], &nums[right]);

    return left;
}
void hoareQuickSort(int *nums, int begin, int end)
{
    if(begin >= end)
        return;

    int keyi = hoarePartSort(nums, begin, end);
    hoareQuickSort(nums, begin, keyi - 1);
    hoareQuickSort(nums, keyi + 1, end);
}

int getMidIndex(int* a, int left, int right)
{
	int mid = left + (right - left) / 2;
	if (a[left] < a[mid])
	{
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
void MidhoareQuickSort(int *nums, int begin, int end)
{
    if(begin >= end)
        return;

    int mid = getMidIndex(nums, begin, end);
    Swap(&nums[begin], &nums[mid]);

    int keyi = hoarePartSort(nums, begin, end);
    MidhoareQuickSort(nums, begin, keyi - 1);
    MidhoareQuickSort(nums, keyi + 1, end);
}
void MinhoareQuickSort(int* nums, int begin, int end)
{
	if (begin >= end)
		return;
	if (begin - end >= 30)
	{	//当 需要排序的数据小于 30 就用插入排序
		InsertSort(nums, begin - end);
	}
	else
	{
		int keyi = hoarePartSort(nums, begin, end);	
		MinhoareQuickSort(nums, begin, keyi - 1);
		MinhoareQuickSort(nums, keyi + 1, end);
	}
}


// 挖坑法快排系列
int pitPartSort(int *nums, int left, int right)
{
    int key = nums[left];
    int piti = left;
    while(left < right)
    {
        while( (left < right) && nums[right] >= key)
        {
            --right;
        }
        nums[piti] = nums[right];
        piti = right;
        while( (left < right) && nums[left] <= key)
        {
            ++left;
        }
        nums[piti] = nums[left];
        piti = left;
    }
    nums[piti] = key;

    return piti;
}
void PitQuickSort(int *nums, int begin, int end)
{
    if(begin >= end)
        return;

    int keyi = pitPartSort(nums, begin, end);
    PitQuickSort(nums, begin, keyi - 1);
    PitQuickSort(nums, keyi + 1, end);
}
void MidPitQuickSort(int *nums, int begin, int end)
{
    if(begin >= end)
        return;

    int mid = getMidIndex(nums, begin, end);
    Swap(&nums[begin], &nums[mid]);

    int keyi = pitPartSort(nums, begin, end);
    MidPitQuickSort(nums, begin, keyi - 1);
    MidPitQuickSort(nums, keyi + 1, end);
}
void MinPitQuickSort(int* nums, int begin, int end)
{
	if (begin >= end)
		return;
	if (begin - end >= 30)
	{
		InsertSort(nums, begin - end);
	}
	else
	{
		int keyi = pitPartSort(nums, begin, end);	
		MinPitQuickSort(nums, begin, keyi - 1);
		MinPitQuickSort(nums, keyi + 1, end);
	}
}


// 前后指针快排系列
int PrevcurPartSort(int *nums, int left, int right)
{
    int prev = left;
    int cur = left + 1;
    int keyi = left;
    while(cur <= right)
    {
        if(nums[cur] < nums[keyi] && (nums[++prev] != nums[cur]))
            Swap(&nums[prev], &nums[cur]);

        ++cur;
    }
    Swap(&nums[prev], &nums[keyi]);

    return prev;
}
void PrevcurQuickSort(int *nums, int begin, int end)
{
    if(begin >= end)
        return;

    int keyi = PrevcurPartSort(nums, begin, end);
    PrevcurQuickSort(nums, begin, keyi - 1);
    PrevcurQuickSort(nums, keyi + 1, end);
}
void MidPrevcurQuickSort(int *nums, int begin, int end)
{
    if(begin >= end)
        return;

    int mid = getMidIndex(nums, begin, end);
    Swap(&nums[begin], &nums[mid]);

    int keyi = PrevcurPartSort(nums, begin, end);
    MidPrevcurQuickSort(nums, begin, keyi - 1);
    MidPrevcurQuickSort(nums, keyi + 1, end);
}
void MinPrevcurQuickSort(int* nums, int begin, int end)
{
	if (begin >= end)
		return;
	if (begin - end >= 30)
	{
		InsertSort(nums, begin - end);
	}
	else
	{
		int keyi = PrevcurPartSort(nums, begin, end);	
		MinPrevcurQuickSort(nums, begin, keyi - 1);
		MinPrevcurQuickSort(nums, keyi + 1, end);
	}
}

// 快排非递归
void QuickSort(int* nums, int begin, int end)
{
    Stack QsSt;
    StackInit(&QsSt);
    StackPush(&QsSt, begin);
    StackPush(&QsSt, end);

    while(!StackEmpty(&QsSt))
    {
        int right = StackTop(&QsSt);
        StackPop(&QsSt);
        int left = StackTop(&QsSt);
        StackPop(&QsSt);

        int keyi = PrevcurPartSort(nums, left, right);
        if(keyi - left > 1)
        {
            StackPush(&QsSt, left);
            StackPush(&QsSt, keyi - 1);
        }
        if(right - keyi > 1)
        {
            StackPush(&QsSt, keyi + 1);
            StackPush(&QsSt, right);
        }
    }
}

// 归并排序
void _margeSort(int* a, int begin, int end, int* tmp)
{
	if (begin >= end)
		return;

	int mid = (begin + end) / 2;
	_margeSort(a, begin, mid, tmp);
	_margeSort(a, mid + 1, end, tmp);

	int begin1 = begin, end1 = mid;
	int begin2 = mid + 1, end2 = end;
	int index = begin;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (a[begin1] < a[begin2])
		{
			tmp[index++] = a[begin1++];
		}
		else
		{
			tmp[index++] = a[begin2++];
		}
	}

	while (begin1 <= end1)
	{
		tmp[index++] = a[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[index++] = a[begin2++];
	}

	memcpy(a + begin, tmp + begin, sizeof(int)* (end - begin + 1));
}

void margeSort(int* a, int size)
{
	int* tmp = (int*)malloc(sizeof(int)* size);
	if (tmp == NULL)
	{
		printf("margeSort fail\n");
		exit(-1);
	}

	_margeSort(a, 0, size - 1, tmp);

	free(tmp);
}

void CountSort(int *nums, int numsSize)
{
    int max = nums[0];
    int min = nums[0];
    for(int i = 0; i < numsSize; i++)
    {
        if(nums[i] > max)
        {
            max = nums[i];
        }
        if (nums[i] < min)
		{
			min = nums[i];
		}
    }

    int *arr = (int*)malloc(sizeof(int) * (max - min + 1));
    assert(arr);
    memset(arr, 0, sizeof(int)*(max - min + 1));

    for(int i = 0; i < numsSize; i++)
    {
        arr[nums[i] - min]++;
    }

    int j = 0;
    for(int i = 0; i < (max - min + 1); i++)
    {
        while (arr[i]--)
		{
			nums[j++] = i + min;
		}
    }
}
int* sortArray(int *nums, int numsSize, int *returnSize)
{
    // 插入排序
    //InsertSort(nums, numsSize);     // 超时

    // 冒泡排序
    //BubbleSort(nums, numsSize);     // 超时

    // 选择排序
    //SelectSort(nums, numsSize);     // 超时

    // 希尔排序
    //ShellSort(nums, numsSize);      // 可行

    // 堆排序
    //HeapSort(nums, numsSize);       // 可行

    // hareo快排 无优化
    //hoareQuickSort(nums, 0, numsSize - 1);  // 超时
    // 三数取中优化版
    //MidhoareQuickSort(nums, 0, numsSize - 1); // 可行
    // 小区间优化版
    //MinhoareQuickSort(nums, 0, numsSize - 1); // 超时

    // 挖坑快排 无优化
    //PitQuickSort(nums, 0, numsSize - 1);    // 超时
    // 三数取中优化版
    //MidPitQuickSort(nums, 0, numsSize - 1);   // 可行
    // 小区间优化版
    //MinPitQuickSort(nums, 0, numsSize - 1); // 超时

    // 双指针快排 无优化
    //PrevcurQuickSort(nums, 0, numsSize - 1);    // 超时
    // 三数取中优化版
    //MidPrevcurQuickSort(nums, 0, numsSize - 1);   // 可行
    // 小区间优化版
    //MinPrevcurQuickSort(nums, 0, numsSize - 1); // 超时

    // 快排 前后指针非递归版
    //QuickSort(nums, 0, numsSize - 1);   // 超时
    
    // 归并排序 
    //margeSort(nums, numsSize);  // 可行

    // 计数排序
    CountSort(nums, numsSize);      // 可行

    *returnSize = numsSize;
    return nums;
}