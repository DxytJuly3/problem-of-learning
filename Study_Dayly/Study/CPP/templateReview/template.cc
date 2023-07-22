#include "template.hpp"

template <class T>
seqList<T>::seqList(int n)
	: _data(new T[n])
	, _capacity(n)
	, _size(0) {}

template <class T>
seqList<T>::~seqList() {
	if (_data) {
		delete[] _data;
	}
	_size = _capacity = 0;
}
