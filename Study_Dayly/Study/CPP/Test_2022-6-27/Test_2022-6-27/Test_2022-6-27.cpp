#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using std::cout;
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
    {
        scanf("%d%d%d", &_year, &_month, &_day);
    }
    void Print()
    {
        cout << _year << "-" << _month << "-" << _day << endl;
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
