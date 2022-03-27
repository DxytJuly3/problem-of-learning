#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

void twoSum(int* nums, int numsSize, int target)
{
    for (int i = 0; i < numsSize - 1; i++)
    {
        if (*(nums + i) > target)
            *(nums + i) = 0;
    }
    for (int i = 0; i < numsSize - 1; i++)
    {
        for (int j = i; j < numsSize; j++)
        {
            if (*(nums + i) + *(nums + j) == target)
                printf("[%d,%d]\n", i, j);
        }
    }
}

int main()
{
    int nums[20] = { 1,22,3,17,5,13,11,23 };
    int numsSize = 8;
    int target = 14;
    twoSum(nums, numsSize, target);

    return 0;
}


