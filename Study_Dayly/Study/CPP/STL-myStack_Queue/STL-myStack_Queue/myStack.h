#pragma once

#include "STL-myStack_Queue.h"

// 在 STL 库中 stack、queue 和 priority_queueu 的实现都使用了适配器作为模板参数
// 什么是适配器？在日常生活中也有许多适配器，例如电源适配器，电源适配器的作用大致来说就是将交流电转换为直流电
// 而 C++ 中也存在适配器的概念
// stack 底层一般由数组实现，而如果使用了适配器，就可以直接用vector 来实现stack，即直接使用 vector的成员函数
// 
// 在STL源码中，stack的模板参数为：template <class T, class Container = deque<T> >
// 其中 Container 即为适配器参数，缺省值为deque<T>,deque 是库中的一个模板类
// 实现了各种数据结构的大部分功能，即 STL中的stack是由 deque 这个类来实现的
//

// stack 在之前已经 用C实现过了
// 其是一个 先进后出 数据结构 只能尾插尾删、通过函数取栈顶元素
namespace July
{
	template<class T, class Container = deque<T>>
	class stack
	{
	public:
		// STL 栈的成员是库中的自定义类型，所以不需要构造函数，需要用编译器自动生成的默认构造

		// 尾插--> 压栈
		// 直接调用 deque的尾插函数
		void push(const T& val)
		{
			_con.push_back(val);
		}
		// 尾删--> 出栈
		void pop()
		{
			_con.pop_back();
		}
		// 取栈顶元素
		const T& top()
		{
			return _con.back();				// 使用适配器来实现类时，最好使用都拥有的且功能相同的函数，因为适配器是可以改变的
											// deque、vector等都可以，所以适配器使用的函数最好其他容器也拥有且功能相同
		}
		// 栈大小
		size_t size()
		{
			return _con.size();
		}
		// 判空
		bool empty()
		{
			return _con.empty();
		}
		// satck的基本功能已经实现了，其他功能也可以调用适配器函数实现
		// 适配器可以是其他容器，如果是其他容器，就需要调用其他容器的成员函数
		//
		// 使用 适配器来实现容器 是非常简单的
		// PS:deque是什么？单独写

	private:
		Container _con;						// 成员变量为 一个适配器类型的变量
	};
}
