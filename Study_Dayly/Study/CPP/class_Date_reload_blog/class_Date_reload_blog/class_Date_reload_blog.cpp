#include "class_Date_reload_blog.h"

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