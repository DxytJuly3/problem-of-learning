/*
整数数组 nums 按升序排列，数组中的值 互不相同 。
在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 旋转，
使数组变为 [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]（下标 从 0 开始 计数）。
例如， [0,1,2,4,5,6,7] 在下标 3 处经旋转后可能变为 [4,5,6,7,0,1,2] 。
给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target ，则返回它的下标，否则返回 -1 。
你必须设计一个时间复杂度为 O(log n) 的算法解决此问题。

示例 1：
输入：nums = [4,5,6,7,0,1,2], target = 0
输出：4

示例 2：
输入：nums = [4,5,6,7,0,1,2], target = 3
输出：-1

示例 3：
输入：nums = [1], target = 0
输出：-1

提示：
    1 <= nums.length <= 5000
    -104 <= nums[i] <= 104
    nums 中的每个值都 独一无二
    题目数据保证 nums 在预先未知的某个下标上进行了旋转
    -104 <= target <= 104

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/search-in-rotated-sorted-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
/*
思路分析：
    题目要求时间复杂度为 O(log N), 说明要求用二分查找的方式
    二分查找的前提是有序, 而数组旋转之后 会出现两段有序序列, 不过如果将数组从中间分开 很有可能是一段有序 另一段无序的
    所以 旋转数组从mid向左右分开 一定存在 左有序 或 右有序
    然后就可以在左或右进行二分查找
    如果 target在无序的边, 依旧可以将其看作旋转数组 从mid向左右分开 一定存在左有序或右有序
    规则还是一样的
    以下为例：
    位：0 1 2 3 4  5  6  7  8  9  10 11 12 13 14
    数：6 7 8 9 10 11 12 13 14 15 1  2  3  4  5

    找 2
    [)划分区间

    从 mid((0 + 15)/2 == 7) 分开
    target != nums[mid]
    [0, 7): 6 7 8 9 10 11 12
    [7, 15): 13 14 15 1  2  3  4  5
    左有序, 则在[0, 7) 判断 target, 发现target 不在此区间内, 则更新 right 为 mid, 以保证下次mid在另一个区间内
    right 变为 7 
    则从 mid((7 + 15)/2 == 11) 分开
    target == nums[mid]
    直接返回 mid

    其实本题的思想, 是 从mid分开的两个区间中 有一个区间一定是的有序的 然后在有序的区间找
    每找到就去另一个区间找, 而另一个无序的区间又可以看作一个旋转数组
    所以 就可以重复
*/
class Solution {
public:
    int search(vector<int>& nums, int target) {
        if(nums.size() == 0)
            return -1;
        if(nums.size() == 1)
            return nums[0] == target ? 0 : -1;
        
        size_t left = 0;
        size_t right = nums.size();
        while(left < right) {
            size_t mid = (left + right) / 2;
            if(nums[mid] == target)
                return mid;
            if(nums[mid] > nums[0]) {
                // 左有序
                if(target < nums[mid] && target >= nums[0])
                    right = mid;
                else
                    left = mid + 1;
            }
            else{
                // 右有序
                if(target > nums[mid] && target <= nums[nums.size() - 1])
                    left = mid + 1;
                else
                    right = mid;
            }
        }

        return -1;
    }
};