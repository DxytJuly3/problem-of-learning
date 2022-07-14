#pragma once

#include "STL-myStack_Queue.h"

// �� STL ���� stack��queue �� priority_queueu ��ʵ�ֶ�ʹ������������Ϊģ�����
// ʲô�������������ճ�������Ҳ������������������Դ����������Դ�����������ô�����˵���ǽ�������ת��Ϊֱ����
// �� C++ ��Ҳ�����������ĸ���
// stack �ײ�һ��������ʵ�֣������ʹ�������������Ϳ���ֱ����vector ��ʵ��stack����ֱ��ʹ�� vector�ĳ�Ա����
// 
// ��STLԴ���У�stack��ģ�����Ϊ��template <class T, class Container = deque<T> >
// ���� Container ��Ϊ������������ȱʡֵΪdeque<T>,deque �ǿ��е�һ��ģ����
// ʵ���˸������ݽṹ�Ĵ󲿷ֹ��ܣ��� STL�е�stack���� deque �������ʵ�ֵ�
//

// stack ��֮ǰ�Ѿ� ��Cʵ�ֹ���
// ����һ�� �Ƚ���� ���ݽṹ ֻ��β��βɾ��ͨ������ȡջ��Ԫ��
namespace July
{
	template<class T, class Container = deque<T>>
	class stack
	{
	public:
		// STL ջ�ĳ�Ա�ǿ��е��Զ������ͣ����Բ���Ҫ���캯������Ҫ�ñ������Զ����ɵ�Ĭ�Ϲ���

		// β��--> ѹջ
		// ֱ�ӵ��� deque��β�庯��
		void push(const T& val)
		{
			_con.push_back(val);
		}
		// βɾ--> ��ջ
		void pop()
		{
			_con.pop_back();
		}
		// ȡջ��Ԫ��
		const T& top()
		{
			return _con.back();				// ʹ����������ʵ����ʱ�����ʹ�ö�ӵ�е��ҹ�����ͬ�ĺ�������Ϊ�������ǿ��Ըı��
											// deque��vector�ȶ����ԣ�����������ʹ�õĺ��������������Ҳӵ���ҹ�����ͬ
		}
		// ջ��С
		size_t size()
		{
			return _con.size();
		}
		// �п�
		bool empty()
		{
			return _con.empty();
		}
		// satck�Ļ��������Ѿ�ʵ���ˣ���������Ҳ���Ե�������������ʵ��
		// �����������������������������������������Ҫ�������������ĳ�Ա����
		//
		// ʹ�� ��������ʵ������ �Ƿǳ��򵥵�
		// PS:deque��ʲô������д

	private:
		Container _con;						// ��Ա����Ϊ һ�����������͵ı���
	};
}
