/*
链接：https://www.nowcoder.com/questionTerminal/4b1658fd8ffb4217bc3b7e85a38cfaf2
来源：牛客网

求一个int类型数字对应的二进制数字中1的最大连续数，例如3的二进制为00000011，最大连续2个1
数据范围：数据组数：1≤t≤5 1\le t\le 5\ 1≤t≤5 ，1≤n≤500000 1\le n\le 500000\ 1≤n≤500000 
进阶：时间复杂度：O(logn) O(logn)\ O(logn) ，空间复杂度：O(1) O(1)\ O(1) 

输入描述:
输入一个int类型数字

输出描述:
输出转成二进制之后连续1的个数

示例1
输入
200
输出
2
说明
200的二进制表示是11001000，最多有2个连续的1。  
*/
/*
思路分析：
    思路:与 求int数据二进制 有多少位1一样,
    将 int数据 & 1, 如果结果 == 1, 则表示末位为1, 1计数++, 并记录是否最大;
    如果结果不等于1, 则表示末位为0, 1计数归零
    然后 数据 >>= 1, 循环直到 数据为0
*/
#include <iostream>
using namespace std;
 
int main() {
    int oneMax = 0;
    int n;
    cin >> n;
    int one = 0;
    while(n != 0) {
        if(n & 1 == 1){
            one++;
            if(one > oneMax)
                oneMax = one;
        }
        else {
            one = 0;
        }
        n >>= 1;
    }
    cout << oneMax << endl;
     
    return 0;
}