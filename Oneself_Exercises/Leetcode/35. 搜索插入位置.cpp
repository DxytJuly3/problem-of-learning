/*
给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。
如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
请必须使用时间复杂度为 O(log n) 的算法。

示例 1:
输入: nums = [1,3,5,6], target = 5
输出: 2

示例 2:
输入: nums = [1,3,5,6], target = 2
输出: 1

示例 3:
输入: nums = [1,3,5,6], target = 7
输出: 4

提示:
    1 <= nums.length <= 104
    -104 <= nums[i] <= 104
    nums 为 无重复元素 的 升序 排列数组
    -104 <= target <= 104

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/search-insert-position
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
/*
思路分析：
    本题限制时间复杂度为 O(log N)
    就表示不能顺序遍历数组, 直接将算法锁定到了二分查找
    所以本题就是在原数组上二分查找数值, 并返回位置

    建议示例画图分析
*/

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int numsBegin = 0;
        int numsEnd = nums.size();
        while(numsBegin < numsEnd) {
            if(target < nums[(numsBegin + numsEnd)/2]) {
                numsEnd = (numsBegin + numsEnd)/2;
            }
            else if(target > nums[(numsBegin + numsEnd)/2]) {
                numsBegin = (numsBegin + numsEnd)/2 + 1;
            }
            else
                return (numsBegin + numsEnd)/2;
        }

        return numsBegin;
    }
};