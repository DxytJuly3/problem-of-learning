#pragma once
#include <iostream>
using namespace std;


class Date
{
public:
	// Date�� ȫȱʡĬ�Ϲ��캯��
	Date(int year = 1, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	// Date�� �������캯��
	/*Date(const Date& D)
	{
		_year = D._year;
		_month = D._month;
		_day = D._day;
	}*/

	// Date�� ��������
	~Date()
	{
		_year = _month = _day = 0;
	}

	void print()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}

private:
	// ��������
	int _year;
	int _month;
	int _day;
};