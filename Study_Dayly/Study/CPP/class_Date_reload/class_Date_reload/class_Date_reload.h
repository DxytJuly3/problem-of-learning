#pragma once

#include <iostream>
#include <cassert>
using std::cout;
using std::cin;
using std::endl;

class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1);

	void print()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}

	// 闰年判断
	bool isLeapYear(int year)
	{
		return (year % 4 == 0 && year % 100 != 0)
			|| (year % 400 == 0);
	}
	// 月份天数获取
	int GetMonthDay(int year, int month);

	// 短小 inline使用
	bool operator==(const Date& d)
	{
		return _year == d._year
			&& _month == d._month
			&& _day == d._day;
	}
	bool operator!=(const Date& d)
	{
		return !(*this == d);			// 能复用尽量复用
	}

	bool operator>(const Date& d)
	{
		return (_year > d._year)
			|| (_year == d._year && _month > d._month)
			|| (_year == d._year && _month == d._month && _day > d._day);
	}
	bool operator>=(const Date& d)
	{
		return *this > d || *this == d;
	}

	bool operator<(const Date& d)
	{
		return !(*this >= d);
	}
	bool operator<=(const Date& d)
	{
		return *this < d || *this == d;
	}

	// 日期 + 天数 ---> 日期
	Date operator+(int day);
	Date& operator+=(int day);

	// 日期 - 天数 ---> 日期
	Date operator-(int day);
	Date& operator-=(int day);

	// 前置++
	Date& operator++();
	// 后置++
	Date operator++(int);		
	// 前置--
	Date& operator--();
	// 后置--
	Date operator--(int);
	// C++ 规定，++、-- 的运算符重载，前置无参、后置有一int类型参数(但是无需手动传参 只是为了区分前后置，编译器传参)

	// 日期 - 日期 ---> 天数
	int operator-(const Date& d);
	
	// 赋值重载
	Date& operator=(const Date& d);

private:
	int _year;
	int _month;
	int _day;
};
