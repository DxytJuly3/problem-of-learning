/*
给你一个整数数组 nums ，该数组具有以下属性：
    nums.length == 2 * n.
    nums 包含 n + 1 个 不同的 元素
    nums 中恰有一个元素重复 n 次
找出并返回重复了 n 次的那个元素。

示例 1：
输入：nums = [1,2,3,3]
输出：3

示例 2：
输入：nums = [2,1,2,5,3,2]
输出：2

示例 3：
输入：nums = [5,1,5,2,5,3,5,4]
输出：5

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/n-repeated-element-in-size-2n-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
题意分析：
    给定一个存放有 2*n 个元素的数组
    且 存在 同一个元素重复了 n 次，且 其他元素均不相同

思路分析：
    思路1：因为 除了唯一重复的元素，其他元素都不相同，并且需要找到重复的元素
        所以 使用哈希表非常的适合这个题，可以看作没有重复的元素，因为只要遇到重复的直接返回就可以了
        并且 需要不断地对比，所以非常适合哈希
        遍历数组，并将遍历过的元素存入 哈希表中，并在遍历过程中 查找元素是否在哈希表中出现过，如果出现过直接返回此元素
    
    思路2：长度为 2*n 的数组中 存在一个元素重复了n次，且其他元素均不相同
        那么 重复n次的元素 如果不是 每间隔一个元素出现一次，那么 一定存在相邻的情况
        但是 还有一种情况除外，n = 2 时，可以不相邻 也可以不只间隔一个元素
        因为 存在这种情况 2 1 3 2 
        不过 n > 2就一定 不是每间隔一个元素出现一次，就是存在相邻的情况
        所以 可以一共遍历四次数组，两次分别从 0 和 1 开始间隔1个对比
        一次 相邻对比，一次间隔2个对比

*/

class Solution {
public:
    // 思路1：
    int repeatedNTimes(vector<int>& nums) {
        unordered_set<int> findSet;
        for(auto e : nums) {
            if(findSet.count(e))
                return e;
            findSet.insert(e);
        }

        return -1;
    }
    // 思路2：
    /*int repeatedNTimes(vector<int>& nums) {
        for(int i = 0; i + 2< nums.size(); i+=2) {
            if(nums[i] == nums[i + 2])
                return nums[i];
        }
        for(int i = 1; i + 2< nums.size(); i+=2) {
            if(nums[i] == nums[i + 2])
                return nums[i];
        }
        for(int i = 0; i + 1< nums.size(); i++) {
            if(nums[i] == nums[i + 1])
                return nums[i];
        }
        for(int i = 0; i + 3< nums.size(); i+=3) {
            if(nums[i] == nums[i + 3])
                return nums[i];
        }

        return -1;
    }*/

};