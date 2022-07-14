#pragma once

#include "STL-myStack_Queue.h"

namespace July
{
	// ��stack���ƣ�STLԴ���У�queue��ʵ��Ҳ������������ʵ�ֵ�
	//
	// queue ����
	// ��һ���Ƚ��ȳ������ݽṹ�������Ŷ�ֻ��β��ͷɾ����ȡ��ͷ�Ͷ�λ��Ԫ��
	template<class T, class Container = deque<T>>
	class queue
	{
	public:
		// ͬ���ĵ���queue����Ҫ��ʽ���幹�캯��
		//
		// ��� --> β��
		void push(const T& val)
		{
			_con.push_back(val);
		}
		// ���� --> ͷɾ
		void pop()
		{
			_con.pop_front();
		}
		// ȡ��ͷԪ��
		const T& front()
		{
			return _con.front();
		}
		// ȡ��βԪ��
		const T& back()
		{
			return _con.back();
		}
		// ���д�С
		size_t size()
		{
			return _con.size();
		}
		// �п�
		bool empty()
		{
			return _con.empty();
		}

	private:
		Container _con;
	};
}

