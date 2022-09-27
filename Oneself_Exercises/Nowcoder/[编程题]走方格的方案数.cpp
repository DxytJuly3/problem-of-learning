/*
链接：https://www.nowcoder.com/questionTerminal/e2a22f0305eb4f2f9846e7d644dba09b
来源：牛客网

请计算n*m的棋盘格子（n为横向的格子数，m为竖向的格子数）从棋盘左上角出发沿着边缘线从左上角走到右下角，总共有多少种走法，要求不能走回头路，即：只能往右和往下走，不能往左和往上走。
注：沿棋盘格之间的边缘线行走
数据范围： 1≤n,m≤8 1 \le n,m \le 8 \ 1≤n,m≤8 

输入描述:
输入两个正整数n和m，用空格隔开。(1≤n,m≤8)

输出描述:
输出一行结果

示例1
输入
2 2
输出
6
*/
/*
题意分析：
    输入n 和 m, n为横向格子数, m为竖向格子数
    不走格子而走线, 且不能回头, 只能向下或向右, 从左上角走到右下角有多少个路线
 
思路分析：
    经过画图，可以发现 n = 1 或 m = 1时, 方案数即为 n+m
    而且 n 或 m 不为1时, 每向下 或 向右 走一步, 剩下的方案即为 n-1 和 m的方案, 或 n,m-1的方案
    而每个格子 均有且只有 向下 或 向右两种走法, 所以 一个格子可以走的方案数 时 n-1 和 m的方案数 + n 和 m-1的方案数
    所以可以用递归解法
*/
#include <iostream>
using namespace std;
int programCount(int n, int m) {
    if(m == 1 || n == 1)
        return m+n;
    else
        return programCount(n, m-1) + programCount(n-1, m);
}
 
int main() {
    int n, m;
    cin >> n >> m;
    cout << programCount(n, m);
     
    return 0;
}