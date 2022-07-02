#pragma once

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::exception;

class Test
{
public:
	Test()
		: _data(0)
	{
		cout << "Test():" << endl;
	}
	~Test()
	{
		cout << "~Test():" << endl;
	}

private:
	int _data;
};

class Stack
{
public:
private:
};

class SeqList
{
public:
	SeqList(int capacity = 4)
		:_capacity(capacity)
		, _size(0)
	{
		_data = new int[capacity];
	}

private:
	int* _data;
	int _size;
	int _capacity;
};

class Myqueque
{
public:
private:
	Stack _pushSt;
	Stack _popSt;
};