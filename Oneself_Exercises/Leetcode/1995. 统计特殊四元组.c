//给你一个下标从 0 开始的整数数组 nums ，返回满足下述条件的不同四元组 (a, b, c, d) 的数目：
//nums[a] + nums[b] + nums[c] == nums[d] ，且
//a < b < c < d

//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/count-special-quadruplets

int countQuadruplets(int* nums, int numsSize)
{//枚举遍历统计
    int count = 0;
    for(int i = 0; i <= numsSize - 4; i++)
    {
        for(int j = i + 1; j < numsSize; j++)
        {
            for(int k = j + 1; k < numsSize; k++)
            {
                for(int l = k + 1; l < numsSize; l++)
                {
                    if(*(nums + i) + *(nums + j) + *(nums + k) == *(nums + l))
                        count++;
                }
            }
        }
    }

    return count;
}