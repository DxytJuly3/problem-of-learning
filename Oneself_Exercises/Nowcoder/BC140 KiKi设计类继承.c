//暂时不会按照描述写
//KiKi理解了继承可以让代码重用，他现在定义一个基类shape，私有数据为坐标点x,y
//由它派生Rectangle类和Circle类
//它们都有成员函数GetArea()求面积
//派生类Rectangle类有数据：矩形的长和宽；
//派生类Circle类有数据：圆的半径。
//Rectangle类又派生正方形Square类，定义各类并测试。
//输入三组数据，分别是矩形的长和宽、圆的半径、正方形的边长，输出三组数据，分别是矩形、圆、正方形的面积。圆周率按3.14计算。
#include <stdio.h>

int main()
{
    int c = 0, k = 0, r = 0, d = 0;
    scanf("%d%d", &c, &k);
    scanf("%d", &r);
    scanf("%d", &d);
    printf("%d\n", c * k);
    printf("%g\n",r * r * 3.14);
    printf("%d",d * d);
    
    return 0;
}