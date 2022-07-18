/*
给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。
请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。

示例 1:
输入: [3,2,1,5,6,4], k = 2
输出: 5

示例 2:
输入: [3,2,3,1,2,4,5,5,6], k = 4
输出: 4

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/kth-largest-element-in-an-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
具体思路：
求 数组中第K个最大元素，类似一个Top-K问题
遍历数组，除前k个元素直接入堆之外，之后的元素中 比 root大的元素的入堆，入堆前删除root
以此建立一个 只有 K个元素的小根堆，
完成之后 堆的根即为所求元素

或者 遍历数组建大堆，然后pop K次堆，此时的 root 即为第K大的元素
*/

class Solution
{
public:
    int findKthLargest(vector<int>& nums, int k)
    {
        priority_queue<int, vector<int>, greater<int>> prQue_K;
        for(int i = -0; i < k; i++)
        {
            prQue_K.push(nums[i]);
        }

        for(int i = k; i < nums.size(); i++)
        {
            if(nums[i] > prQue_K.top())
            {
                prQue_K.pop();
                prQue_K.push(nums[i]);
            }
        }

        return prQue_K.top();
    }
    /*int findKthLargest(vector<int>& nums, int k)
    {
        priority_queue<int> prQue_K(nums.begin(), nums.end());
        for(int i = 0; i < k-1; i++)
        {
            prQue_K.pop();
        }
        
        return prQue_K.top();
    }*/
};