/*
描述
根据输入的日期，计算是这一年的第几天。
保证年份为4位数且日期合法。
进阶：时间复杂度：O(n) O(n)\ O(n) ，空间复杂度：O(1) O(1)\ O(1) 
输入描述：

输入一行，每行空格分割，分别是年，月，日
输出描述：
输出是这一年的第几天
示例1
输入：
2012 12 31
输出：
366

示例2
输入：
1982 3 4
输出：
63

原题链接：https://www.nowcoder.com/practice/769d45d455fe40b385ba32f97e7bcded
*/

#include <iostream>
using std::cout;
using std::cin;

bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int main()
{
    int dayArray[13] = { 0,31,59,90,120,151,181,212,243,273,304,334,365 };
    int year,month,day;
    //scanf("%d%d%d",&year,&month,&day);
    cin >> year >> month >> day;
    
    int yearDay = dayArray[month-1] + day;
    if(month > 2 && isLeapYear(year))
    {
        yearDay++;
    }
    cout << yearDay;
    
    return 0;
}