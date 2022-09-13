/*
写出一个程序，接受一个正浮点数值，输出该数值的近似整数值。
如果小数点后数值大于等于 0.5 ,向上取整；小于 0.5 ，则向下取整。

数据范围：保证输入的数字在 32 位浮点数范围内
输入描述：
输入一个正浮点数值
输出描述：
输出该数值的近似整数值

示例1
输入：
5.5
输出：
6
说明：
0.5>=0.5，所以5.5需要向上取整为6   

示例2
输入：
2.499
输出：
2
说明：
0.499<0.5，2.499向下取整为2

来源：牛客
链接：https://www.nowcoder.com/practice/3ab09737afb645cc82c35d56a5ce802a
*/

#include <iostream>
using namespace std;

int main(){
    double n;
    cin >> n;
    if(n - (int)n >= 0.5) {
        cout << (int)n+1;
    }
    else 
        cout << (int)n;

    return 0;
}