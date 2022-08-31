/*
给定两个数组 nums1 和 nums2 ，返回 它们的交集 。输出结果中的每个元素一定是 唯一 的。我们可以 不考虑输出结果的顺序

示例 1：
输入：nums1 = [1,2,2,1], nums2 = [2,2]
输出：[2]

示例 2：
输入：nums1 = [4,9,5], nums2 = [9,4,9,8,4]
输出：[9,4]
解释：[4,9] 也是可通过的

提示：
    1 <= nums1.length, nums2.length <= 1000
    0 <= nums1[i], nums2[i] <= 1000

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/intersection-of-two-arrays
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
本题中提到的交集 并不是数学中提到的两个集合相同顺序的交集
                而只是 两个数组中都存在的元素，且统计不重复，即元素唯一
解题思路：
    1. 首先 用两个 set 去重存放 nums1 和 nums2 的元素，然后再找两个set中都有的元素
*/
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        vector<int> retArr;
        if(nums1.empty() || nums2.empty())
            return retArr;
        
        set<int> setNums1;
        for(auto e : nums1) {
            setNums1.insert(e);
        }
        set<int> setNums2;
        for(auto e : nums2) {
            setNums2.insert(e);
        }

        set<int>::iterator vIt1 = setNums1.begin();
        set<int>::iterator vIt2 = setNums2.begin();
        while(vIt1 != setNums1.end() && vIt2 != setNums2.end()) {
            if(*vIt1 == *vIt2) {
                retArr.push_back(*vIt1);
                vIt1++;
                vIt2++;
            }
            else if(*vIt2 > *vIt1)
                vIt1++;
            else
                vIt2++;
        }

        return retArr;
    }
};