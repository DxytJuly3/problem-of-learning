#pragma once

#include <iostream>

template <class T>
class seqList {
public:
	seqList(int n = 10);
	~seqList();

private:
	T* _data;
	size_t _capacity;
	size_t _size;
};
