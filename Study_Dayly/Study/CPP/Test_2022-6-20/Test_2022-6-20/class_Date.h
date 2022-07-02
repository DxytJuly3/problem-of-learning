#pragma once
#include <iostream>
using namespace std;


class Date
{
public:
	// Date类 全缺省默认构造函数
	Date(int year = 1, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	// Date类 拷贝构造函数
	/*Date(const Date& D)
	{
		_year = D._year;
		_month = D._month;
		_day = D._day;
	}*/

	// Date类 析构函数
	~Date()
	{
		_year = _month = _day = 0;
	}

	void print()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}

private:
	// 内置类型
	int _year;
	int _month;
	int _day;
};