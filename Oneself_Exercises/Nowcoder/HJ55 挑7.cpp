/*
描述
输出 1到n之间 的与 7 有关数字的个数。
一个数与7有关是指这个数是 7 的倍数，或者是包含 7 的数字（如 17 ，27 ，37 ... 70 ，71 ，72 ，73...）

数据范围： 1≤n≤30000 1 \le n \le 30000 \ 1≤n≤30000 

输入描述：
一个正整数 n 。( n 不大于 30000 )
输出描述：
一个整数，表示1到n之间的与7有关的数字个数。

示例1
输入：
20

输出：
3

说明：
输入20，1到20之间有关的数字包括7,14,17共3个。 

来源: 牛客
链接：https://www.nowcoder.com/practice/ba241b85371c409ea01ac0aa1a8d957b
*/

/*
思路分析：
    思路1：
        最笨的思路, 遍历从 7 到 N, 判断每个数是否是 7的倍数或 某一位上有7
*/
#include<iostream>
using namespace std;

bool isForSeven(int n) {
    if(n % 7 == 0)
            return true;
    do{
        if(n % 10 == 7)
            return true;
    }while(n /= 10);
    
    return false;
}
int main() {
    int n;
    cin >> n;
    int count = 0;
    for(int i = 7; i <= n; i++) {
        if(isForSeven(i))
            count++;
    }
    cout << count;
    
    return 0;
}