/*
给你两个整数数组 nums1 和 nums2 ，请你以数组形式返回两数组的交集。
返回结果中每个元素出现的次数，应与元素在两个数组中都出现的次数一致（如果出现次数不一致，则考虑取较小值）。可以不考虑输出结果的顺序。
示例 1：
输入：nums1 = [1,2,2,1], nums2 = [2,2]
输出：[2,2]

示例 2:
输入：nums1 = [4,9,5], nums2 = [9,4,9,8,4]
输出：[4,9]

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/intersection-of-two-arrays-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
题意分析：
    题目要求 去两个数组中相同的元素, 
    且如果 同一个元素有多次重复(例如:1 2 3 4 4 4 4 5 6  和 3 4 4 4 5 6 7 中 4 多次重复), 记录重复次数少的
    
思路分析：
    将 两个数组的元素 用 哈希map 记录并统计
    再遍历其中一个map, 并在 另一个map中查找是否存在, 如果存在 则循环插入此元素, 循环次数是 map统计次数少的那个
*/
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> nums1Map;
        unordered_map<int, int> nums2Map;
        for(auto e : nums1) {
            nums1Map[e]++;
        }
        for(auto e : nums2) {
            nums2Map[e]++;
        }

        vector<int> ret;
        for(auto kv : nums1Map) {
            auto mIt = nums2Map.find(kv.first);
            if(mIt != nums2Map.end()) {
                if(mIt->second > kv.second) {
                    for(int i = 0; i < kv.second; i++) 
                        ret.push_back(mIt->first);
                }
                else {
                    for(int i = 0; i < mIt->second; i++) 
                        ret.push_back(mIt->first);
                }
            }
        }

        return ret;
    }
};