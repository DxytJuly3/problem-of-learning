/*

描述
    请考虑性能
输入描述：
    一个整数N
输出描述：
    小于N的质数数量

备注：
    0、1 不属于质数。

来源：牛客（Nowcoder）
链接：https://www.nowcoder.com/practice/9e7a88d6a00e404c8418602515a5046c
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

// 首先要知道什么是质数
// 1-本身之间，除了 1 和 本身没有其他可以整除的数 叫质数
// 并且经过分析可以发现 大于十的数中 只有个位是 1 3 7 9的数 才有可能是质数
// 而 10 以内的质数有 2 3 5 7，所以 10以内可以单独判断
#include <iostream>
#include <cmath>
using std::cin;
using std::cout;
using std::endl;

int main() {
    long long n = 0;
    cin >> n;
    if(n < 2) {
        cout << 0;
    }
    else if(n == 2) {
        cout << 1;
    }
    else if(n >= 3 && n < 5) {
        cout << 2;
    }
    else if(n >= 5 && n < 7) {
        cout << 3;
    }
    else {
        size_t count = 3;
        for(int i = 7; i <= n; i += 2) {    //偶数不是，所以 += 2
            if(i % 10 == 1 || i % 10 == 3 || i % 10 == 7 || i % 10 == 9) {
                size_t flag = 0;
                for(int j = 2; j <= sqrt(i); j++) {
                    if(i % j == 0) {
                        flag = 1;
                        break;
                    }
                }
                if(flag == 0)
                    count++;
            }
        }
        cout << count;
    }
    
    return 0;
}