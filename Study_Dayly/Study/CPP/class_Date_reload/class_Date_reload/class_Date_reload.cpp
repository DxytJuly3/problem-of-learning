#include "class_Date_reload.h"

// 全缺省构造函数
Date::Date(int year, int month, int day)
{
	if (year >= 1
		&& month >= 1 && month <= 12
		&& day >= 1 && day <= GetMonthDay(year, month))
	{
		_year = year;
		_month = month;
		_day = day;
	}
	else
	{
		cout << "日期设置非法" << endl;
	}
}

// 月份天数获取
int Date::GetMonthDay(int year, int month)
{
	assert(year >= 1 && (month >= 1 && month <= 12));

	static int MonthDayArray[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	// static 修饰：此函数可能被频繁调用，加static修饰可以避免频繁开辟空间

	if (month == 2 && isLeapYear(year))
	{
		return 29;
	}

	return MonthDayArray[month];
}
// 日期 + 天数 ---> 日期
Date Date::operator+(int day)
{
	Date ret(*this);

	ret += day;			// 复用 +=

	return ret;
}
Date& Date::operator+=(int day)
{
	if (day < 0)
		return *this -= -day;

	_day += day;
	while (_day > GetMonthDay(_year, _month))
	{
		_day -= GetMonthDay(_year, _month);
		_month++;
		if (_month == 13)
		{
			_year++;
			_month = 1;
		}
	}

	return *this;
}

// 日期 - 天数 ---> 日期
Date Date::operator-(int day)
{
	Date ret(*this);

	ret -= day;			// 复用 -=

	return ret;
}
Date& Date::operator-=(int day)
{
	if (day < 0)
		return *this += -day;

	while (day >= _day)
	{
		day -= _day;
		--_month;
		if (_month == 0)
		{
			_year--;
			_month = 12;
		}
		_day = GetMonthDay(_year, _month);
	}
	_day -= day;

	return *this;
}

// 前置++
Date& Date::operator++()
{
	*this += 1;

	return *this;
}
// 后置++
Date Date::operator++(int)
{
	Date tmp(*this);
	*this += 1;

	return tmp;
}
// 前置--
Date& Date::operator--()
{
	*this -= 1;

	return *this;
}
// 后置--
Date Date::operator--(int)
{
	Date tmp(*this);
	*this -= 1;

	return tmp;
}



// 日期 - 日期 ---> 天数
int Date::operator-(const Date& d)
{
	Date max = *this;
	Date min = d;
	int flag = 1;
	if (*this < d)
	{
		max = d;
		min = *this;
		flag = -1;
	}

	int day = 0;
	while (min != max)
	{
		++day;
		++min;
	}

	return day * flag;
}

Date& Date::operator=(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;

	// 由于需要连等赋值，所以需要将结果作为返回值，返回
	return *this;		//返回值 用类的引用，节省资源 (直接返回 值 会调用拷贝构造)
	// 返回值类型不能用 const修饰 因为 类似(d1 = d2) = d3;这样的表达式 会先计算(d1 = d2) 如果结果被const修饰了，则无法给其赋值
}
