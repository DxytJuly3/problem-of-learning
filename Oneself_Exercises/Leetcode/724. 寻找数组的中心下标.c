//给你一个整数数组 nums ，请计算数组的 中心下标 。
//数组 中心下标 是数组的一个下标，其左侧所有元素相加的和等于右侧所有元素相加的和。
//如果中心下标位于数组最左端，那么左侧数之和视为 0 ，因为在下标的左侧不存在元素。这一点对于中心下标位于数组最右端同样适用。
//如果数组有多个中心下标，应该返回 最靠近左边 的那一个。如果数组不存在中心下标，返回 -1 。

//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/find-pivot-index
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

int pivotIndex(int* nums, int numsSize)
{
    for(int i = 0; i < numsSize; i++)
    {//从中心点为 0 开始，计算左右两边和
        int sum_left = 0;
        int sum_right = 0;
        for(int j = 0; j < numsSize; j++)
        {//i 每递增一次  左边多一个元素，右边少一个元素
            if (j < i)//小于i  的都是左元素
                sum_left += *(nums + j); 
            else if (j > i)//大于i  的都是右元素
                sum_right += *(nums + j);
        }
        if(sum_right == sum_left)
         return i;
    }
    
    return -1;
}