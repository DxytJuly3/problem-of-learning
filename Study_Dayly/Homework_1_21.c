#define _CRT_SECURE_NO_WARNINGS 1

//#include<stdio.h>
//int  main()
//{
//    int a[12] = { 1,2,3,4,5,6,7,8,9,10,11,12 }, * p[4], i;
//    for (i = 0; i < 4; i++)
//        p[i] = &a[i * 3];
//    printf("%d\n", p[3][2]);
//    return 0;
//}

#include <stdio.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* productExceptSelf(int* nums, int numsSize/*, int* returnSize*/)
{
    /*
     先从左往右，把 i 左边的乘积，放入目标数组
     然后再从右往左，把 i 右边的乘积，乘入目标数组的对应位置
     然后返回目标数组
     */
    int* output = (int*)malloc(sizeof(int) * numsSize);
    //*returnSize = numsSize;
    int product_right = 1;
    int product_left = 1;
    for (int i = 0; i < numsSize; i++)
    {
        output[i] = product_left;
        product_left *= nums[i];
    }
    for (int i = numsSize - 1; i >= 0; i--)
    {
        output[i] *= product_right;
        product_right *= nums[i];
    }

    return output;
}

void print(int* new, int sz)
{
	for (int i = 0; i < sz; i++)
	{
		printf("%d ", *(new + i));
	}
}

int main()
{
	int arr[20] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };
	int* new = productExceptSelf(arr, 20);
	print(new, 20);

	return 0;
}