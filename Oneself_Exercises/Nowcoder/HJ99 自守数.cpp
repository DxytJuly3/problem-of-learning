/*
描述
自守数是指一个数的平方的尾数等于该数自身的自然数。例如：25^2 = 625，76^2 = 5776，9376^2 = 87909376
请求出n(包括n)以内的自守数的个数
数据范围： 1≤n≤10000 1 \le n \le 10000 \ 1≤n≤10000
输入描述：
int型整数
输出描述：
n以内自守数的数量。

示例1
输入：
6
输出：
4
说明：
有0，1，5，6这四个自守数      

示例2
输入：
1
输出：
2
说明：
有0, 1这两个自守数


来源：牛客（Nowcoder）
链接：https://www.nowcoder.com/practice/88ddd31618f04514ae3a689e83f3ab8e
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <string>
using namespace std;

// 首先 观察示例可发现规律：
// 只有 末位为 0 1 5 6 的数可能为自守数，可以以此为基础优化
// 思路：
//    对比 该数与平方数的后几位
//
// 写法1：
// 直接 使用int类型数据对比，总对比个位数 每对比一次数据 /10
int main() {
    int n = 0;
    while(cin >> n) {
        size_t count = 0;
        for(int i = 0; i <= n; i++) {
            if((i%10 == 0) || (i%10 == 1) || (i%10 == 5) || (i%10 == 6)) {
                int tmp = i;
                int tmpSq = i*i;
                while(tmp) {
                    if((tmp % 10) != (tmpSq % 10)) {    //对比个位数 
                        break;    // 各位不相等 直接退出对比
                    }
                    tmp /= 10;
                    tmpSq /= 10;
                }
                if(!tmp)
                    count++;
            }
        }
        cout << count;
    }
    
    return 0;
}

// 写法2：
//将数据转换为 string类型，对比 square后几位 与 该数
/*size_t countAutonomicNumber(int n) {
    size_t count = 0;
    for(int i = 0; i <= n; i++) {
        if((i%10 == 0) || (i%10 == 1) || (i%10 == 5) || (i%10 == 6)) {
            string nStr = to_string(i);
            string nSqStr = to_string(i*i);
            
            // 以下对比的过程可以直接 使用 find 在 nSqStr中查找nStr
            while(!nStr.empty()) {
                size_t nSize = nStr.size();
                size_t nSqSize = nSqStr.size();
                if(nStr[nSize-1] == nSqStr[nSqSize-1]) {
                    nStr.pop_back();
                    nSqStr.pop_back();
                }
                else {
                    break;
                }
            }
            if(nStr.empty())
                count++;
        }
    }
    
    return count;
}

int main() {
    int n = 0;
    while(cin >> n) {
        cout << countAutonomicNumber(n) << endl;
    }
    
    return 0;
}*/