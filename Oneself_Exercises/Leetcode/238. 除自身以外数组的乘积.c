//给你一个长度为 n 的整数数组 nums，其中 n > 1，返回输出数组 output ，其中 output[i] 等于 nums 中除 nums[i] 之外其余各元素的乘积。

//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/product-of-array-except-self
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* productExceptSelf(int* nums, int numsSize, int* returnSize)
{
    /*
     先从左往右，把 i 左边的乘积，放入目标数组
     然后再从右往左，把 i 右边的乘积，乘入目标数组的对应位置
     然后返回目标数组
     */
    int* output = (int *)malloc(sizeof(int) * numsSize);
    *returnSize = numsSize;
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