/*
描述
设计一个程序能计算一个日期加上若干天后是什么日期。
输入描述：
输入第一行表示样例个数m，接下来m行每行四个整数分别表示年月日和累加的天数。
输出描述：
输出m行，每行按yyyy-mm-dd的个数输出。
示例1
输入：
1
2008 2 3 100
输出：
2008-05-13

原题地址：https://www.nowcoder.com/practice/eebb2983b7bf40408a1360efb33f9e5d
*/

#include <iostream>
using std::cout;
using std::cin;

class Date
{
public:
    bool isLeapYear(int year)
    {
        return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    }
    int getMonthDay(int year, int month)
    {
        static int MonthDayArray[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
        if (month == 2 && isLeapYear(year))
        {
            return 29;
        }

        return MonthDayArray[month];
    }
    Date()
    {
        scanf("%d%d%d", &_year, &_month, &_day);
    }
    void Print()
    {
        printf("%d-%02d-%02d\n", _year, _month, _day);
    }

    Date& operator+=(int day)
    {
        _day += day;
        while (_day > getMonthDay(_year, _month))
        {
            _day -= getMonthDay(_year, _month);
            _month++;
            if (_month == 13)
            {
                _year++;
                _month = 1;
            }
        }

        return *this;
    }

private:
    int _year;
    int _month;
    int _day;
};

int main()
{
    int n = 0;
    cin >> n;
    while (n--)
    {
        Date d1;
        int day;
        cin >> day;

        d1 += day;
        d1.Print();
    }

    return 0;
}