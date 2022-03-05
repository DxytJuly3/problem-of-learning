//数组nums包含从0到n的所有整数，但其中缺了一个。
//请编写代码找出那个缺失的整数。你有办法在O(n)时间内完成吗？
//注意：本题相对书上原题稍作改动

//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/missing-number-lcci
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

/*int missingNumber(int* nums, int numsSize)
{
    int* newnums = (int*)malloc(sizeof(int) * (numsSize + 1));
    for(int i = 0; i < numsSize + 1; i++)
    {
        newnums[i] = -1;
    }
    for(int i = 0; i < numsSize; i++)
    {
        int tmp = nums[i];
        newnums[tmp] = tmp;
    }
    for(int i = 0; i < numsSize + 1; i++)
    {
        if(newnums[i] == -1)
            return i;
    }

    free(newnums);
    return -1;
}*/
int missingNumber(int* nums, int numsSize)
{
    int flag = 0;
    for(int i = 0; i < numsSize + 1; i++)
        flag ^= i;
    for(int i = 0; i < numsSize; i++)
        flag ^= nums[i];
        
    return flag;
}