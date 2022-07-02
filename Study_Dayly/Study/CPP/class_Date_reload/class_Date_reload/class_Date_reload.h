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

	// �����ж�
	bool isLeapYear(int year)
	{
		return (year % 4 == 0 && year % 100 != 0)
			|| (year % 400 == 0);
	}
	// �·�������ȡ
	int GetMonthDay(int year, int month);

	// ��С inlineʹ��
	bool operator==(const Date& d)
	{
		return _year == d._year
			&& _month == d._month
			&& _day == d._day;
	}
	bool operator!=(const Date& d)
	{
		return !(*this == d);			// �ܸ��þ�������
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

	// ���� + ���� ---> ����
	Date operator+(int day);
	Date& operator+=(int day);

	// ���� - ���� ---> ����
	Date operator-(int day);
	Date& operator-=(int day);

	// ǰ��++
	Date& operator++();
	// ����++
	Date operator++(int);		
	// ǰ��--
	Date& operator--();
	// ����--
	Date operator--(int);
	// C++ �涨��++��-- ����������أ�ǰ���޲Ρ�������һint���Ͳ���(���������ֶ����� ֻ��Ϊ������ǰ���ã�����������)

	// ���� - ���� ---> ����
	int operator-(const Date& d);
	
	// ��ֵ����
	Date& operator=(const Date& d);

private:
	int _year;
	int _month;
	int _day;
};
