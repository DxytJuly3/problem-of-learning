/*
链接：https://www.nowcoder.com/questionTerminal/5a304c109a544aef9b583dce23f5f5db
来源：牛客网

一个数组有 N 个元素，求连续子数组的最大和。 例如：[-1,2,1]，和最大的连续子数组为[2,1]，其和为 3
输入描述:
输入为两行。 第一行一个整数n(1 <= n <= 100000)，表示一共有n个元素 第二行为n个数，即每个元素,每个整数都在32位int范围内。以空格分隔。

输出描述:
所有连续子数组中和最大的值。

示例1
输入
3
-1 2 1

输出
3

*/
/*
思路分析：
    可以在遍历 数组的过程中 并对遍历过的元素求和, 并记录和为maxSum, 如果减小了就不记录
    遍历一遍之后 max 即为连续子序列的最大和
    具体的细节：
        首先 向 vector<int> numsV 中输入n个数
        后 定义三个变量: oldSum, sum, maxSum
            oldSum 记录上一次循环的sum, 初始化要为 numsV.begin()
            sum 记录 +当前元素时的和, 初始化要为 0, 保证不影响元素相加
            maxSum 记录 过程中最大的和, 初始化也要为 numsV.begin()
                原因是, 如果数组全为负数, 则maxSum 只能是负数
                若 maxSum 被初始化为 0, 则 maxSum 在整个遍历过程中不会更新
        然后 迭代器循环遍历数组
        进入循环之后, sum += *vIt 即 加迭代器表示的当前值
        相加之后 
        如果 sum > oldSum 就表示 sum与上一次相比变大了, 表示当前值为正数
                但是 即使sum变大了,也有可能没有当前值大, 即 sum之前为负数
                    那么 sum 就该更新为 当前值
                再将 当前sum 与 记录过的 maxSum 对比, 如果sum大, 就更新maxSum
        如果 sum < oldSum 就表示 sum与上一次相比变小了, 即表明当前值为 负数
                则 记录 oldSum = sum, 然后 把sum = 0
        
        迭代器向后走, 直到遍历结束
        最终的maxSum 即为所求
*/

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    vector<int> numsV;
    cin >> n;
    for(int i = 0; i < n; i++) {
        int num;
        cin >> num;
        numsV.push_back(num);
    }
    
    int oldSum = *numsV.begin();
    int sum = 0;
    int maxSum = *numsV.begin();
    auto vIt = numsV.begin();
    while(vIt != numsV.end()) {
        sum += *vIt;
        if(sum > oldSum) {
            if(*vIt >= sum)
                sum = *vIt;
            if(sum > maxSum)
                maxSum = sum;
        }
        else {
            oldSum = sum;
            sum = 0;
        }
        
        vIt++;
    }
    cout << maxSum;
    
    return 0;
}