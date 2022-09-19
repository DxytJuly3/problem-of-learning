/*
给你两个数组，arr1 和 arr2，arr2 中的元素各不相同，arr2 中的每个元素都出现在 arr1 中。
对 arr1 中的元素进行排序，使 arr1 中项的相对顺序和 arr2 中的相对顺序相同。未在 arr2 中出现过的元素需要按照升序放在 arr1 的末尾。

示例 1：
输入：arr1 = [2,3,1,3,2,4,6,7,9,2,19], arr2 = [2,1,4,3,9,6]
输出：[2,2,2,1,4,3,3,9,6,7,19]

示例  2:
输入：arr1 = [28,6,22,8,44,17], arr2 = [22,28,8,6]
输出：[22,28,8,6,17,44]

提示：
    1 <= arr1.length, arr2.length <= 1000
    0 <= arr1[i], arr2[i] <= 1000
    arr2 中的元素 arr2[i]  各不相同 
    arr2 中的每个元素 arr2[i] 都出现在 arr1 中

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/relative-sort-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
/*
思路分析：
    将 arr1 的所有元素用哈希表统计
    然后遍历arr2 按照arr2中数据的顺序将 哈希表中arr2也存在的数据 存放到需要返回的vector<int> 中
    同时将 已经存放过的元素计数, 在哈希表中改为 -1
    然后遍历哈希表将 其他元素 存放到数组中
    再将 后来存放的部分进行排序
*/

class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        vector<int> retV;
        unordered_map<int, int> arr1Map;
        for(auto n : arr1) {
            arr1Map[n]++;
        }
        for(int i = 0; i < arr2.size(); i++) {
            for(int j = 0; j < arr1Map[arr2[i]]; j++)
                retV.push_back(arr2[i]);
            arr1Map[arr2[i]] = -1;
        }
        int Size = retV.size();
        for(auto &e : arr1Map) {
            if(e.second != -1) {
                for(int i = 0; i < e.second; i++) 
                    retV.push_back(e.first);
                e.second = -1;
            }
        }

        sort(retV.begin()+Size, retV.end());

        return retV;
    }
};