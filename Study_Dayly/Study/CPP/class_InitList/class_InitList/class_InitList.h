#pragma once

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::cin;



class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
		:_year(year)
		,_month(month)
		,_day(day)
	{}
	void Print()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};

class A
{
public:
	// 显式定义构造函数(非默认构造函数)
	A(int a)
		:_a(a)
	{}
private:
	int _a;
};

class B
{
public:
	B(int x = 10, int b = 15)
		:_i(20)
		, _y(x)
		, _a(b)
	{}

private:
	const int _i;
	int& _y;
	A _a;
};

class C
{
public:
	explicit C(int year = 1900)
		:_year(year)
	{}

private:
	int _year = 1;
};

class D
{
public:
	D(int a)
		:_a1(a)
		, _a2(_a1)
	{}
	void Print()
	{
		cout << _a1 << " " << _a2 << endl;
	}

private:
	int _a2;
	int _a1;
};

class X
{
public:
	X()
	{
		_x++;
	}
	static int getX()
	{
		return _x;
	}
private:
	int _xx;
	static int _x;
};

int X::_x = 0;
