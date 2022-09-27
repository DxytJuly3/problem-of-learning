/*
链接：https://www.nowcoder.com/questionTerminal/f8538f9ae3f1484fb137789dec6eedb9
来源：牛客网

任意一个偶数（大于2）都可以由2个素数组成，组成偶数的2个素数有很多种情况，本题目要求输出组成指定偶数的两个素数差值最小的素数对。
数据范围：输入的数据满足 4≤n≤1000 4 \le n \le 1000 \ 4≤n≤1000 
输入描述:
输入一个大于2的偶数
输出描述:
从小到大输出两个素数
示例1
输入
20
输出
7
13

示例2
输入
4
输出
2
2
*/
/*
思路分析：
    将给定的偶数除以2, 找最接近结果的一个素数
    找到之后 用原数减去找到的素数, 就是所求的两个素数
*/
#include <iostream>
#include <math.h>
using namespace std;
bool isPrime(int n) {
    for(int i = 2; i <= sqrt(n); i++) {
        if((n % i) == 0)
            return false;
    }
     
    return true;
}
 
int main() {
    int n = 0;
    cin >> n;
    int halfN = n / 2;
    while(1 && halfN != 2){
        // halN == 2时, 直接输出halN就可以了
        if(halfN % 2 == 0)
            halfN++;
        if(isPrime(halfN)) {
            if(isPrime(n-halfN))
                break;
        }
        halfN += 2;
    }
    cout << n - halfN << endl << halfN << endl;
     
    return 0;
}