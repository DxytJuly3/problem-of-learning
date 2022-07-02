#pragma once

#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;

class SeqList
{
public:
	// ȫȱʡĬ�Ϲ��캯��
	SeqList(int capacity = 4)
	{
		_data = (int*)malloc(sizeof(int)* capacity);
		assert(_data);

		_size = 0;
		_capacity = capacity;
	}

	// ����ʽʵ�ֿ�������
	// ��������ǳ����

	// SeqList�� ��������
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