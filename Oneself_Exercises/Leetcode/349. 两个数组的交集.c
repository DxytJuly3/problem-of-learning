//给定两个数组，编写一个函数来计算它们的交集。

//链接：https://leetcode-cn.com/problems/intersection-of-two-arrays/
//来源：力扣（LeetCode）
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */  
int cmp(const void *a, const void *b)
 {
    return (*(int*)a - *(int*)b);
}
int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize)
{
    if (!nums1 || !nums2) 
    {
        *returnSize = 0;
        return NULL;
    }
    /* 快排对两个数组升序排序 */
    qsort(nums1, nums1Size, sizeof(nums1[0]), cmp);
    qsort(nums2, nums2Size, sizeof(nums2[0]), cmp);

    int* returnNum = (int *)malloc(sizeof(int) * (nums1Size + nums2Size));

    int tmp = 0;// 记录 重复数字的个数
    for (int i = 0, j = 0; i < nums1Size && j < nums2Size; )
    {
        if (*(nums1 + i) < *(nums2 + j))       //两数组元素一对一对比，哪个小 哪个位置递增
            i++;
        else if (*(nums1 + i) > *(nums2 + j))
            j++;
        else                                   //两数组元素相等就存入需要返回的数组中
        {
            *(returnNum + tmp) = *(nums1 + i);
            tmp++;
            i++;
            j++;
            //存入两个以上的时候，判断是否有重复存入第2个 就判断 returnNum[0] 和 returnNum[1]，即tmp - 1 和 tmp - 2  
            if (tmp > 1 && *(returnNum+ tmp - 1) == *(returnNum+ tmp - 2))
                tmp--;
        }
    }

    *returnSize = tmp;
    return returnNum;
}