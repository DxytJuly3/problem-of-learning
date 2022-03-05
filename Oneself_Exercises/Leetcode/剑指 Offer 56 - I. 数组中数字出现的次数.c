//一个整型数组 nums 里除两个数字之外，其他数字都出现了两次。
//请写程序找出这两个只出现一次的数字。
//要求时间复杂度是O(n)，空间复杂度是O(1)。

//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-lcof
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* singleNumbers(int* nums, int numsSize, int* returnSize)
{
    int flag = 0;
    int count = 1;
    *returnSize = 2;
    int* returnNums = (int*)malloc(sizeof(int) * *returnSize);
    int* Nums1 = (int*)malloc(sizeof(int) * numsSize);
    for(int i = 0; i < numsSize; i++)
        flag ^= nums[i];

    while((flag & count) != count)
        count <<= 1;

    int x = 0;
    int y = 0;
    int flag2 = flag;
    int count2 = 0;
    for(int i = 0; i < numsSize; i++)
    {
        if((nums[i] & count) == count)
        {
            Nums1[count2] = nums[i];
            count2++;
        }
    }
    for(int i = 0; i < count2; i++)
    {
        flag2 ^= Nums1[i];
    }
    x = flag2;
    y = flag ^ x;
    
    returnNums[0] = x;
    returnNums[1] = y;

    free(Nums1);
    return returnNums;
}