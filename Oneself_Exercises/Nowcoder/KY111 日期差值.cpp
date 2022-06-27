/*
描述
有两个日期，求两个日期之间的天数，如果两个日期是连续的我们规定他们之间的天数为两天
输入描述：
有多组数据，每组数据有两行，分别表示两个日期，形式为YYYYMMDD
输出描述：
每组数据输出一行，即日期差值
示例1
输入：
20110412
20110422
输出：
11

原题链接：https://www.nowcoder.com/practice/ccb7383c76fc48d2bbc27a2a6319631c
*/

#include <iostream>
using std::cout;
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
    {
        scanf("%4d%2d%2d", &_year, &_month, &_day);
    }

    bool operator<(const Date& d) const
    {
        return (_year < d._year)
            || (_year == d._year && _month < d._month)
            || (_year == d._year && _month == d._month && _day < d._day);
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
    Date& operator++()
    {
        *this += 1;

        return *this;
    }
    int operator-(const Date& d)
    {
        Date max = *this;
        Date min = d;
        if (*this < d)
        {
            max = d;
            min = *this;
        }

        int count = 0;
        while (min < max)
        {
            count++;
            min += 1;
        }

        return count;
    }

private:
    int _year;
    int _month;
    int _day;
};

int main()
{
    Date d1;
    Date d2;
    cout << (d1 - d2 + 1);

    return 0;
}
