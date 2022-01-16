//给你一个整数数组 nums ，其中总是存在 唯一的 一个最大整数 。
//请你找出数组中的最大元素并检查它是否 至少是数组中每个其他数字的两倍 。如果是，则返回 最大元素的下标 ，否则返回 -1 。

//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/largest-number-at-least-twice-of-others
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

int dominantIndex(int* nums, int numsSize) {
    if (numsSize == 1)
        return 0;
    int max = *nums;
    int max_2 = 0;
    int returnSign = 0;
    for (int i = 0; i < numsSize; i++)
    {
        if (*(nums + i) > max)
        {
            returnSign = i;
            max = *(nums + i);
        }
    }
    for (int i = 0; i < numsSize; i++)
    {
        if (*(nums + i) > max_2 && *(nums + i) < max)
            max_2 = *(nums + i);
    }
    if (max - 2 * max_2 >= 0)
        return returnSign;
    else
        return -1;
}