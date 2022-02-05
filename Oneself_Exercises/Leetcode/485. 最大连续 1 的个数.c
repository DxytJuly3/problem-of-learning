//给定一个二进制数组 nums ， 计算其中最大连续 1 的个数。

//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/max-consecutive-ones
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

int findMaxConsecutiveOnes(int* nums, int numsSize)
{
    int count1 = 0;
    int count_max = 0;
    for(int i = 0; i < numsSize; i++)
    {
        if(nums[i])
        {
            count1++;
        }
        else
        {
            if(count1 > count_max)
            {
                count_max = count1;
            }
            count1 = 0;
        }
    }
    if(count1 > count_max)
    {
       count_max = count1;
    }

    return count_max;
}