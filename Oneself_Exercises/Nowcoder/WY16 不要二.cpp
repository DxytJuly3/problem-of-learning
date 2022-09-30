/*
描述
二货小易有一个W*H的网格盒子，网格的行编号为0~H-1，网格的列编号为0~W-1。每个格子至多可以放一块蛋糕，任意两块蛋糕的欧几里得距离不能等于2。
对于两个格子坐标(x1,y1),(x2,y2)的欧几里得距离为:
( (x1-x2) * (x1-x2) + (y1-y2) * (y1-y2) ) 的算术平方根
小易想知道最多可以放多少块蛋糕在网格盒子里。
输入描述：
每组数组包含网格长宽W,H，用空格分割.(1 ≤ W、H ≤ 1000)
输出描述：
输出一个最多可以放的蛋糕数

示例1
输入：
3 2
输出：
4
*/
/*
分析题意:
    蛋糕放的位置 x坐标的差^2 + y坐标的差^2 不能等于 4
    也就是说 x1-x2(y1-y2) == 0 时, y1-y2(y2-y1) != 2
         或 x1-x2(y1-y2) == 2 时, y1-y2(y2-y1) != 0
    即 两坐标x 相等时, y坐标不能相差2
       两坐标y 相等时, X坐标不能相差2
    模拟坐标可以发现下面这种规律可以存放
     
       0  1  2  3  4  5  6  7  8      9
    0  x  x        x  x        x      x
    1  x  x        x  x        x      x
    2        x  x        x  x
    3        x  x        x  x
    4  x  x        x  x        x      x
    5  x  x        x  x        x      x
    6        x  x        x  x
    7        x  x        x  x
    8  x  x        x  x        x      x
     
     
    9  x  x        x  x        x      x
    可以发现 行列坐标 以 2 为单位分为 可放 : 不可放
    所以 只需要数 行列坐标 可放 不可放的数量 可放行*可放列 + 不可放行*不可放列 就是最终的蛋糕数
*/
#include <iostream>
using namespace std;
 
int main() {
    int w, h;
    cin >> w;
    cin >> h;
    int placeYW = 0, placeNW = 0, placeYH = 0, placeNH = 0;
    placeYW = w/4*2 + (w%4 >= 2 ? 2 : w%4);
    placeNW = w - placeYW;
    placeYH = h/4*2 + (h%4 >= 2 ? 2 : h%4);
    placeNH = h - placeYH;
    cout << placeYW*placeYH + placeNW*placeNH;
     
    return 0;
}