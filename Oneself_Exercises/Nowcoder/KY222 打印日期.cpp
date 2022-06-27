/*
描述
给出年分m和一年中的第n天，算出第n天是几月几号。
输入描述：
输入包括两个整数y(1<=y<=3000)，n(1<=n<=366)。
输出描述：
可能有多组测试数据，对于每组数据， 按 yyyy-mm-dd的格式将输入中对应的日期打印出来。
示例1
输入：
2000 3
2000 31
2000 40
2000 60
2000 61
2001 60

输出：
2000-01-03
2000-01-31
2000-02-09
2000-02-29
2000-03-01
2001-03-01

原题地址：https://www.nowcoder.com/practice/b1f7a77416194fd3abd63737cdfcf82b
*/

#include <iostream>
using std::cin;
using std::endl;

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
        :_month(1)
        ,_day(0)
    {
        scanf("%d", &_year);
    }
    void Print()
    {
        printf("%d-%02d-%02d", _year, _month, _day);
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
    Date d1;
    int day;

    cin >> day;
    d1 += day;
    d1.Print();

    return 0;
}