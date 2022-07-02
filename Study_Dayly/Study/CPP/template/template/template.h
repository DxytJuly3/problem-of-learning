#pragma once

#include <iostream>
using std::cout;
using std::endl;

template<typename T>
void swap(T& left, T& right)
{
	T tmp = left;
	left = right;
	right = tmp;
}

template<typename T>
T* func(int n)
{
	return new T[n];
}


template<typename T1, typename T2>
T2 add(T1& a, T2& b)
{
	return a + b;
}

template<class T>
class SeqList
{
public:
	SeqList(size_t capacity = 10)
		: _pData(new T[capacity])
		, _size(0)
		, _capacity(capacity)
	{}
	~SeqList();

private:
	T* _pData;
	size_t _size;
	size_t _capacity;
};

template <class T>
SeqList<T>::~SeqList()
{
	if (_pData)
		delete[] _pData;
	_size = _capacity = 0;
}

