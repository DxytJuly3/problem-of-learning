//集合 s 包含从 1 到 n 的整数。不幸的是，因为数据错误，导致集合里面某一个数字复制了成了集合里面的另外一个数字的值
//导致集合丢失了一个数字并且有一个数字重复 。
//给定一个数组 nums 代表了集合 S 发生错误后的结果。
//请你找出重复出现的整数，再找到丢失的整数，将它们以数组的形式返回。

//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/set-mismatch
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int returnNum[2] = { 0 }; 
void sort(int* nums, int numsSize)
{
    int i, j, t;
    for (i = 1; i < numsSize; i++)
    {
        t = nums[i];
        j = i - 1;
        while (j >= 0 && t < nums[j])
        {
            nums[j + 1] = nums[j];
            --j;
        }
        nums[j + 1] = t;
    }
}
int* findErrorNums(int* nums, int numsSize, int* returnSize)
{
    sort(nums, numsSize);
    int* first = nums;
    int count = 0;
    if (*nums == *(nums + 1))
        returnNum[0] = *nums;
    while (*nums != *(nums + 1))
    {
        nums++;
        if (*nums == *(nums + 1))
        {
            returnNum[0] = *nums;
            break;
        }
    }
    nums = first;
    while (count < numsSize - 1)
    {
        if (*(nums + 1) - *nums == 2)
        {
            returnNum[1] = *nums + 1;
            break;
        }
        nums++;
        count++;
    }
    nums = first;
    if (*nums != 1)
        returnNum[1] = 1;
    else if (*(nums + numsSize - 1) != numsSize)
        returnNum[1] = numsSize;
    if(returnNum[0] != 0 && returnNum[1] != 0)
        *returnSize = 2;

    return returnNum;
}
