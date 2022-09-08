/*
【排序子序列】牛牛定义排序子序列为一个数组中一段连续的子序列,并且这段子序列是非递增或者非递减排序的。
牛牛有一个长度为n的整数数组A,他现在有一个任务是把数组A分为若干段排序子序列,牛牛想知道他最少可以把这个数组分为几段排序子序列.
如样例所示,牛牛可以把数组A划分为[1,2,3]和[2,2,1]两个排序子序列,至少需要划分为2个排序子序列,所以输出2

输入描述：
输入的第一行为一个正整数n(1 ≤ n ≤ 10^5)
第二行包括n个整数A_i(1 ≤ A_i ≤ 10^9),表示数组A的每个数字
输出描述：
输出一个整数表示牛牛可以将A最少划分为多少段排序子序列

示例1：
输入:
6
1 2 3 2 2 1
输出
2
*/

/*
题意分析：
按顺序输入 n 个数，不改变这组数的顺序，将这组数划分为若干段有序的子组 且划分的有序子组最少
例如：13487247890123 可分为 1348 72 4789 0123
思路分析：
解法：将输入的数存储起来，然后 使用两个指针一前一后遍历数组
根据指针指向内容的大小关系变化来判断是否可以划出 有序的子组
在遍历过程中 两指针指向内容大小关系发生变化 即表示排序方式发生了变化
所以 大小关系发生变化的次数 + 1，即为可以分为子序列的个数
问题在于 怎么判断 这一次的大小关系 较 上一次的大小关系 发生了变化
只用一个循环 来逐个遍历 逐个比较，逐个的判断 有些麻烦
所以可以采用另一种思路：
依旧外循环遍历，但是
1. 当大小关系是 > 时, 内循环找大小关系 <,找到的话 子序列数+1,且指针位置++
2. 当大小关系是 < 时, 内循环找大小关系 >,找到的话 子序列数+1,且指针位置++
3. 当大小关系是 == 时, 指针位置++ 并进入下一次外循环
举个实例：
划分 1 3 4 6 7 5 2 1 3 7 9 8 4 2 2 3 3 3 4 5 7
第一次进入外循环, 判断出 1(slow) < 3(fast), 则嵌套循环向后找 slow > fast的情况,
找到 7(slow) > 5(fast), 次数 +1 且 slow和fast ++
第二次进入外循环, 判断出 5(slow) > 2(fast), 则嵌套循环向后找 slow < fast的情况,
找到 1(slow) < 3(fast), 次数 +1 且 slow和fast ++
第三次进入外循环, 判断出 3(slow) < 7(fast), 则嵌套循环向后找 slow > fast的情况,
找到 9(slow) > 8(fast), 次数 +1 且 slow和fast ++
第四次进入外循环, 判断出 8(slow) > 4(fast), 则嵌套循环向后找 slow < fast的情况,
找到 2(slow) < 3(fast), 次数 +1 且 slow和fast ++
第五次进入外循环, 判断出 3(slow) == 3(fast), 则slow和fast ++,进入下一次外循环
第六次进入外循环, 判断出 3(slow) == 3(fast), 则slow和fast ++,进入下一次外循环\
第七次进入外循环, 判断出 3(slow) < 4(fast), 则嵌套循环向后找 slow > fast的情况,
直到结束也没有找到 所以次数不加
最终 即为 1 + (1 + 1 + 1 + 1)
*/
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> arrV;
    for(int i = 0; i < n; i++) {
        int num;
        cin >> num;
        arrV.push_back(num);
    } 
    int result = 1;
    auto fastIt = arrV.begin() + 1;
    auto slowIt = arrV.begin();
    while(fastIt != arrV.end()) {
        if(*fastIt > *slowIt) {
            while(*fastIt >= *slowIt && fastIt != arrV.end()) {
                fastIt++;
                slowIt++;
            }
            if(fastIt != arrV.end()) {
                fastIt++;
                slowIt++;
                result++;
            }
        }
        else if(*fastIt < *slowIt) {
            while(*fastIt <= *slowIt && fastIt != arrV.end()) {
                fastIt++;
                slowIt++;
            }
            if (fastIt != arrV.end()){
                fastIt++;
                slowIt++;
                result++;
            }
        }
        else{
            if(fastIt != arrV.end()) {
                fastIt++;
                slowIt++;
            }
        }
    }
    cout << result;
    return 0;
}