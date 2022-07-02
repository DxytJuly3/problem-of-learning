#pragma once
#include <iostream>
using namespace std;

class Time
{
public:
	// 定义时间类的全缺省构造函数，作为默认构造函数
	Time(int hour = 1, int minite = 1, int second = 1)
	{
		_hour = hour;
		_minite = minite;
		_second = second;
	}
	/*Time(int hour, int minite, int second)
	{
		_hour = hour;
		_minite = minite;
		_second = second;
	}*/

	void Display()
	{
		cout << "  " << _hour << ":" << _minite << ":" << _second << endl;
	}

private:
	int _hour;
	int _minite;
	int _second;
};

class Date
{
public:
	// 日期类无显式构造函数，使编译器自动生成

	void Display()
	{
		cout << _year << "-" << _month << "-" << _day;
		_time.Display();
	}
private:
	// 内置类型
	int _year;
	int _month;
	int _day;

	// 自定义类型
	Time _time;
};