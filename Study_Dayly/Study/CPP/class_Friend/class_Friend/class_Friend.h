#pragma once

#include <iostream>
using std::istream;
using std::ostream;
using std::cout;
using std::endl;
using std::cin;

class Date
{
    friend ostream& operator<<(ostream& _cout, const Date& d);
    friend istream& operator>>(istream& _cin, Date& d);

public:
    Date(int year = 1900, int month = 1, int day = 1)
        :_year(year)
        , _month(month)
        , _day(day)
    {}

private:
    int _year;
    int _month;
    int _day;
};

ostream& operator<<(ostream& _cout, const Date& d)
{
    cout << d._year << "-" << d._month << "-" << d._day << endl;

    return _cout;
}
istream& operator>>(istream& _cin, Date& d)
{
    cin >> d._year >> d._month >> d._day;

    return _cin;
}

class A
{
public:
    A(int a = 1)
        :_a(a)
    {}
    class B
    {
    public:
        void Func(const A& a)
        {
            cout << _x << endl;
            cout << a._a << endl;
        }
    private:
        int _b;
    };

private:
    int _a;
    static int _x;
};

int A::_x = 1;