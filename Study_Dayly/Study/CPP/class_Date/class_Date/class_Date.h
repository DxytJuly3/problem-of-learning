#pragma once
#include <iostream>
using namespace std;

class Time
{
public:
	// ����ʱ�����ȫȱʡ���캯������ΪĬ�Ϲ��캯��
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
	// ����������ʽ���캯����ʹ�������Զ�����

	void Display()
	{
		cout << _year << "-" << _month << "-" << _day;
		_time.Display();
	}
private:
	// ��������
	int _year;
	int _month;
	int _day;

	// �Զ�������
	Time _time;
};