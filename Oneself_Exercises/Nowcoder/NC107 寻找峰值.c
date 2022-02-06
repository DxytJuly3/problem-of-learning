//给定一个长度为n的数组nums，请你找到峰值并返回其索引。数组可能包含多个峰值，在这种情况下，返回任何一个所在位置即可。
//1.峰值元素是指其值严格大于左右相邻值的元素。严格大于即不能有等于
//2.假设 nums[-1] = nums[n] = -\infty−∞
//3.对于所有有效的 i 都有 nums[i] != nums[i + 1]
//4.你可以使用O(logN)的时间复杂度实现此问题吗？

/**
 * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
 *
 * 
 * @param nums int整型一维数组 
 * @param numsLen int nums数组长度
 * @return int整型
 *
 * C语言声明定义全局变量请加上static，防止重复定义
 */
int findPeakElement(int* nums, int numsLen )
{
    for(int i = 0; i < numsLen; i++)
    {
        if(nums[0] > nums[1])
            return 0;
        else if(nums[numsLen - 1] > nums[numsLen - 2])
            return numsLen - 1;
        else
        {
            if(nums[i] > nums[i - 1] && nums[i] > nums[i + 1])
                return i;
        }
    }
    
    return 0;
}