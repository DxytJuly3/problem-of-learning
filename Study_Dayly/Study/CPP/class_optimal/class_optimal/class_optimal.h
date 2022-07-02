#pragma once

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

class Widget
{
public:
	Widget()
	{
		cout << "Widget()" << endl;
	}
	Widget(const Widget& d)
	{
		cout << "Widget(const Widget& d)" << endl;
	}
	/*~Widget()
	{
		cout << "~Widget()" << endl;
	}*/

	Widget& operator=(const Widget& w)
	{
		cout << "operator+(const Widget& w)" << endl;

		return *this;
	}
};

