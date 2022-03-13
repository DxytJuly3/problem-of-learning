/*
给你两个按 非递减顺序 排列的整数数组 nums1 和 nums2，另有两个整数 m 和 n ，分别表示 nums1 和 nums2 中的元素数目。
请你 合并 nums2 到 nums1 中，使合并后的数组同样按 非递减顺序 排列。
注意：最终，合并后数组不应由函数返回，而是存储在数组 nums1 中。为了应对这种情况，nums1 的初始长度为 m + n，其中前 m 个元素表示应合并的元素，后 n 个元素为 0 ，应忽略。nums2 的长度为 n 。
示例 1：
输入：nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
输出：[1,2,2,3,5,6]
解释：需要合并 [1,2,3] 和 [2,5,6] 。
合并结果是 [1,2,2,3,5,6] ，其中斜体加粗标注的为 nums1 中的元素。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/merge-sorted-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

//取巧
//直接将 nums2 的数据 赋予 nums1 后面，然后排序
/*int cmp_int(const void *elem1, const void *elem2 )
{
    return *(int*)elem1 - *(int*)elem2;
}

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n)
{
    for(int i = m, j = 0; i < n+m; i++, j++)
    {
        nums1[i] = nums2[j];
    }

    qsort(nums1, n+m, sizeof(int), cmp_int);
}*/

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n)
{
    int end1 = m - 1;
    int end2 = n - 1;
    int end_end =  m + n - 1;

    while(end1 >= 0 && end2 >=0)
    {
        if(nums1[end1] >= nums2[end2])
        {
            nums1[end_end] = nums1[end1];
            end_end--;
            end1--;
        }
        else
        {
            nums1[end_end] = nums2[end2];
            end_end--;
            end2--;
        }
    }

    while(end1 >= 0)
    {
        nums1[end_end] = nums1[end1];
        end_end--;
        end1--;
    }
    while(end2 >= 0)
    {
        nums1[end_end] = nums2[end2];
        end_end--;
        end2--;
    }
}