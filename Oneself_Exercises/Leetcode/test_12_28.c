#include <stdio.h>
//力扣第一题 但是暂时看不懂指定的格式
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


