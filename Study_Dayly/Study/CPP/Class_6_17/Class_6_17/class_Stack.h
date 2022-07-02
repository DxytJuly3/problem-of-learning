#pragma once
#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;

class Stack 
{
public:
	// 栈的初始化
	void StackInit()
	{
		_data = nullptr;
		_top = 0;			// 栈顶初始位置定义 (top = -1, 先++后赋值; top = 0, 先赋值后++)
		_capacity = 0;
	}
	// 栈的销毁
	void StackDestroy()
	{
		free(_data);
		_data = nullptr;
		_top = _capacity = 0;
	}
	// 压栈
	void StackPush(int x)
	{
		if (_top == _capacity)
		{
			int newCapacity = _capacity == 0 ? 4 : _capacity * 2;
			int* tmp = (int*)realloc(_data, newCapacity * sizeof(int));
			if (tmp == nullptr)
			{
				printf("realloc failed\n");
				exit(-1);
			}
			else
				_data = tmp;

			_capacity = newCapacity;
		}

		_data[_top++] = x;
	}
	// 出栈
	void StackPop()
	{
		assert(_top > 0);

		--_top;
	}
	// 判空
	bool StackEmpty()
	{
		return _top == 0;			// top 等于 0 栈为空，返回 true; 不等于 0 ，返回 false
	}
	// 栈顶数据
	int StackTop()
	{
		return _data[_top - 1];
	}

private:
	int *_data;
	int _top;				// 栈顶位置
	int _capacity;			// 栈的容量
};