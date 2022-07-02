#pragma once

#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;

class SeqList
{
public:
	// 全缺省默认构造函数
	SeqList(int capacity = 4)
	{
		_data = (int*)malloc(sizeof(int)* capacity);
		assert(_data);

		_size = 0;
		_capacity = capacity;
	}

	// 不显式实现拷贝构造
	// …………浅拷贝

	// SeqList类 析构函数
	~SeqList()
	{
		free(_data);
		_data = nullptr;
		_size = _capacity = 0;
	}

private:
	int* _data;
	int _size;
	int _capacity;
};